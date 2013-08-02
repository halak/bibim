using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Bibim.Time
{
    public interface IUpdateable
    {
        void Update(float dt, int timestamp);
    }
}
