using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StringMatch
{
    public static class ArraySorter
    {
        public static void sort(int[] array, string original, IComparer<int> comp, int depth = 0)
        {
            if (depth > 0)
            {
                mergeSort(array, original, depth, comp);
            }
            else
            {
                Array.Sort(array, comp);
            }
        }

        private static void mergeSort(int[] whole, string original, int depth, IComparer<int> comp)
        {
            //IComparer<int> comp = new MyStringComparer(original, whole);

            if (depth == 0)
            {
                Array.Sort(whole, comp);
            }

            else
            {
                int[] firstHalf = new int[whole.Length / 2];
                int[] secondHalf = new int[whole.Length / 2];
                Array.Copy(whole, 0, firstHalf, 0, whole.Length / 2);
                Array.Copy(whole, whole.Length / 2, secondHalf, 0, whole.Length / 2);


                Task[] tasks = new Task[2];
                tasks[0] = Task.Run(() => mergeSort(firstHalf, original, depth - 1, comp));
                tasks[1] = Task.Run(() => mergeSort(secondHalf, original, depth - 1, comp));
                Task.WaitAll(tasks);

                int i = 0, j = 0, k = 0;
                while (i < firstHalf.Length || j < secondHalf.Length)
                {
                    if (i == firstHalf.Length)
                    {
                        whole[k] = secondHalf[j++];
                    }
                    else if (j == secondHalf.Length)
                    {
                        whole[k] = firstHalf[i++];
                    }
                    else if (comp.Compare(firstHalf[i], secondHalf[j]) < 0)
                    {
                        whole[k] = firstHalf[i++];
                    }
                    else
                    {
                        whole[k] = secondHalf[j++];
                    }
                    k++;
                }
            }
        }

    }
}
