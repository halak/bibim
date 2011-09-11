using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Text;

namespace Halak.Bibim
{
    public static class GameModuleFactory
    {
        #region Fields
        static Dictionary<uint, ConstructorInfo> entries;
        #endregion

        #region Constructors
        static GameModuleFactory()
        {
            entries = new Dictionary<uint, ConstructorInfo>(100);
            AddEntries(Assembly.GetEntryAssembly().GetTypes());
            AddEntries(Assembly.GetCallingAssembly().GetTypes());
            AddEntries(Assembly.GetExecutingAssembly().GetTypes());
        }
        #endregion

        #region Methods
        /// <summary>
        /// 지정한 class 식별자의 Instance를 생성합니다.
        /// </summary>
        /// <param name="classID">GameModule class 식별자</param>
        /// <returns>생성된 Module</returns>
        public static GameModule Create(uint classID)
        {
            return null;
        }

        #region Private
        private static void AddEntries(Type[] types)
        {
            foreach (Type item in types)
            {
                object[] attributeObjects = item.GetCustomAttributes(typeof(GameModuleAttribute), true);
                if (attributeObjects != null && attributeObjects.Length > 0)
                {
                    GameModuleAttribute attribute = (GameModuleAttribute)attributeObjects[0];

                    Debug.Assert(entries.ContainsKey(attribute.ClassID) == false);

                    entries.Add(attribute.ClassID, item.GetConstructor(Type.EmptyTypes));
                }
            }
        }
        #endregion
        #endregion
    }
}
