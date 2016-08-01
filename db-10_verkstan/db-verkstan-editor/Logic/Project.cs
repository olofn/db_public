using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace VerkstanEditor.Logic
{
    public class Project: IDisposable
    {
        #region Properties
        private String filename;
        public String Filename
        {
            get
            {
                return filename;
            }
            set
            {
                filename = value;
            }
        }
        private int version = 1;
        public int Version
        {
            get
            {
                return version;
            }
            set
            {
                version = value;
            }
        }
        private int bpm = 120;
        public int BPM
        {
            get
            {
                return bpm;
            }
            set
            {
                bpm = value;
            }
        }   
        private List<Page> pages;
        public ICollection<Page> OperatorPages
        {
            get
            {
                return pages;
            }
        }
        #endregion

        #region Constructors
        public Project()
        {
            pages = new List<Page>();
        }
        #endregion

        #region Public Methods
        public void Dispose()
        {
            foreach (Page page in pages)
                page.Dispose();
        }
        public XmlElement ToXmlElement(XmlDocument doc)
        {
            XmlElement root = doc.CreateElement("project");
            XmlElement version = doc.CreateElement("version");
            version.InnerText = Version.ToString();
            root.AppendChild(version);
            XmlElement bpm = doc.CreateElement("bpm");
            bpm.InnerText = BPM.ToString();
            root.AppendChild(bpm);

            foreach (Page page in OperatorPages)
            {
                root.AppendChild(page.ToXmlElement(doc));
            }

            return root;
        }
        public void FromXmlElement(XmlElement root)
        {
            foreach (XmlNode node in root.ChildNodes)
            {
                if (node.Name == "version")
                    Version = int.Parse(node.InnerText);
                else if (node.Name == "bpm")
                    BPM = int.Parse(node.InnerText);
                else if (node.Name == "page")
                {
                    Page page = new Page();
                    page.FromXmlElement((XmlElement)node);
                    OperatorPages.Add(page);
                }
            }
        }
        #endregion
    }
}
