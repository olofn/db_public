using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace VerkstanEditor.Logic
{
    class PropagateOperator: Operator
    {
        #region Properties
        public override Verkstan.CoreOperator BindedCoreOperator
        {
            get 
            {
                List<Operator> senders = GetSenderOperators();
                if (senders.Count == 0)
                    return null;
                else
                    return senders.First().BindedCoreOperator;
            }
        }
        public override Verkstan.Constants.OperatorTypes Type
        {
            get
            {
                return Verkstan.Constants.OperatorTypes.Unspecified;
            }
        }
        public override bool IsProcessable
        {
            get
            {
                if (senders.Count == 0)
                    return false;
                else
                    return senders.First().IsProcessable;
            }
        }
        public override ICollection<Verkstan.CoreOperatorProperty> Properties
        {
            get
            {
                return new List<Verkstan.CoreOperatorProperty>();
            }
        }
        public override String TypeName
        {
            get
            {
                return "Propagate";
            }
        }
        #endregion

        #region Constructors
        public PropagateOperator()
            :base()
        {
            UniqueName = AllocateUniqueName(TypeName);
        }
        #endregion

        #region Public Methods
        public override List<Operator> GetInputs()
        {
            throw new NotImplementedException();
        }
        public override void OnDisposed(Operator op)
        {

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
            List<Operator> result = new List<Operator>();
            foreach (Operator sender in senders)
                foreach (Operator senderSender in sender.GetSenderOperators())
                    result.Add(senderSender);

            return result;
        }
        public override List<Operator> GetSenderOperatorsForLoad()
        {
            List<Operator> result = new List<Operator>();

            foreach (Operator sender in senders)
                foreach (Operator senderSender in sender.GetSenderOperators())
                    result.Add(senderSender);
           
            return result;
        }
        public override void StackConnectChangedUpwards()
        {
            foreach (Operator op in senders)
                op.StackConnectChangedUpwards();

            OnStateChanged();
        }
        public override void CascadeStackConnectChangedDownwards()
        {
            foreach (Operator op in receivers)
                op.CascadeStackConnectChangedDownwards();

            foreach (Operator op in loads)
                op.CascadeStackConnectChangedDownwards();

            IsWarningPresent = senders.Count != 1;
            OnStateChanged();
        }
        public override XmlElement ToXmlElement(XmlDocument doc)
        {
            XmlElement root = doc.CreateElement("operator");
            root.SetAttribute("type", "Propagate");

            PopulateXmlElementWithBasicOperatorInformation(root, doc);

            return root;
        }
        public override void FromXmlElement(XmlElement root)
        {
            PopulateOperatorWithBasicXmlElementInformation(root);
        }
        #endregion
    }
}
