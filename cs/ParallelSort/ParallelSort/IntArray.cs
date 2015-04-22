using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ParallelSort
{
    public class IntArray
    {
        private static Random random = new Random();

        private int[] array;

        public IntArray(int size, bool fillWithRandom = false)
        {
            array = new int[size];

            if (fillWithRandom)
            {
                for (int i = 0; i < size; i++)
                {
                    array[i] = random.Next(1000);
                }
            }
        }

        public void print()
        {
            for (int i = 0; i < array.Length; i++)
            {
                Console.Write(array[i] + " ");
            }
            Console.WriteLine();
        }

        public static void print(int[] array)
        {
            for (int i = 0; i < array.Length; i++)
            {
                Console.Write(array[i] + " ");
            }
            Console.WriteLine();
        }

        public void sort(int depth = 0)
        {
            if (depth > 0)
            {
                mergeSort(ref array, depth);
            }
            else
            {
                Array.Sort(array);
            }
        }

        private static void mergeSort(ref int[] whole, int depth)
        {
            if (depth == 0)
            {
                Array.Sort(whole);
            }

            else
            {
                int[] firstHalf = new int[whole.Length / 2];
                int[] secondHalf = new int[whole.Length / 2];
                Array.Copy(whole, 0, firstHalf, 0, whole.Length / 2);
                Array.Copy(whole, whole.Length / 2, secondHalf, 0, whole.Length / 2);


                Task[] tasks = new Task[2];
                tasks[0] = Task.Run(() => mergeSort(ref firstHalf, depth - 1));
                tasks[1] = Task.Run(() => mergeSort(ref secondHalf, depth - 1));
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
                    else if (firstHalf[i] < secondHalf[j])
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
