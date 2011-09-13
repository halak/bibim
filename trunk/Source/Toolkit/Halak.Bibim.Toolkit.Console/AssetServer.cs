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

                C.WriteLine("IsConnected {0}", pipe.IsConnected);

                if (command == "exit")
                    break;
            }

            pipe.Close();

            C.WriteLine("Ended!");
        }
    }
}
