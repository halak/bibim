﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim
{
    [AttributeUsage(AttributeTargets.Class, AllowMultiple = false, Inherited = false)]
    public class GameModuleAttribute : Attribute
    {
        #region Properties
        public uint ClassID
        {
            get;
            private set;
        }
        #endregion

        #region Constructors
        public GameModuleAttribute(char a, char b, char c, char d)
            : this(FOURCC.Make(a, b, c, d))
        {
        }

        public GameModuleAttribute(uint classID)
        {
            ClassID = classID;
        }
        #endregion

        #region StaticMethods
        public static uint GetClassID(Type type)
        {
            object[] attributes = type.GetCustomAttributes(typeof(GameModuleAttribute), false);
            if (attributes != null && attributes.Length > 0)
                return ((GameModuleAttribute)attributes[0]).ClassID;
            else
                return 0;
        }
        #endregion
    }
}