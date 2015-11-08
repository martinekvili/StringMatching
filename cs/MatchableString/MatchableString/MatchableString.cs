using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MatchableString
{
    public abstract class MatchableString
    {
        protected string Str;

        public MatchableString(string s)
        {
            Str = s;
        }

        public virtual void PreProcess(bool parallel) { }

        public abstract List<int> Match(Pattern pattern, bool parallel);
    }
}
