using MatchableString.Boyer;
using MatchableString.SuffixArray;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MatchableString
{
    public static class MatchableStrings
    {
        public enum NumberOfMatches
        {
            LessThan1000,
            MoreThan1000
        }

        public static MatchableString CreateBoyer(string s)
        {
            return new MatchableStringB(s);
        }

        public static MatchableString CreateSuffixArray(string s)
        {
            return new MatchableStringSA(s);
        }

        public static MatchableString Create(string s, NumberOfMatches approx)
        {
            switch (approx)
            {
                case NumberOfMatches.LessThan1000:
                    return new MatchableStringB(s);
                case NumberOfMatches.MoreThan1000:
                    return new MatchableStringSA(s);
                default:
                    return null;
            }
        }
    }
}
