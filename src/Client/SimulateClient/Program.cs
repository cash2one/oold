using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Text;

namespace SimulateClient
{
    static class Program
    {
        [DllImport("kernel32.dll")]
        public static extern bool AllocConsole();

        [DllImport("kernel32.dll")]
        public static extern bool FreeConsole();

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            init();
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new FormLogin());
            final();
        }

        static void init()
        {
            AllocConsole();

            UnityGMClient.CClientCore.Singleton = new UnityGMClient.CClientCore();
            UnityGMClient.CClientCore.Singleton.Init();

             

            string file = System.Environment.CurrentDirectory;
            file += "SimulateClient.log";
            m_outFile = new System.IO.FileInfo(file);
            System.IO.FileStream stream = m_outFile.Open(System.IO.FileMode.Append, System.IO.FileAccess.Write, System.IO.FileShare.Write | System.IO.FileShare.Delete);
            //m_streamWriter = new System.IO.StreamWriter(stream);

            DateTime dateTime = DateTime.Now;
        }

        static void final()
        {
            UnityGMClient.CClientCore.Singleton.Final();
            FreeConsole();
        }
        static void timerWait_Tick(object sender, EventArgs e)
        {
            UnityUtility.CTrace.Singleton.update(cbTraceUpdate);
        }

        static void cbTraceUpdate(DateTime a_dataTime, UnityUtility.ETracerLevel a_level, string a_context, string a_file, int a_line)
        {
            StringBuilder strBuilder = new StringBuilder();
            strBuilder.Append(a_dataTime.ToString("[yyyy-MM-dd HH:mm:ss]"));
            strBuilder.Append("[" + a_level.ToString() + "]");
            strBuilder.Append(a_context);
            strBuilder.Append("[" + a_file + "(" + a_line.ToString() + ")]\n");

            //m_streamWriter.WriteLine(strBuilder.ToString());
            //m_streamWriter.Flush();

            Console.WriteLine("[{0}]{1}", a_level, a_context);
        }

        static System.IO.FileInfo m_outFile;
        //static System.IO.StreamWriter m_streamWriter;
        static System.Timers.Timer m_waitTimer = new System.Timers.Timer();
    }
}
