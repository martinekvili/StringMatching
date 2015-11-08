using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MatchableString.Boyer
{
    public class MatchableStringB : MatchableString
    {
        private int findFirst(Pattern p, int startPos, int endPos)
        {
            int i = p.Str.Length - 1;
            while (i < endPos - startPos)
            {
                int j = p.Str.Length - 1;
                for (; j >= 0; j--, i--)
                {
                    if (Str[startPos + i] != p.Str[j])
                    {
                        break;
                    }
                }
                if (j < 0)
                {
                    return i + 1;
                }
                else
                {
                    int delta1 = p.getDelta1(Convert.ToInt32(Str[startPos + i]));
                    int delta2 = p.Delta2[j];
                    i += delta1 > delta2 ? delta1 : delta2;
                }
            }
            return -1;
        }

        private List<int> _matchSubstr(Pattern p, int startPos, int endPos)
        {
            List<int> occurrences = new List<int>();
            int occ = 0, next;
            while ((next = findFirst(p, startPos + occ, endPos)) != -1)
            {
                occ += next;
                occurrences.Add(occ + startPos);
                occ++;
            }
            return occurrences;
        }

        private List<int> matchSubstr(Pattern p, int parts, int i)
        {
            /*
	         * Tehát a szöveget parts darabra bontjuk.
	         * Mindegyik kezdőpontja az i * length / parts, ezek az osztópontok.
	         * Azért hogy meglegyen a megfelelő átfedés, a hossz a length / parts-nál p.getLength() - 1 -gyel hosszabb,
	         * kivéve az utolsó string esetén, ahol viszont a kerekítésekből származó különbséget vesszük hozzá.
	         */
            int startPos = i * Str.Length / parts;
            int length = Str.Length / parts + p.Str.Length - 1;
            return _matchSubstr(p, startPos, (i == parts - 1) ? Str.Length : startPos + length);
        }

        public MatchableStringB(string s) : base(s) { }

        public override List<int> Match(Pattern pattern, bool parallel)
        {
            if (!pattern.IsPreprocessed)
            {
                pattern.PreProcess();
            }

            int parts = 8;

            List<int>[] occurrencesArray = new List<int>[parts];

            if (!parallel)
            {
                for (int i = 0; i < parts; i++)
                {
                    occurrencesArray[i] = matchSubstr(pattern, parts, i);
                }
            }
            else
            {
                // Using parallel for
                Parallel.For(0, parts, i => occurrencesArray[i] = matchSubstr(pattern, parts, i));

                // Using P-LINQ
                //Enumerable.Range(0, parts).AsParallel().ForAll(i => occurrencesArray[i] = matchSubstr(p, parts, i));
            }

            List<int> occurrences = new List<int>();
            for (int i = 0; i < parts; i++)
            {
                occurrences.AddRange(occurrencesArray[i]);
            }
            return occurrences;
        }
    }
}
