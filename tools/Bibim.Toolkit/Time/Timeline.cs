using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim.Time
{
    [ClassID('T', 'M', 'L', 'N')]
    public class Timeline : UpdateableGameModule
    {
        public void Add(IUpdateable item)
        {
        }

        public void Remove(IUpdateable item)
        {
        }

        public override void Update(float dt, int timestamp)
        {
            throw new NotImplementedException();
        }
    }
}
