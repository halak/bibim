using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Asset.Pipeline
{
    public interface ICookable<TOutput> : ICookable
    {
        new TOutput Cook(CookingContext context);
    }
}
