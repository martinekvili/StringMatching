using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MatrixMultiplication
{
    public class Matrix<T>
    {
        public delegate T GetRandom();

        protected T[][] matrix;

        public Matrix(int size, bool fillWithRandom = false, GetRandom getRandom = null)
        {
            matrix = new T[size][];
            for (int i = 0; i < size; i++)
            {
                matrix[i] = new T[size];
            }

                if (fillWithRandom && getRandom != null)
                {
                    for (int i = 0; i < size; i++)
                    {
                        for (int j = 0; j < size; j++)
                        {
                            matrix[i][j] = getRandom();
                        }
                    }
                }
        }

        public int getSize()
        {
            return matrix.GetLength(0);
        }

        public T get(int i, int j)
        {
                return matrix[i][j];
            
        }

        public void set(int i, int j, T e)
        {
                matrix[i][j] = e;
        }
    }
}
