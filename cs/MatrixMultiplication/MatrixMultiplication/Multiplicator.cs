using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MatrixMultiplication
{
    public static class Multiplicator
    {

        //public static Matrix<int> multiply(Matrix<int> a, Matrix<int> b, bool parallel = false)
        //{
        //    Task[] tasks = null;
        //    int size = a.getSize();

        //    Matrix<int> product = new Matrix<int>(size);

        //    if (parallel)
        //    {
        //        tasks = new Task[size * size];
        //    }

        //    for (int i = 0; i < size; i++)
        //    {
        //        for (int j = 0; j < size; j++)
        //        {
        //            if (parallel)
        //            {
        //                int tmpi = i;
        //                int tmpj = j;
        //                tasks[i * size + j] = Task.Run(() => setValue(a, b, tmpi, tmpj, ref product));
        //            }
        //            else
        //            {
        //                for (int k = 0; k < a.getSize(); k++)
        //                {
        //                    product.set(i, j, product.get(i, j) + a.get(i, k) * b.get(k, j));
        //                }
        //            }
        //        }
        //    }

        //    if (parallel)
        //    {
        //        Task.WaitAll(tasks);
        //    }

        //    return product;
        //}

        public static Matrix<int> multiply(Matrix<int> a, Matrix<int> b, bool parallel)
        {
            int size = a.getSize();

            Matrix<int> product = new Matrix<int>(size);

            if (parallel)
            {
                Parallel.For(0, size, i => setValue(a, b, i, product));
            }
            else
            {
                for (int i = 0; i < size; i++)
                {
                    setValue(a, b, i, product);
                }
            }

            return product;
        }

        public static void setValue(Matrix<int> a, Matrix<int> b, int i, Matrix<int> product)
        {
            for (int j = 0; j < a.getSize(); j++)
            {
                for (int k = 0; k < a.getSize(); k++)
                {
                    product.set(i, j, product.get(i, j) + a.get(i, k) * b.get(k, j));
                }
            }
        }

    }
}
