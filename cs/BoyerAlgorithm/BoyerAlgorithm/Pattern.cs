﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BoyerAlgorithm
{
    class Pattern
    {
        public int[] Delta1 { get; private set; }
        public int[] Delta2 { get; private set; }

        public string Str { get; private set; }

        private void fillDelta1()
        {
            for (int i = 0; i < 256; i++)
            {
                Delta1[i] = Str.Length;
            }

            for (int i = Str.Length - 1; i >= 0; i--)
            {
                if (Delta1[Convert.ToInt32(Str[i])] == Str.Length)
                {
                    Delta1[Convert.ToInt32(Str[i])] = i;
                }
            }

            for (int i = 0; i < 256; i++)
            {
                if (Delta1[i] != Str.Length)
                {
                    Delta1[i] = Str.Length - 1 - Delta1[i];
                }
            }
        }

        private int rpr(int i)
        {
            int subPatternLength = Str.Length - i - 1;

            int j = i - 1;
            for (; j >= -subPatternLength; j--)
            {
                if (j >= 0)
                {
                    if (string.Compare(Str, j, Str, i + 1, subPatternLength) == 0)
                    {
                        if (j == 0 || Str[j - 1] != Str[i])
                        {
                            break;
                        }
                    }
                }
                else
                {
                    if (string.Compare(Str, 0, Str, i + 1 - j, subPatternLength + j) == 0)
                    {
                        break;
                    }
                }
            }

            return j;
        }

        private void fillDelta2()
        {
            Delta2[Str.Length - 1] = 1;
            for (int i = Str.Length - 2; i >= 0; i--)
            {
                Delta2[i] = Str.Length - rpr(i);
            }
        }

        public Pattern(string str)
        {
            Str = str;

            Delta1 = new int[256];
            Delta2 = new int[Str.Length];
        }

        public void PreProcess()
        {
            fillDelta1();
            fillDelta2();
        }
    }
}