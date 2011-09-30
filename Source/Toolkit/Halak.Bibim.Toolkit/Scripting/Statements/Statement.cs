using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim.Scripting.Statements
{
    public abstract class Statement
    {
        #region Fields
        private Statement previous;
        private Statement next;
        #endregion

        #region Properties
        public Statement Previous
        {
            get { return previous; }
            set
            {
                if (previous != value)
                {
                    if (previous != null)
                        previous.next = null;

                    previous = value;

                    if (previous != null)
                        previous.next = this;
                }
            }
        }

        public Statement Next
        {
            get { return next; }
            set
            {
                if (next != value)
                {
                    if (next != null)
                        next.previous = null;

                    next = value;

                    if (next != null)
                        next.previous = this;
                }
            }
        }
        #endregion

        #region Constructors
        protected Statement()
        {
        }
        #endregion
    }
}
