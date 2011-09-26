﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Text;
using Halak.Bibim.Reflection;

namespace Halak.Bibim.UI
{
    public static class UIElementFactory
    {
        #region Fields
        static Dictionary<uint, ConstructorInfo> entries;
        #endregion

        #region Constructors
        static UIElementFactory()
        {
            ICollection<Type> moduleClasses = AssemblyUtility.FindClasses(typeof(UIElement), true, false);

            entries = new Dictionary<uint, ConstructorInfo>(moduleClasses.Count);

            foreach (Type item in moduleClasses)
            {
                UIElementAttribute attribute = item.GetCustomAttribute<UIElementAttribute>();
                if (attribute != null)
                {
                    Debug.Assert(entries.ContainsKey(attribute.ClassID) == false);
                    entries.Add(attribute.ClassID, item.GetConstructor(Type.EmptyTypes));
                }
            }
        }
        #endregion

        #region Methods
        /// <summary>
        /// 지정한 class 식별자의 Instance를 생성합니다.
        /// </summary>
        /// <param name="classID">GameModule class 식별자</param>
        /// <returns>생성된 Module</returns>
        public static UIElement Create(uint classID)
        {
            return null;
        }
        #endregion
    }
}
