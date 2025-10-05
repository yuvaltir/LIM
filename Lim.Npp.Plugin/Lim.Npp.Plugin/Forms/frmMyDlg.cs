using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Kbg.NppPluginNET
{
    public partial class frmMyDlg : Form
    {
        public frmMyDlg()
        {
            InitializeComponent();
        }

        public void Append(string text)
        {
            if (string.IsNullOrEmpty(DialogText))
            {
                richTextBox1.Text = text;
            }
            else
            {
                richTextBox1.Text += string.Format("{0}{1}", Environment.NewLine,text);
            }
        }

        public  string DialogText
        {
            get { return this.richTextBox1.Text; }
            set { this.richTextBox1.Text = value; }
        }
    }
}
