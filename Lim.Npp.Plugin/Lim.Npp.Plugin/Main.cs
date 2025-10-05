using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Runtime.ExceptionServices;
using System.Runtime.InteropServices;
using System.Security;
using System.Text;
using System.Windows.Forms;
using Kbg.NppPluginNET.PluginInfrastructure;
using Lim.Npp.Plugin;
using LIM;

namespace Kbg.NppPluginNET
{
    class Main
    {
        internal const string PluginName = "Lim.Npp.Plugin";
        //internal const int MaxSelectionLength = 100000;
        //internal const int MaxLineCount = 100;
        
        
        static frmMyDlg _frmMyDlg = null;
        static int idMyDlg = -1;
        static Bitmap tbBmp = Properties.Resources.star;
        static Bitmap tbBmp_tbTab = Properties.Resources.star_bmp;
        static Icon tbIcon = null;
        static IScintillaGateway editor = new ScintillaGateway(PluginBase.GetCurrentScintilla());
        static Lim.Npp.Plugin.PluginConfig _config;

        public static void OnNotification(ScNotification notification)
        {  
            // This method is invoked whenever something is happening in notepad++
            // use eg. as
            // if (notification.Header.Code == (uint)NppMsg.NPPN_xxx)
            // { ... }
            // or
            //
            // if (notification.Header.Code == (uint)SciMsg.SCNxxx)
            // { ... }
        }

        internal static void CommandMenuInit()
        {
            //StringBuilder sbIniFilePath = new StringBuilder(Win32.MAX_PATH);
            //Win32.SendMessage(PluginBase.nppData._nppHandle, (uint) NppMsg.NPPM_GETPLUGINSCONFIGDIR, Win32.MAX_PATH, sbIniFilePath);
            //configFilePath = sbIniFilePath.ToString();
            //if (!Directory.Exists(configFilePath)) Directory.CreateDirectory(configFilePath);
            //configFilePath = Path.Combine(configFilePath, PluginName + ".ini");
            //maxSegmentSelectionLength =Win32.GetPrivateProfileInt("Prameters", "MaxWorkingSegmentLength", MaxSelectionLength, configFilePath);
            //maxLineCount = Win32.GetPrivateProfileInt("Prameters", "MaxLineCount", MaxLineCount, configFilePath);
            LoadConfig();
            PluginBase.SetCommand(0, "Convert", replaceTextEvent, new ShortcutKey(true, false, true, Keys.L));
            PluginBase.SetCommand(1, "Convert back", replaceTextBackEvent, new ShortcutKey(true, false, true, Keys.M));
            PluginBase.SetCommand(0, "SMAZ", smazTextEvent, new ShortcutKey(true, false, true, Keys.S));
            PluginBase.SetCommand(1, "SMAZ back", smazTextBackEvent, new ShortcutKey(true, false, true, Keys.Z));
            PluginBase.SetCommand(2, "Show dialog", myDockableDialog);
            idMyDlg = 1;
        }

        private static void LoadConfig()
        {
            var sbIniFilePath = new StringBuilder(Win32.MAX_PATH);
            var configFilePath = string.Empty;
            Win32.SendMessage(PluginBase.nppData._nppHandle, (uint)NppMsg.NPPM_GETPLUGINSCONFIGDIR, Win32.MAX_PATH, sbIniFilePath);
            configFilePath = sbIniFilePath.ToString();
            if (!Directory.Exists(configFilePath)) Directory.CreateDirectory(configFilePath);
            configFilePath = Path.Combine(configFilePath, PluginName + ".xml");
            if (!File.Exists(configFilePath))
            {
                _config = new PluginConfig { Parsing = new ParsingRules { MaxLineCount = "100", MaxSelectionLength = "100000" } };
                File.WriteAllText(configFilePath, Serializer<PluginConfig>.Serialize(_config));
            }
            else
            {
                _config = Serializer<PluginConfig>.Deserialize(File.ReadAllText(configFilePath));
            }
        }

        internal static void SetToolBarIcon()
        {
            toolbarIcons tbIcons = new toolbarIcons();
            tbIcons.hToolbarBmp = tbBmp.GetHbitmap();
            IntPtr pTbIcons = Marshal.AllocHGlobal(Marshal.SizeOf(tbIcons));
            Marshal.StructureToPtr(tbIcons, pTbIcons, false);
            Win32.SendMessage(PluginBase.nppData._nppHandle, (uint) NppMsg.NPPM_ADDTOOLBARICON, PluginBase._funcItems.Items[idMyDlg]._cmdID, pTbIcons);
            Marshal.FreeHGlobal(pTbIcons);
        }

        internal static void PluginCleanUp()
        {
           // Win32.WritePrivateProfileString("Prameters", "MaxWorkingSegmentLength", maxSegmentSelectionLength.ToString(), configFilePath);
        }

        internal static void UpdateDialog(string text)
        {
            if (_frmMyDlg != null)
            {
                _frmMyDlg.Append(text);
            }
        }

        internal static void ReplaceText(Importer.Operation op=Importer.Operation.Lim)
        {
            try
            {
                var selectionLength = editor.GetSelectionLength();
                var start = editor.GetSelectionNStart(0);
                var end = editor.GetSelectionEnd();
                var replacedTextLength = 0;
                UpdateDialog(string.Format("Replacing all text using {0} between {1} and {2}",op,start.Value,end.Value));
                //var end = start.Value + editor.GetSelectionLength();
                //var replacementCount = selectionLength / MaxSelection;
                //for(var i=0;i< replacementCount; ++i)
                //{                                     
                //    var seletionStart = start.Value + (i* MaxSelection);
                //    var endSelection = i < (selectionLength - 1) ? (seletionStart + MaxSelection -1) : end;
                //    UpdateDialog(String.Format("Replacing text between {0} and {1}", seletionStart, endSelection));
                //    editor.SetSelection(seletionStart, endSelection);                    
                //    ReplaceTextInSelection(back);
                //}
                var lastPosition = 0;
                if (selectionLength > _config.Parsing.MaxSelectionLengthInt)
                {
                    var firstLineId = editor.LineFromPosition(start);
                    var lastLineId = editor.LineFromPosition(end);
                    var lineCount = lastLineId - firstLineId + 1;
                    var batchCount = lineCount / _config.Parsing.MaxLineCountInt;
                    for (int i =0;i< batchCount;++i)
                    {
                        UpdateDialog(string.Format("Processing batch {0} out of {1}", i, batchCount));

                        // if first batch, start is where the selection starts. Otherwise it is the first character of the 
                        // first line in the batch
                        var batchStart = i == 0 ? start.Value : editor.PositionFromLine(firstLineId + (i * _config.Parsing.MaxLineCountInt)).Value;

                        // if last batch, the last character is the last one in the last line. Otherwise it is the last character of 
                        // the last line in the batch
                        int batchEnd;
                        if (i < (batchCount - 1))
                        {                            
                            var lineAfterBatch = firstLineId + ((i + 1) * _config.Parsing.MaxLineCountInt) ; 
                            var positionOfLineAfterBatch = editor.PositionFromLine(lineAfterBatch);
                            batchEnd = positionOfLineAfterBatch.Value > 0 ? positionOfLineAfterBatch.Value - 1 : end.Value;
                        }
                        else
                        {
                            UpdateDialog(string.Format("Reached final batch {0}", i));
                            batchEnd = editor.PositionFromLine(lastLineId+1).Value-1;
                        }
                         
                        UpdateDialog(String.Format("Replacing text between {0} and {1}", batchStart, batchEnd));
                        editor.SetSelection(batchStart, batchEnd);
                        replacedTextLength=ReplaceTextInSelection(op);
                        end = new Position(batchEnd);
                        lastPosition = batchStart + replacedTextLength;
                    }
                }
                else
                {
                    replacedTextLength = ReplaceTextInSelection(op);
                    lastPosition = start.Value + replacedTextLength;
                }
                editor.SetSelection(start.Value, lastPosition);
            
            }
            catch(Exception ex)
            {
                MessageBox.Show(string.Format("Got error {0} {1}", ex, ex.StackTrace)); 
            }
        }

        [HandleProcessCorruptedStateExceptions]
        [SecurityCritical]
        private static int ReplaceTextInSelection(Importer.Operation op = Importer.Operation.Mil)
        {
            string selectedText;
            try
            {
                selectedText = editor.GetSelText(_config.Parsing.MaxSelectionLengthInt);
            }
            catch(Exception ex)
            {
                MessageBox.Show(string.Format("Received serious error from plugin gateway {0} {1}", ex, ex.StackTrace));
                return 0;
            }
            string revertedText = string.Empty;
            char[] outputStr = new char[4096];
            switch (op)
            {
                case Importer.Operation.Mil:
                    revertedText = Importer.replaceBack(selectedText, selectedText.Length);
                    break;
                case Importer.Operation.Lim:
                    revertedText= Importer.replace(selectedText, selectedText.Length);
                    break;
                case Importer.Operation.Smaz:
                    revertedText = Importer.smaz(selectedText, selectedText.Length, 4096);
                    break;
                case Importer.Operation.Zams:
                    revertedText = Importer.zams(selectedText, selectedText.Length, 4096);
                    break;
            }                                    
                editor.ReplaceSel(revertedText);
                return revertedText.Length;
            
        }

        internal static void smazTextEvent()
        {
            try
            {
                ReplaceText(Importer.Operation.Smaz);
            }
            catch (Exception ex)
            {
                MessageBox.Show(string.Format("Got error {0} {1}", ex, ex.StackTrace));
            }
        }

        internal static void smazTextBackEvent()
        {
            try
            {
                ReplaceText(Importer.Operation.Zams);
            }
            catch (Exception ex)
            {
                MessageBox.Show(string.Format("Got error {0} {1}", ex, ex.StackTrace));
            }
        }

        internal static void replaceTextEvent()
        {
            try
            {            
                ReplaceText(Importer.Operation.Lim);                                        
            }
            catch(Exception ex)
            {
                MessageBox.Show(string.Format("Got error {0} {1}", ex, ex.StackTrace));
            }            
            
        }

        internal static void replaceTextBackEvent()
        {
            try
            {
                ReplaceText(Importer.Operation.Mil);                
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }

        }


        internal static void myDockableDialog()
        {
            if (_frmMyDlg == null)
            {
                _frmMyDlg = new frmMyDlg();

                using (Bitmap newBmp = new Bitmap(16, 16))
                {
                    Graphics g = Graphics.FromImage(newBmp);
                    ColorMap[] colorMap = new ColorMap[1];
                    colorMap[0] = new ColorMap();
                    colorMap[0].OldColor = Color.Fuchsia;
                    colorMap[0].NewColor = Color.FromKnownColor(KnownColor.ButtonFace);
                    ImageAttributes attr = new ImageAttributes();
                    attr.SetRemapTable(colorMap);
                    g.DrawImage(tbBmp_tbTab, new Rectangle(0, 0, 16, 16), 0, 0, 16, 16, GraphicsUnit.Pixel, attr);
                    tbIcon = Icon.FromHandle(newBmp.GetHicon());
                }

                NppTbData _nppTbData = new NppTbData();
                _nppTbData.hClient = _frmMyDlg.Handle;
                _nppTbData.pszName = "Shishito-Less is More";
                _nppTbData.dlgID = idMyDlg;
                _nppTbData.uMask = NppTbMsg.DWS_DF_CONT_RIGHT | NppTbMsg.DWS_ICONTAB | NppTbMsg.DWS_ICONBAR;
                _nppTbData.hIconTab = (uint)tbIcon.Handle;
                _nppTbData.pszModuleName = PluginName;                
                IntPtr _ptrNppTbData = Marshal.AllocHGlobal(Marshal.SizeOf(_nppTbData));
                Marshal.StructureToPtr(_nppTbData, _ptrNppTbData, false);

                Win32.SendMessage(PluginBase.nppData._nppHandle, (uint) NppMsg.NPPM_DMMREGASDCKDLG, 0, _ptrNppTbData);
            }
            else
            {
                Win32.SendMessage(PluginBase.nppData._nppHandle, (uint) NppMsg.NPPM_DMMSHOW, 0, _frmMyDlg.Handle);
            }
        }
    }
}