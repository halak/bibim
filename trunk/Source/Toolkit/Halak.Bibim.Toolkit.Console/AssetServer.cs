using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Pipes;
using System.Linq;
using System.Text;
using System.Threading;
using C = System.Console;

namespace Halak.Bibim.Toolkit.Console
{
    public sealed class AssetServer
    {
        static void Main(string[] args)
        {
            C.Title = "Halak Bibim Console > AssetServer";
            C.WriteLine("================================");
            C.WriteLine("Halak Bibim Asset Server");
            C.WriteLine("================================");
            C.WriteLine("Ready");


            NamedPipeServerStream pipe = new NamedPipeServerStream("Echo");
            pipe.WaitForConnection();
            byte[] data = new byte[128];
            int result = pipe.Read(data, 0, 128);
            string s = System.Text.Encoding.ASCII.GetString(data, 0, result);
            C.WriteLine(s); 
            C.WriteLine("Started!");
            for (; ; )
            {
                C.Write("> ");

                string command = C.ReadLine();
                if (string.IsNullOrEmpty(command) == false)
                    command = command.ToLower();
                else
                    command = string.Empty;

                switch (command)
                {
                    case "cls":
                    case "clear":
                        C.Clear();
                        break;
                }

                byte[] response = Encoding.ASCII.GetBytes("GoodBye");
                pipe.Write(response, 0, response.Length);

                C.WriteLine("IsConnected {0}", pipe.IsConnected);

                if (command == "exit")
                    break;
            }

            pipe.Close();

            C.WriteLine("Ended!");
        }
    }
}
