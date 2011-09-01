using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Text;
using C = System.Console;

namespace Halak.Bibim.Toolkit.Console
{
    /// <summary>
    /// 실행시간에 여러가지 Program을 결정하여 실행해주는 Program.
    /// </summary>
    public sealed class Hub
    {
        [MTAThread]
        static void Main(string[] args)
        {
            try
            {
                if (args.Length == 0 || string.IsNullOrWhiteSpace(args[0]) || string.IsNullOrEmpty(args[0]))
                    return;

                string command = args[0].Trim();
                string[] filteredArgs = new string [args.Length - 1];

                for (int i = 0; i < filteredArgs.Length; i++)
                    filteredArgs[i] = args[i + 1];

                if (command[0] == '-')
                    ProcessCommand(command, filteredArgs);
                else
                    ExecuteProgram(command, filteredArgs);

            }
            catch (Exception e)
            {
                C.WriteLine(e.Message);
                C.WriteLine(e.StackTrace);
            }
        }

        /// <summary>
        /// 기본 명령들을 처리합니다.
        /// </summary>
        /// <param name="command">명령</param>
        /// <param name="args">명령 인자</param>
        static void ProcessCommand(string command, string[] args)
        {
            Trace.Assert(command[0] == '-');

            switch (command)
            {
                case "-?":
                    PrintHelpMessages();
                    break;
            }
        }

        /// <summary>
        /// Console에서 사용할 수 있는 명령어를 비롯해 각종 도움말들을 출력합니다.
        /// </summary>
        static void PrintHelpMessages()
        {
        }

        /// <summary>
        /// 지정한 이름의 class에 연결되어 있는 Main 함수를 호출합니다.
        /// </summary>
        /// <param name="className">class 이름</param>
        /// <param name="args">명령 인자</param>
        static void ExecuteProgram(string className, string[] args)
        {
            MethodInfo programEntry = FindProgramEntry(className);
            if (programEntry != null)
            {
                Trace.Assert(programEntry.GetParameters().Length == 1);
                Trace.Assert(programEntry.GetParameters()[0].ParameterType == typeof(string[]));

                programEntry.Invoke(null, new object[] { args });
            }
        }

        /// <summary>
        /// 지정한 이름의 Program Main Entry Method 객체를 찾아서 반환합니다.
        /// </summary>
        /// <param name="className">class 이름</param>
        /// <returns>Main Method 객체</returns>
        static MethodInfo FindProgramEntry(string className)
        {
            Assembly[] assemblies = GetAssemblies();
            foreach (Assembly item in assemblies)
            {
                MethodInfo programEntry = FindProgramEntry(className, item.GetTypes());
                if (programEntry != null)
                    return programEntry;
            }

            return null;
        }

        /// <summary>
        /// 지정한 Type 목록에서 지정한 이름의 Program Main Entry Method 객체를 찾아서 반환합니다.
        /// </summary>
        /// <param name="className">class 이름</param>
        /// <param name="types">Type 목록</param>
        /// <returns>Main Method 객체</returns>
        static MethodInfo FindProgramEntry(string className, Type[] types)
        {
            foreach (Type item in types)
            {
                if (item.FullName == className || item.Name == className)
                {
                    MethodInfo methodInfo = item.GetMethod("Main", BindingFlags.Static | BindingFlags.Public | BindingFlags.NonPublic);
                    ParameterInfo[] parameters = methodInfo.GetParameters();
                    if (parameters.Length == 1 && parameters[0].ParameterType == typeof(string[]))
                        return methodInfo;
                }
            }

            return null;
        }

        /// <summary>
        /// 현재 Assembly 목록을 가져옵니다.
        /// </summary>
        /// <returns>Assembly 목록</returns>
        static Assembly[] GetAssemblies()
        {
            Assembly assembly1 = Assembly.GetExecutingAssembly();
            Assembly assembly2 = Assembly.GetEntryAssembly();
            Assembly assembly3 = Assembly.GetCallingAssembly();

            if (assembly1 != assembly2)
            {
                if (assembly1 != assembly3 && assembly2 != assembly3)
                    return new Assembly[] { assembly1, assembly2, assembly3 };
                else
                    return new Assembly[] { assembly1, assembly2 };
            }
            else
            {
                if (assembly1 != assembly3)
                    return new Assembly[] { assembly1, assembly3 };
                else
                    return new Assembly[] { assembly1 };
            }
        }
    }
}
