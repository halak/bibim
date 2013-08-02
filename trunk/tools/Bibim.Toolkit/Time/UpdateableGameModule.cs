using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Time
{
    public abstract class UpdateableGameModule : GameModule, IUpdateable
    {
        public UpdateableGameModule()
        {
        }

        public abstract void Update(float dt, int timestamp);
    }
}
