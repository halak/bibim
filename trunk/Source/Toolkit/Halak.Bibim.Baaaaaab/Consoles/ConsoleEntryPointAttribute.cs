﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Bab.Consoles
{
    [AttributeUsage(AttributeTargets.Class, AllowMultiple = false, Inherited = false)]
    public sealed class ConsoleEntryPointAttribute : Attribute
    {
    }
}
