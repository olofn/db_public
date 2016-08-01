using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Xml;

namespace VerkstanEditor.Logic
{
    public class Timeline: IDisposable
    {
        #region Properties
        private List<Channel> channels;
        public ICollection<Channel> Channels
        {
            get
            {
                return channels;
            }
        }
        public String Name
        {
            get
            {
                return operatorParent.Name;
            }
        }
        #endregion

        #region Private Variables
        private Operator operatorParent;
        private Clip.EventHandler clipStateChangedHandler;
        private Channel.EventHandler channelStateChangedHandler;
        #endregion

        #region Constructors
        public Timeline(Operator operatorParent)
        {
            this.operatorParent = operatorParent;
            channels = new List<Channel>();
            clipStateChangedHandler = new Clip.EventHandler(this.clip_StateChanged);
            channelStateChangedHandler = new Channel.EventHandler(this.channel_StateChanged);
        }
        #endregion

        #region Public Methods
        public List<GeneratorClip> GetGeneratorClips()
        {
            List<GeneratorClip> result = new List<GeneratorClip>();

            foreach (Channel channel in channels)
                foreach (Clip clip in channel.Clips)
                    if (typeof(GeneratorClip) == clip.GetType())
                        result.Add((GeneratorClip)clip);

            return result;
        }
        public List<SplineClip> GetSplineClips()
        {
            List<SplineClip> result = new List<SplineClip>();

            foreach (Channel channel in channels)
                foreach (Clip clip in channel.Clips)
                    if (typeof(SplineClip) == clip.GetType())
                        result.Add((SplineClip)clip);

            return result;
        }
        public void Dispose()
        {
            foreach (Channel channel in channels)
                channel.Dispose();
        }
        public void SelectClips(Rectangle rectangle)
        {
            ICollection<Clip> oldSelection = GetSelectedClips();
            ICollection<Clip> newSelection = GetClipsIn(rectangle);

            foreach (Clip clip in oldSelection)
                if (!newSelection.Contains(clip))
                    clip.IsSelected = false;

            foreach (Clip clip in newSelection)
                if (!oldSelection.Contains(clip))
                    clip.IsSelected = true;
        }
        public void SelectAllClips()
        {
            foreach (Channel channel in channels)
                foreach (Clip clip in channel.Clips)
                    if (!clip.IsSelected)
                        clip.IsSelected = true;
        }
        public void DeselectAllClips()
        {
            foreach (Channel channel in channels)
                foreach (Clip clip in channel.Clips)
                    if (clip.IsSelected)
                        clip.IsSelected = false;
        }
        public void ClearClips()
        {

        }
        public ICollection<Clip> GetSelectedClips()
        {
            List<Clip> selected = new List<Clip>();
            foreach (Channel channel in channels)
            {
                foreach (Clip clip in channel.Clips)
                {
                    if (clip.IsSelected)
                        selected.Add(clip);
                }
            }
            return selected;
        }
        public ICollection<Clip> GetNonSelectedClips()
        {
            List<Clip> nonSelected = new List<Clip>();
            foreach (Channel channel in channels)
            {
                foreach (Clip clip in channel.Clips)
                {
                    if (!clip.IsSelected)
                        nonSelected.Add(clip);
                }
            }
            return nonSelected;
        }
        public void MoveSelectedClips(Point point)
        {
            ICollection<Clip> selected = GetSelectedClips();

            foreach (Clip clip in selected)
            {
                Rectangle dim = clip.Dimension;
                dim.X += point.X;
                dim.Y += point.Y;
                // Cannot perform move if a clip ends up outside of a channel.
                if (dim.X < 0
                    || dim.Y >= channels.Count
                    || dim.Y < 0)
                    return;
            }
            foreach (Clip clip in selected)
            {
                if (Move(clip, point))
                    OnClipMoved(clip);
            }
        }
        public void RemoveSelectedClips()
        {
            ICollection<Clip> selected = GetSelectedClips();
            foreach (Clip clip in selected)
                channels[clip.Dimension.Y].RemoveCip(clip);

            OnClipRemoved(selected);

            foreach (Clip clip in selected)
            {
                clip.StateChanged -= clipStateChangedHandler;
                clip.Dispose();
            }

            UpdateCoreClips();
        }
        public void ResizeSelectedClips(int x)
        {
            ICollection<Clip> selected = GetSelectedClips();
            ICollection<Clip> notSelected = GetNonSelectedClips();

            foreach (Clip selectedClip in selected)
            {
                Rectangle dim = selectedClip.Dimension;
                dim.Width += x;

                // Cannot perform resize when a clip gets a size less than 1.
                if (dim.Width < 1)
                    return;
            }

            foreach (Clip clip in selected)
                if (Resize(clip, x))
                    OnClipResized(clip);
        }
        public Clip GetClipAt(Point point)
        {
            foreach (Channel channel in channels)
                foreach (Clip clip in channel.Clips)
                    if (clip.Dimension.Contains(point))
                        return clip;
            return null;
        }
        public ICollection<Clip> GetClipsIn(Rectangle rectangle)
        {
            List<Clip> result = new List<Clip>();
            foreach (Channel channel in channels)
                foreach (Clip clip in channel.Clips)
                    if (rectangle.IntersectsWith(clip.Dimension))
                        result.Add(clip);
         
            return result;
        }
        public int GetBeats()
        {
            int beats = 0;
            foreach (Channel channel in channels)
                if (channel.GetBeats() > beats)
                    beats = channel.GetBeats();
            return beats;
        }
        public int GetTicks()
        {
            return GetBeats() * Metronome.TicksPerBeat;
        }
        public void AddChannel(Channel channel)
        {
            int number = 0;
            foreach (Channel presentChannel in channels)
                if (number < presentChannel.ChannelNumber)
                    number = presentChannel.ChannelNumber;

            channel.ChannelNumber = number + 1;
            channel.Y = channels.Count;
            channels.Add(channel);
            OnChannelAdded(channel);
            channel.StateChanged += channelStateChangedHandler;
        }
        public void RemoveChannel(Channel channel)
        {
            channel.StateChanged -= channelStateChangedHandler;
            foreach (Clip clip in channel.Clips)
                clip.StateChanged -= clipStateChangedHandler;

            channels.Remove(channel);

            foreach (Channel presentChannel in channels)
                if (presentChannel.Y > channel.Y)
                    presentChannel.Y--;

            OnChannelRemoved(channel);
            channel.Dispose();

            UpdateCoreClips();
        }
        public void AddClip(Clip clip, Point location, int beats)
        {
            if (location.X < 0 || beats <= 0 || location.Y < 0 || location.Y >= channels.Count)
                return;

            clip.Dimension = new Rectangle(location.X, location.Y, beats, 1);
            channels[location.Y].AddClip(clip);
            OnClipAdded(clip);
            clip.StateChanged += clipStateChangedHandler;

            UpdateCoreClips();
        }
        public void SelectChannel(Point point)
        {
            if (channels.Count <= point.Y)
                return;

            Channel selectedChannel = GetSelectedChannel();
            Channel channel = channels[point.Y];

            if (selectedChannel == channel)
                return;

            if (selectedChannel != null)
                selectedChannel.IsSelected = false;

            channel.IsSelected = true;
        }
        public Channel GetSelectedChannel()
        {
            foreach (Channel channel in channels)
                if (channel.IsSelected)
                    return channel;
            return null;
        }
        public void RemoveSelectedChannel()
        {
            Channel channel = GetSelectedChannel();
            if (channel != null)
                RemoveChannel(channel);
        }
        public XmlElement ToXmlElement(XmlDocument doc)
        {
            XmlElement root = doc.CreateElement("timeline");

            foreach (Channel channel in channels)
                root.AppendChild(FromChannelToXmlElement(channel, doc));

            return root;
        }
        public void FromXmlElement(XmlElement root)
        {
            foreach (XmlNode node in root.ChildNodes)
            {
                XmlElement element = (XmlElement)node;
                if (element.Name == "channel")
                    FromXmlElementToChannel(element);
            }
        }
        #endregion

        #region Private Methods
        private void UpdateCoreClips()
        {
            operatorParent.BindedCoreOperator.ClearClips();
            int numberOfClips = 0;
            foreach (Channel channel in channels)
            {
                foreach (Clip clip in channel.Clips)
                {
                    operatorParent.BindedCoreOperator.SetClipId(numberOfClips, clip.Id);
                    numberOfClips++;
                }
            }
            operatorParent.BindedCoreOperator.SetNumberOfClips(numberOfClips);
            if (GetTicks() == 0)
                operatorParent.BindedCoreOperator.SetTicks(1);
            else
                operatorParent.BindedCoreOperator.SetTicks(GetTicks());
        }   
        private bool Move(Clip clip, Point point)
        {
            Rectangle dim = clip.Dimension;
            dim.X += point.X;
            dim.Y += point.Y;

            channels[clip.Dimension.Y].RemoveCip(clip);
            clip.Dimension = new Rectangle(dim.X, dim.Y, dim.Width, dim.Height); 
            channels[dim.Y].AddClip(clip);

            return true;
        }
        private bool Resize(Clip clip, int x)
        {
            Rectangle dim = clip.Dimension;
            dim.Width += x;        
            clip.Dimension = new Rectangle(dim.X, dim.Y, dim.Width, dim.Height);

            return true;
        }
        private XmlElement FromChannelToXmlElement(Channel channel, XmlDocument doc)
        {
            XmlElement channelElement = doc.CreateElement("channel");
            XmlElement number = doc.CreateElement("number");
            number.InnerText = channel.ChannelNumber.ToString();
            channelElement.AppendChild(number);

            foreach (Clip clip in channel.Clips)
                channelElement.AppendChild(clip.ToXmlElement(doc));
            
            return channelElement;
        }
        private void FromXmlElementToChannel(XmlElement channelElement)
        {
            Channel channel = new Channel();
            AddChannel(channel);
            foreach (XmlNode node in channelElement.ChildNodes)
            {
                if (node.Name == "number")
                {
                    channel.ChannelNumber = int.Parse(node.InnerText);
                }
                else if (node.Name == "clip")
                {
                    XmlElement element = (XmlElement)node;
                    if (element.GetAttribute("type") == "spline")
                    {
                        SplineClip clip = new SplineClip();
                        clip.FromXmlElement(element);
                        AddClip(clip, clip.Location, clip.Dimension.Width);
                    }
                    else if (element.GetAttribute("type") == "generator")
                    {
                        GeneratorClip clip = new GeneratorClip();
                        clip.FromXmlElement(element);
                        AddClip(clip, clip.Location, clip.Dimension.Width);
                    }
                }
            }
        }
        #endregion

        #region Events
        public class EventArgs : System.EventArgs
        {
            public readonly ICollection<Clip> Clips;
            public readonly Channel Channel;
            public EventArgs(Channel channel, ICollection<Clip> clips)
            {
                Channel = channel;
                Clips = clips;
            }
        }
        public delegate void EventHandler(Timeline.EventArgs e);
        public event EventHandler ClipStateChanged;
        protected void OnClipStateChanged(Clip clip)
        {
            List<Clip> clips = new List<Clip>();
            clips.Add(clip);
            if (ClipStateChanged != null)
                ClipStateChanged(new Timeline.EventArgs(null, clips));
        }
        public event EventHandler ChannelStateChanged;
        protected void OnChannelStateChanged(Channel channel)
        {
            if (ChannelStateChanged != null)
                ChannelStateChanged(new Timeline.EventArgs(channel, new List<Clip>()));
        }
        public event EventHandler ChannelRemoved;
        protected void OnChannelRemoved(Channel channel)
        {
            if (ChannelRemoved != null)
                ChannelRemoved(new Timeline.EventArgs(channel, null));
        }
        public event EventHandler ChannelAdded;
        protected void OnChannelAdded(Channel channel)
        {
            if (ChannelAdded != null)
                ChannelAdded(new Timeline.EventArgs(channel, null));
        }
        public event EventHandler ClipAdded;
        protected void OnClipAdded(Clip clip)
        {
            List<Clip> clips = new List<Clip>();
            clips.Add(clip);
            if (ClipAdded != null)
                ClipAdded(new Timeline.EventArgs(null, clips));
        }
        public event EventHandler ClipRemoved;
        protected void OnClipRemoved(ICollection<Clip> clips)
        {
            if (ClipRemoved != null)
                ClipRemoved(new Timeline.EventArgs(null, clips));
        }
        public event EventHandler ClipMoved;
        protected void OnClipMoved(Clip clip)
        {
            List<Clip> clips = new List<Clip>();
            clips.Add(clip);
            if (ClipMoved != null)
                ClipMoved(new Timeline.EventArgs(null, clips));
        }
        public event EventHandler ClipResized;
        protected void OnClipResized(Clip clip)
        {
            List<Clip> clips = new List<Clip>();
            clips.Add(clip);
            if (ClipResized != null)
                ClipResized(new Timeline.EventArgs(null, clips));
        }
        #endregion 

        #region Event Handlers
        private void channel_StateChanged(Channel channel)
        {
            OnChannelStateChanged(channel);
        }
        private void clip_StateChanged(Clip clip)
        {
            OnClipStateChanged(clip);
        }
        #endregion
    }
}
