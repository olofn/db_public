using System;
using System.Collections.Generic;
using System.Text;

namespace DB.DoF.Entities
{
    public abstract class PersistentEntity : Entity
    {
        public string GetConstructorString()
        {
            StringBuilder sb = new StringBuilder(this.GetType().Name + "(");
            string[] args = GetConstructorArguments();
            String s = CommaSeparate(args);
            sb.Append(s);

            sb.Append(")");
            return sb.ToString();
        }

        protected abstract string[] GetConstructorArguments();

        protected static string Quote(string s)
        {
            return '"' + s + '"';
        }

        public static string CommaSeparate(string[] args)
        {
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < args.Length; i++)
            {
                if (i != 0)
                {
                    sb.Append(", ");
                }

                sb.Append(args[i]);
            }
            return sb.ToString();
        }
    }
}
