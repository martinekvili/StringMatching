using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StringMatch
{
    public class MyStringComparer : IComparer<int>
    {
        private string original;
        private int length;
        private int[] substringArray;

        public MyStringComparer(string original, int[] array)
        {
            this.original = original;
            length = original.Length;
            this.substringArray = array;
        }

        private int getCharNum(char ch)
        {
            ch = Char.ToLower(ch);
            if ('a' <= ch && ch <= 'z')
            {
                return ch - 'a';
            }
            else
            {
                return 'z' - 'a' + 1;
            }
        }

        //private int getCharNum(char ch)
        //{
        //    switch (Char.ToLower(ch))
        //    {
        //        case 'a':
        //        case 'á':
        //            return 0;
        //        case 'b':
        //            return 1;
        //        case 'c':
        //            return 2;
        //        case 'd':
        //            return 3;
        //        case 'e':
        //        case 'é':
        //            return 4;
        //        case 'f':
        //            return 5;
        //        case 'g':
        //            return 6;
        //        case 'h':
        //            return 7;
        //        case 'i':
        //        case 'í':
        //            return 8;
        //        case 'j':
        //            return 9;
        //        case 'k':
        //            return 10;
        //        case 'l':
        //            return 11;
        //        case 'm':
        //            return 12;
        //        case 'n':
        //            return 13;
        //        case 'o':
        //        case 'ó':
        //        case 'ö':
        //        case 'ő':
        //            return 14;
        //        case 'p':
        //            return 15;
        //        case 'q':
        //            return 16;
        //        case 'r':
        //            return 17;
        //        case 's':
        //            return 18;
        //        case 't':
        //            return 19;
        //        case 'u':
        //        case 'ú':
        //        case 'ü':
        //        case 'ű':
        //            return 20;
        //        case 'v':
        //            return 21;
        //        case 'w':
        //            return 22;
        //        case 'x':
        //            return 23;
        //        case 'y':
        //            return 24;
        //        case 'z':
        //            return 25;
        //        default:
        //            return 26;
        //    }
        //}

        //private int compareStrings(string one, string other)
        //{
        //    int i = 0;
        //    while (i < one.Length && i < other.Length)
        //    {
        //        int diff = getCharNum(one[i]) - getCharNum(other[i]);
        //        if (diff < 0)
        //        {
        //            return -1;
        //        }
        //        else if (diff > 0)
        //        {
        //            return 1;
        //        }
        //        else
        //        {
        //            i++;
        //        }
        //    }

        //    if (i == one.Length && i < other.Length)
        //    {
        //        return -1;
        //    }
        //    else if (i < one.Length & i == other.Length) {
        //        return 1;
        //    }
        //    else
        //    {
        //        return 0;
        //    }
        //}

        private unsafe int compareSubstrings(int x, int y)
        {
            fixed (char* start = original)
            {
                char* one = start + x;
                char* other = start + y;

                while (x < length && y < length)
                {
                    int diff = getCharNum(*one) - getCharNum(*other);
                    if (diff < 0)
                    {
                        return -1;
                    }
                    else if (diff > 0)
                    {
                        return 1;
                    }
                    else
                    {
                        x++;
                        y++;
                        one++;
                        other++;
                    }
                }

                if (x == length && y < length)
                {
                    return -1;
                }
                else if (x < length && y == length)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
        }

        public int Compare(int x, int y)
        {
            //return compareStrings(original.Substring(x), original.Substring(y));
            return compareSubstrings(x, y);
        }
    }
}
