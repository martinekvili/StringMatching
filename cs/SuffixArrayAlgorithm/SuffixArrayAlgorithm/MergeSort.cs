using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SuffixArrayAlgorithm
{
    class MergeSort<T>
    {
        private class Comparer : IComparer<T>
        {
            private Comparator comp;

            public Comparer(Comparator c)
            {
                comp = c;
            }

            public int Compare(T x, T y)
            {
                return comp(x, y);
            }
        }

        private static readonly int mergeTreshold = 1250000;
        private static readonly int sortTreshold = 1250000;

        public delegate int Comparator(T one, T other);

        private static void sequentialMerge(T[] arr1, int start1, int end1, T[] arr2, int start2, int end2, T[] dst, int start_dst, Comparator comp)
        {
            while (start1 != end1 && start2 != end2)
            {
                if (comp(arr1[start1], arr2[start2]) < 0)
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

        private static void swap<U>(ref U one, ref U other)
        {
            U tmp = one;
            one = other;
            other = tmp;
        }

        private static void parallelMerge(T[] arr, int start1, int end1, int start2, int end2, T[] dst, int pos, Comparator comptor, IComparer<T> comparer)
        {
            int length1 = end1 - start1;
            int length2 = end2 - start2;

            if (length1 < length2)
            {
                swap(ref start1, ref start2);
                swap(ref end1, ref end2);
                swap(ref length1, ref length2);
            }

            if (length1 == 0)
            {
                return;
            }

            if ((length1 + length2) < mergeTreshold)
            {
                sequentialMerge(arr, start1, end1, arr, start2, end2, dst, pos, comptor);
            }
            else
            {
                int xpos1 = (start1 + end1) / 2;

                int xpos2 = Array.BinarySearch(arr, start2, end2 - start2, arr[xpos1], comparer);
                xpos2 = xpos2 < 0 ? ~xpos2 : xpos2;     // A dokumentáció szerint így kapjuk meg az első nem kisebb elem indexét. 

                int xpos_dst = pos + (xpos1 - start1) + (xpos2 - start2);

                dst[xpos_dst] = arr[xpos1];

                Parallel.Invoke(
                    () => { parallelMerge(arr, start1, xpos1, start2, xpos2, dst, pos, comptor, comparer); },
                    () => { parallelMerge(arr, xpos1 + 1, end1, xpos2, end2, dst, xpos_dst + 1, comptor, comparer); }
                    );
            }
        }

        static void parallelSort(T[] src, int start, int end, T[] dest, Comparator comptor, IComparer<T> comparer, bool srcToDest = false)
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
                () => { parallelSort(src, start, middle, dest, comptor, comparer, !srcToDest); },
                () => { parallelSort(src, middle, end, dest, comptor, comparer, !srcToDest); }
                );

            if (srcToDest)
            {
                parallelMerge(src, start, middle, middle, end, dest, start, comptor, comparer);
            }
            else
            {
                parallelMerge(dest, start, middle, middle, end, src, start, comptor, comparer);
            }
        }

        public static void ParallelSort(T[] arr, Comparator comptor)
        {
            T[] acc = new T[arr.Length];

            parallelSort(arr, 0, arr.Length, acc, comptor, new Comparer(comptor));
        }


    }
}
