using System;
using System.Collections.Generic;
using System.Text;

namespace Bibim
{
    public abstract class GameModule
    {
        #region Static Fields
        public const int UnspecifiedID = -1;
        #endregion

        #region Fields
        private int id;
        private bool alive;
        private bool active;
        #endregion

        #region Properties
        public int ID
        {
            get { return id; }
            set
            {
                if (id != value)
                {
                    if (id != UnspecifiedID && Node != null && Node.Tree != null)
                    {
                        if (Node.Tree.Find(value) != null)
                            throw new ArgumentException(string.Empty, "value");
                    }

                    int oldID = id;

                    id = value;

                    if (Node != null && Node.Tree != null)
                        Node.Tree.OnModuleIDChanged(this, oldID);
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

                    // DeadStatus에선 Active가 바뀌어도 Status가 바뀌지 않듯
                    // Active는 Status에 무조건적으로 영향을 주지 않습니다.
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

        public int ClassID
        {
            get { return ClassIDAttribute.GetClassID(GetType()); }
        }

        internal GameModuleNode Node
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

        protected GameModule(int id)
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
