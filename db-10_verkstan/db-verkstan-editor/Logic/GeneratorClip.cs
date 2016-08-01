using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace VerkstanEditor.Logic
{
    public class GeneratorClip: Clip
    {
        #region Properties
        public override ushort Id
        {
            get { return bindedCoreGeneratorClip.Id; }
        }
        #endregion

        #region Private Variables
        private Verkstan.CoreGeneratorClip bindedCoreGeneratorClip;
        #endregion

        #region Constructors
        public GeneratorClip()
        {
            bindedCoreGeneratorClip = new Verkstan.CoreGeneratorClip();
            SetGeneratorType(0);
            SetPeriodInBeats(1);
            SetBindedCoreClip(bindedCoreGeneratorClip);
        }
        #endregion

        #region Public Methods
        public void SetGeneratorType(int type)
        {
            bindedCoreGeneratorClip.SetGeneratorType(type);
            DestroyPreview();
            OnStateChanged();
        }
        public int GetGeneratorType()
        {
            return bindedCoreGeneratorClip.GetGeneratorType();
        }
        public override void Dispose()
        {
            bindedCoreGeneratorClip.Dispose();
        }
        public void SetPeriodInTicks(int period)
        {
            bindedCoreGeneratorClip.SetPeriod(period);
            DestroyPreview();
            OnStateChanged();
        }
        public void SetPeriodInBeats(int period)
        {
            bindedCoreGeneratorClip.SetPeriod(period * Metronome.TicksPerBeat);
            DestroyPreview();
            OnStateChanged();
        }
        public int GetPeriodInTicks()
        {
            return bindedCoreGeneratorClip.GetPeriod();
        }
        public int GetPeriodInBeats()
        {
            return bindedCoreGeneratorClip.GetPeriod() / Metronome.TicksPerBeat;
        }
        public override XmlElement ToXmlElement(XmlDocument doc)
        {
            XmlElement root = doc.CreateElement("clip");
            root.SetAttribute("type", "generator");

            PopulateXmlElementWithBasicClipInformation(root, doc);

            XmlElement generatorTypeElement = doc.CreateElement("generatortype");
            generatorTypeElement.InnerText = GetGeneratorType().ToString();
            root.AppendChild(generatorTypeElement);
            XmlElement periodElement = doc.CreateElement("period");
            periodElement.InnerText = GetPeriodInTicks().ToString();
            root.AppendChild(periodElement);
            return root;
        }
        public override void FromXmlElement(XmlElement root)
        {
            PopulateClipWithBasicInformationFromXmlElement(root);

            foreach (XmlNode node in root.ChildNodes)
            {
                if (node.Name == "generatortype")
                {
                    int type = int.Parse(node.InnerText);
                    SetGeneratorType(type);
                }
                else if (node.Name == "period")
                {
                    int period = int.Parse(node.InnerText);
                    SetPeriodInTicks(period);
                }
            }
        }
        #endregion
    }
}
