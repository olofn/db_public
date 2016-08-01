using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace VerkstanEditor.Logic
{
    class LoadOperator: Operator
    {
        #region Properties
        public override Verkstan.Constants.OperatorTypes Type
        {
            get { return Verkstan.Constants.OperatorTypes.Unspecified; }
        }
        public override Verkstan.CoreOperator BindedCoreOperator
        {
            get 
            {
                if (target == null)
                    return null;

                return target.BindedCoreOperator;
            }
        }
        public override bool IsProcessable
        {
            get
            {
                if (target == null)
                    return false;
                return target.IsProcessable;
            }
        }
        public override ICollection<Verkstan.CoreOperatorProperty> Properties
        {
            get
            {
                ICollection<Verkstan.CoreOperatorProperty> properties = new List<Verkstan.CoreOperatorProperty>();
                properties.Add(new Verkstan.CoreOperatorProperty(0, "Target", Verkstan.Constants.OperatorPropertyTypes.String));
                return properties;
            }
        }
        private String typeName;
        public override String TypeName
        {
            get
            {
                return typeName;
            }
        }
        #endregion

        #region Private Variables
        private String targetName;
        private Operator target;
        private Operator.EventHandler stateChangedEventHandler;
        #endregion

        #region Private Static Variables
        private static List<LoadOperator> instances = new List<LoadOperator>();
        #endregion

        #region Constructors
        public LoadOperator()
            : base()
        {
            instances.Add(this);
            typeName = "Load";
            stateChangedEventHandler = new Operator.EventHandler(this.load_StateChanged);
            UniqueName = AllocateUniqueName(TypeName);
        }
        #endregion

        #region Public Methods
        public override List<Operator> GetInputs()
        {
            throw new NotImplementedException();
        }
        public override void Dispose()
        {
            instances.Remove(this);
            base.Dispose();
        }
        public override void OnDisposed(Operator op)
        {
            if (target == op)
            {
                target = null;
                typeName = "Load";
                OnStateChanged();
            }
        }
        public override List<Operator> GetReceiverOperators()
        {
            List<Operator> result = new List<Operator>();
            foreach (Operator receiver in receivers)
                foreach (Operator receiverReceiver in receiver.GetReceiverOperators())
                    result.Add(receiverReceiver);

            return result;
        }
        public override List<Operator> GetSenderOperators()
        {
            if (target == null)
                return new List<Operator>();
            else
                return target.GetSenderOperatorsForLoad();
        }
        public override List<Operator> GetSenderOperatorsForLoad()
        {
            return new List<Operator>();
        }
        public override void StackConnectChangedUpwards()
        {
            if (target != null)
                target.StackConnectChangedUpwards();

            OnStateChanged();
        }
        public override void CascadeStackConnectChangedDownwards()
        {
            foreach (Operator op in receivers)
                op.CascadeStackConnectChangedDownwards();

            foreach (Operator op in loads)
                op.CascadeStackConnectChangedDownwards();

            OnStateChanged();
        }
        public override String GetStringProperty(int index)
        {   
            if (index == 0 && target != null)
                return target.Name;

            return "";   
        }
        public override void SetStringProperty(int index, String value)
        {
            if (index == 0)
            {
                targetName = value;

                Operator newTarget = Operator.Find(value);

                if (newTarget == target)
                    return;

                if (target != null)
                {
                    target.RemoveLoadOperator(this);
                    target.StateChanged -= stateChangedEventHandler;
                }

                target = newTarget;
                if (target != null)
                {
                    typeName = "L<" + target.Name + ">";
                    target.ConnectWithLoadOperator(this);
                    target.StateChanged += stateChangedEventHandler;
                }
                else
                {
                    typeName = "Load";
                }

                CascadeStackConnectChangedDownwards();
            }
        }
        public override XmlElement ToXmlElement(System.Xml.XmlDocument doc)
        {
            XmlElement root = doc.CreateElement("operator");
            root.SetAttribute("type", "Load");

            PopulateXmlElementWithBasicOperatorInformation(root, doc);

            XmlElement target = doc.CreateElement("target");
            target.InnerText = GetStringProperty(0);

            root.AppendChild(target);

            return root;
        }
        public override void FromXmlElement(XmlElement root)
        {
            PopulateOperatorWithBasicXmlElementInformation(root);

            foreach (XmlNode node in root.ChildNodes)
            {
                if (node.Name == "target")
                {
                    XmlElement element = (XmlElement)node;
                    String target = element.InnerText;
                    target.Trim();
                    targetName = target;
                    if (target == "")
                        target = null;
                    SetStringProperty(0, target);
                }
            }
        }
        #endregion

        #region Public Static Methods
        public static void PropagateOnOperatorAdded(Operator op)
        {
            foreach (LoadOperator loadOp in instances)
                loadOp.OnOperatorAdded(op);
        }
        #endregion

        #region Private Methods
        private void OnOperatorAdded(Operator op)
        {
            // Check if this load operator has the operator as target.
            // If so, update the target reference.
            if (op.Name != null && op.Name == targetName)
            {
                SetStringProperty(0, targetName);
                CascadeStackConnectChangedDownwards();
            }
        }
        #endregion

        #region Event Handlers
        void load_StateChanged(Operator.EventArgs e)
        {
            if (e.Operator.Name == null || e.Operator.Name == "")
                target = null;

            if (target != null)
                typeName = "L<" + target.Name + ">";
            else
                typeName = "Load";

            OnStateChanged();
        }
        #endregion
    }
}
