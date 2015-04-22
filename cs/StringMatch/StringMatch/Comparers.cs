using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StringMatch
{
    public abstract class ComparerBase
    {
        protected string original;
        protected string pattern;
        protected int[] substringArray;

        public ComparerBase(string o, string p, int[] ssA)
        {
            original = o;
            pattern = p;
            substringArray = ssA;
        }

        abstract protected int checkIfValid(int num);

        protected int secureStringCompare(int num)
        {
            if (original.Length - substringArray[num] < pattern.Length)
            {
                if (String.Compare(original.Substring(substringArray[num]), pattern.Substring(0, original.Length - substringArray[num])) <= 0)
                {
                    return -1;
                }
                else
                {
                    return 1;
                }
            }
            else
            {
                return String.Compare(original.Substring(substringArray[num], pattern.Length), pattern);
            }
        }

        public int compare(int num)
        {
            int comp = secureStringCompare(num);
            if (comp != 0)
            {
                return comp;
            }
            else
            {
                return checkIfValid(num);
            }
        }
    }

    public class FirstOccurenceComparer : ComparerBase
    {
        public FirstOccurenceComparer(string o, string p, int[] ssA) : base(o, p, ssA) {}

        protected override int checkIfValid(int num)
        {
            if (num == 0 || secureStringCompare(num - 1) != 0)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
    }

    public class LastOccurenceComparer : ComparerBase
    {
        public LastOccurenceComparer(string o, string p, int[] ssA) : base(o, p, ssA) { }

        protected override int checkIfValid(int num)
        {
            if (num == original.Length - 1 || secureStringCompare(num + 1) != 0)
            {
                return 0;
            }
            else
            {
                return -1;
            }
        }
    }
}
