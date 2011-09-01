using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Halak.Bibim
{
    public abstract class GameModule
    {
        #region Static Fields
        public const uint UnspecifiedID = 0x00000000;
        #endregion

        #region Fields
        private uint id;
        private bool alive;
        private bool active;
        #endregion

        #region Properties
        public uint ID
        {
            get { return id; }
            set
            {
                if (id != value)
                {
                    if (id != UnspecifiedID && Node != null && Node.Structure != null)
                    {
                        if (Node.Structure.Find(value))
                            throw new Exception("");
                    }

                    uint oldID = id;

                    id = value;

                    if (Node != null && Node.Structure != null)
                        Node.Structure.OnModuleIDChanged(this, oldID);
                }
            }
        }

        public bool Alive
        {
            get { return alive; }
            set
            {
                if (alive != value)
                {
                    GameModuleStatus old = Status;

                    alive = value;

                    OnStatusChanged(old);
                }
            }
        }

        public bool Active
        {
            get { return active; }
            set
            {
                if (active != value)
                {
                    GameModuleStatus old = Status;

                    active = value;

                    if (alive)
                        OnStatusChanged(old);
                }
            }
        }

        public GameModuleStatus Status
        {
            get
            {
                if (alive)
                {
                    if (active)
                        return GameModuleStatus.Active;
                    else
                        return GameModuleStatus.Alive;
                }
                else
                    return GameModuleStatus.Dead;
            }
        }

        internal GameNode Node
        {
            get;
            set;
        }
        #endregion

        #region Constructors
        protected GameModule()
        {
            id = UnspecifiedID;
            alive = true;
            active = true;
        }

        protected GameModule(uint id)
        {
            this.id = id;
            this.alive = true;
            this.active = true;
        }
        #endregion

        #region Methods
        protected virtual void OnStatusChanged(GameModuleStatus old)
        {
        }
        #endregion
    }
}
