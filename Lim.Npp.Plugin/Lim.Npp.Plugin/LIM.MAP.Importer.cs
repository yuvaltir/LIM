using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
// Imports the CPP DLL
namespace LIM
{
    public static class Importer
    {
        //[DllImport("LIM.MAP.dll", EntryPoint = "replace", ExactSpelling = false)]
        //public static extern string replace(string original, Int32 len);

        //[DllImport("LIM.MAP.dll", CallingConvention = CallingConvention.Cdecl)]
        //public static extern string add(int a, int b);
        [DllImport("LIM.DAWG.Map.dll", EntryPoint = "add", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int add(int a, int b);

        [DllImport("LIM.DAWG.Map.dll", EntryPoint = "replace", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)] 
        public static extern string replace([MarshalAs(UnmanagedType.LPStr)] string original, int len);

        [DllImport("LIM.DAWG.Map.dll", EntryPoint = "replaceBack", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string replaceBack([MarshalAs(UnmanagedType.LPStr)] string original, int len);

        [DllImport("LIM.SMAZ.dll", EntryPoint = "smaz_comp", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string smaz([MarshalAs(UnmanagedType.LPStr)] string inStr, int inlen, int bufferLen);

        [DllImport("LIM.SMAZ.dll", EntryPoint = "smaz_decomp", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string zams([MarshalAs(UnmanagedType.LPStr)] string inStr, int inlen, int bufferLen);

        public enum Operation
        {
            Mil,
            Lim,
            Smaz,
            Zams
        };
    }
}


