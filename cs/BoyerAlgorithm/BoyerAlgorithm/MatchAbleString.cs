using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BoyerAlgorithm
{
    class MatchAbleString
    {
        private string Str;

        private static int findFirst(Pattern p, string str)
        {
            int i = p.Str.Length - 1;
            while (i < str.Length)
            {
                int j = p.Str.Length - 1;
                for (; j >= 0; j--, i--)
                {
                    if (str[i] != p.Str[j])
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
                    int delta1 = p.Delta1[Convert.ToInt32(str[i])];
                    int delta2 = p.Delta2[j];
                    i += delta1 > delta2 ? delta1 : delta2;
                }
            }
            return -1;
        }

	    private static List<int> matchSubstr(Pattern p, string str, int startPos)
        {
            List<int> occurrences = new List<int>();
	        int occ = 0, next;
	        while ((next = MatchAbleString.findFirst(p, str.Substring(occ))) != -1)
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
	        return MatchAbleString.matchSubstr(p, (i == parts - 1) ? Str.Substring(startPos) : Str.Substring(startPos, length), startPos);
        }

        public MatchAbleString(string s)
        {
            Str = s;
        }

	    public List<int> Match(Pattern p, bool parallel = false)
        {
            int parts = 8;

            List<int>[] occurrencesArray = new List<int>[parts];
    
	        if (!parallel) 
            {
		        for (int i = 0; i < parts; i++)
                {
			        occurrencesArray[i] = matchSubstr(p, parts, i);
		        }
	        }
	        else 
            {
		        // TODO
	        }

	        List<int> occurrences = new List<int>();
	        for (int i = 0; i < parts; i++) {
                occurrences.AddRange(occurrencesArray[i]);
	        }
            return occurrences;
        }
    }
}
