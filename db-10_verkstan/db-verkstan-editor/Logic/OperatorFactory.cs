using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace VerkstanEditor.Logic
{
    public class OperatorFactory
    {
        #region Static Methods
        public static Operator Create(String typeName)
        {
            typeName = typeName.ToLower();

            Operator op = null;
            if (typeName == "store")
            {
                op = new StoreOperator();
            }
            else if (typeName == "load")
            {
                op = new LoadOperator();
            }
            else if (typeName == "propagate")
            {
                op = new PropagateOperator();
            }
            else if (typeName == "timeline")
            {
                Verkstan.CoreOperator coreOp = Verkstan.CoreOperatorFactory.Create(typeName);
                op = new CoreOperator(coreOp);
                op.Timeline = new Timeline(op);
            }
            else
            {
                Verkstan.CoreOperator coreOp = Verkstan.CoreOperatorFactory.Create(typeName);
                op = new CoreOperator(coreOp);
            }

            return op;
        }
        public static ICollection<String> GetCategories()
        {
            return Verkstan.CoreOperatorFactory.GetCategories().ToList<String>();
        }
        public static ICollection<String> GetNamesInCategory(String category)
        {
            return Verkstan.CoreOperatorFactory.GetNamesInCategory(category).ToList<String>();
        }
        #endregion
    }
}
