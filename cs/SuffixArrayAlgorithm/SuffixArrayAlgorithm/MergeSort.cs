using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SuffixArrayAlgorithm
{
    public class MergeSort
    {
        public class Comparer : IComparer<int>
        {
            private string str;

            public Comparer(string s)
            {
                str = s;
            }

            public int Compare(int x, int y)
            {
                return String.Compare(str, x, str, y, str.Length);
            }
        }

        private static readonly int mergeTreshold = 8192;
        private static readonly int sortTreshold = 48;

        private static void sequentialMerge(int[] arr1, int start1, int end1, int[] arr2, int start2, int end2, int[] dst, int start_dst, IComparer<int> comp)
        {
            while (start1 != end1 && start2 != end2)
            {
                if (comp.Compare(arr1[start1], arr2[start2]) < 0)
                {
                    dst[start_dst] = arr1[start1];
                    start1++;
                }
                else
                {
                    dst[start_dst] = arr2[start2];
                    start2++;
                }
                start_dst++;
            }

            while (start1 != end1)
            {
                dst[start_dst] = arr1[start1];
                start1++;
                start_dst++;
            }

            while (start2 != end2)
            {
                dst[start_dst] = arr2[start2];
                start2++;
                start_dst++;
            }
        }

        private static void swapInt(ref int one, ref int other)
        {
            int tmp = one;
            one = other;
            other = tmp;
        }

        private static void parallelMerge(int[] arr, int start1, int end1, int start2, int end2, int[] dst, int pos, IComparer<int> comparer)
        {
            int length1 = end1 - start1;
            int length2 = end2 - start2;

            if (length1 < length2)
            {
                swapInt(ref start1, ref start2);
                swapInt(ref end1, ref end2);
                swapInt(ref length1, ref length2);
            }

            if (length1 == 0)
            {
                return;
            }

            if ((length1 + length2) < mergeTreshold)
            {
                sequentialMerge(arr, start1, end1, arr, start2, end2, dst, pos, comparer);
            }
            else
            {
                int xpos1 = (start1 + end1) / 2;

                int xpos2 = Array.BinarySearch(arr, start2, end2 - start2, arr[xpos1], comparer);
                xpos2 = xpos2 < 0 ? ~xpos2 : xpos2;     // A dokumentáció szerint így kapjuk meg az első nem kisebb elem indexét. 

                int xpos_dst = pos + (xpos1 - start1) + (xpos2 - start2);

                dst[xpos_dst] = arr[xpos1];

                Parallel.Invoke(
                    () => { parallelMerge(arr, start1, xpos1, start2, xpos2, dst, pos, comparer); },
                    () => { parallelMerge(arr, xpos1 + 1, end1, xpos2, end2, dst, xpos_dst + 1, comparer); }
                    );
            }
        }

        static void parallelSort(int[] src, int start, int end, int[] dest, IComparer<int> comparer, bool srcToDest = false)
        {
            if (start == end)
            {
                return;
            }

            if ((end - start) < sortTreshold)
            {
                Array.Sort(src, start, end - start, comparer);

                if (srcToDest)
                {
                    for (int i = start; i < end; i++)
                    {
                        dest[i] = src[i];
                    }
                }

                return;
            }

            int middle = (start + end) / 2;
            Parallel.Invoke(
                () => { parallelSort(src, start, middle, dest, comparer, !srcToDest); },
                () => { parallelSort(src, middle, end, dest, comparer, !srcToDest); }
                );

            if (srcToDest)
            {
                parallelMerge(src, start, middle, middle, end, dest, start, comparer);
            }
            else
            {
                parallelMerge(dest, start, middle, middle, end, src, start, comparer);
            }
        }

        public static void ParallelSort(int[] arr, IComparer<int> comparer)
        {
            int[] acc = new int[arr.Length];

            parallelSort(arr, 0, arr.Length, acc, comparer);
        }


    }
}
