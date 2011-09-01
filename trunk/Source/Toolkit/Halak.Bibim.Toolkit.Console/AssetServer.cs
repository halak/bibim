using System;
using System.Collections.Generic;
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
            C.WriteLine("================================");
            C.WriteLine("Halak Bibim Asset Server");
            C.WriteLine("================================");
            C.WriteLine("Ready");

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

                if (command == "exit")
                    break;
            }

            C.WriteLine("Ended!");
        }
    }
}
