using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;
using System.Xml.Serialization;
using Bibim.Asset;

namespace Bibim.Animation
{
    public abstract class SequenceTemplate<T> : GameAsset, IXmlSerializable
    {
        #region Fields
        private Keyframe<T>[] keyframes;
        private float duration;
        private bool startTimeChanged;
        #endregion

        #region Properties
        public float Duration
        {
            get
            {
                if (duration < 0.0f)
                {
                    duration = 0.0f;

                    foreach (var item in keyframes)
                        duration += item.Duration;
                }

                return duration;
            }
        }

        public Keyframe<T> this[int index]
        {
            get { return GetKeyframe(index); }
            set
            {
                SetKeyframe(index, value);
            }
        }

        public Keyframe<T> this[float time]
        {
            get { return GetKeyframe(time); }
        }
        #endregion

        #region Constructors
        public SequenceTemplate()
        {
            keyframes = Keyframe<T>.ZeroArray;
            duration = 0.0f;
            startTimeChanged = true;
        }
        #endregion

        #region Methods
        public void AddKeyframe(Keyframe<T> item)
        {
            if (item.Duration < 0.0f)
                throw new ArgumentException("item.Duration");

            var newKeyframes = new Keyframe<T>[keyframes.Length + 1];
            for (int i = 0; i < keyframes.Length; i++)
                newKeyframes[i] = keyframes[i];
            newKeyframes[newKeyframes.Length - 1] = item;

            keyframes = newKeyframes;
            startTimeChanged = true;
        }

        public void InsertKeyframe(int index, Keyframe<T> item)
        {
            if (index < 0 || index >= keyframes.Length)
                throw new ArgumentOutOfRangeException("index");
            if (item.Duration < 0.0f)
                throw new ArgumentException("item.Duration");

            var newKeyframes = new Keyframe<T>[keyframes.Length + 1];
            for (int i = 0; i < index; i++)
                newKeyframes[i] = keyframes[i];
            newKeyframes[index] = item;
            for (int i = index + 1; i < keyframes.Length; i++)
                newKeyframes[i] = keyframes[i - 1];

            keyframes = newKeyframes;
            startTimeChanged = true;
        }

        public void InsertKeyframe(float time, Keyframe<T> item)
        {
            InsertKeyframe(GetKeyframeIndex(time), item);
        }

        public void RemoveKeyframe(int index)
        {
            if (index < 0 || index >= keyframes.Length)
                throw new ArgumentOutOfRangeException("index");

            var newKeyframes = new Keyframe<T>[keyframes.Length - 1];
            for (int i = 0; i < index; i++)
                newKeyframes[i] = keyframes[i];
            for (int i = index + 1; i < keyframes.Length; i++)
                newKeyframes[i - 1] = keyframes[i];

            keyframes = newKeyframes;
            startTimeChanged = true;
        }

        public void RemoveKeyframe(float time)
        {
            int index = GetKeyframeIndex(time);
            if (index != -1)
                RemoveKeyframe(index);
        }

        public void RemoveAllKeyframes()
        {
            keyframes = Keyframe<T>.ZeroArray;
        }

        public int GetNumberOfKeyframes()
        {
            return keyframes.Length;
        }

        public Keyframe<T> GetKeyframe(int index)
        {
            if (startTimeChanged)
            {
                startTimeChanged = false;
                UpdateStartTimes();
            }

            return keyframes[index];
        }

        public Keyframe<T> GetKeyframe(float time)
        {
            int index = GetKeyframeIndex(time);
            if (index != -1)
                return keyframes[index];
            else
                return Keyframe<T>.Empty;
        }

        public int GetKeyframeIndex(float time)
        {
            return GetKeyframeIndex(time, 0);
        }

        public int GetKeyframeIndex(float time, int startIndex)
        {
            if (keyframes.Length == 0)
                return -1;
            if (time <= 0.0f)
                return 0;

            if (startTimeChanged)
            {
                startTimeChanged = false;
                UpdateStartTimes();
            }

            for (int i = startIndex; 0 <= i && i < keyframes.Length; )
            {
                var item = keyframes[i];
                if (item.StartTime <= time && time < item.StartTime + item.Duration)
                    return i;
                else
                {
                    if (time < item.StartTime)
                        i--;
                    else
                        i++;
                }
            }

            return keyframes.Length - 1;
        }

        public void SetKeyframe(int index, Keyframe<T> item)
        {
            if (item.Duration < 0.0f)
                throw new ArgumentException("item.Duration");

            if (keyframes[index].Duration != item.Duration)
            {
                ResetDuration();
                startTimeChanged = true;
            }

            keyframes[index] = item;
        }

        private void ResetDuration()
        {
            duration = -1.0f;
        }

        private void UpdateStartTimes()
        {
            float time = 0.0f;
            for (int i = 0; i < keyframes.Length; i++)
            {
                keyframes[i].StartTime = time;
                time += keyframes[i].Duration;
            }
        }
        #endregion

        #region IXmlSerializable
        public System.Xml.Schema.XmlSchema GetSchema()
        {
            return null;
        }

        public void ReadXml(System.Xml.XmlReader reader)
        {
            bool wasEmpty = reader.IsEmptyElement;
            reader.Read();

            if (wasEmpty)
                return;

            XmlSerializer valueSerializer = new XmlSerializer(typeof(T));
            var keyframeList = new LinkedList<Keyframe<T>>();

            reader.ReadStartElement("Keyframes");

            float totalDuration = 0.0f;
            while (reader.NodeType != System.Xml.XmlNodeType.EndElement)
            {
                float duration = float.Parse(reader.GetAttribute("Duration"));
                reader.ReadStartElement("Item");
                T value = (T) valueSerializer.Deserialize(reader);
                reader.ReadEndElement();

                keyframeList.AddLast(new Keyframe<T>(value, duration, totalDuration));
                totalDuration += duration;
            }

            reader.ReadEndElement();

            this.keyframes = new Keyframe<T>[keyframeList.Count];
            this.duration = totalDuration;
            this.startTimeChanged = false;

            int index = 0;
            foreach (var item in keyframeList)
                this.keyframes[index++] = item;
        }

        public void WriteXml(System.Xml.XmlWriter writer)
        {
            XmlSerializer valueSerializer = new XmlSerializer(typeof(T));

            writer.WriteStartElement("Keyframes");
            foreach (var item in keyframes)
            {
                writer.WriteStartElement("Item");
                writer.WriteAttributeString("Duration", item.Duration.ToString());
                valueSerializer.Serialize(writer, item.Value);
                writer.WriteEndElement();
            }
            writer.WriteEndElement();
        }
        #endregion
    }
}
