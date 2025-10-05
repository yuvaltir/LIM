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
        [DllImport("LIM.DAWG.Map.dll", EntryPoint = "replace", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string replace([MarshalAs(UnmanagedType.LPStr)] string original, int len);

        [DllImport("LIM.DAWG.Map.dll", EntryPoint = "replaceBack", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.LPStr)]
        public static extern string replaceBack([MarshalAs(UnmanagedType.LPStr)] string original, int len);
       
    }
}


