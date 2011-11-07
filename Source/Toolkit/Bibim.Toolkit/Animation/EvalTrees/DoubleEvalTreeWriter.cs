﻿using System;
using System.Collections.Generic;
using System.Text;
using Bibim.Asset;
using Bibim.IO;

namespace Bibim.Animation
{
    [GameAssetWriter(typeof(DoubleEvalTree))]
    public sealed class DoubleEvalTreeWriter : EvalTreeWriterTemplate<DoubleEvalTree, double>
    {
    }
}
