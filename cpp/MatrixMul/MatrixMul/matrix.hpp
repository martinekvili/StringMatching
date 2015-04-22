#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED

#include "tbb\parallel_for.h"
#include "tbb\blocked_range.h"

template <class T>
class Matrix {

	T *matrix;
	size_t size;

	Matrix(const Matrix<T> &other);

	Matrix<T> & operator= (const Matrix<T> &other);

public:

	Matrix(size_t size, bool fillWithRandom = false, T(*getRandom)() = NULL) {
		this->size = size;

		matrix = new T[size * size];

		if (fillWithRandom && getRandom != NULL)
		{
			for (size_t i = 0; i < size; i++)
			{
				for (size_t j = 0; j < size; j++)
				{
					matrix[i * size + j] = getRandom();
				}
			}
		}
	}

	size_t getSize() const {
		return size;
	}

	T get(int i, int j) const {
		return matrix[i * size + j];
	}

	void set(int i, int j, T e) {
		matrix[i * size + j] = e;
	}

	static void multiply(Matrix<T> &a, Matrix<T> &b, Matrix<T> &product, bool parallel)
	{
		if (!parallel) {
			for (size_t i = 0; i < a.getSize(); i++)
			{
				setValue(a, b, i, product);
			}
		}
		else {
			tbb::parallel_for(tbb::blocked_range<size_t>(0, a.getSize()), ValueSetter(a, b, product));
		}	
	}

	class ValueSetter {
		Matrix<T> &a, &b, &product;
	public:
		void operator()(const tbb::blocked_range<size_t>& r) const {
			for (size_t i = r.begin(); i != r.end(); i++) {
				setValue(a, b, i, product);
			}	
		}
		ValueSetter(Matrix<T> &a, Matrix<T> &b, Matrix<T> &product) :
			a(a), b(b), product(product)
		{}
	};

	static void setValue(Matrix<T> &a, Matrix<T> &b, size_t i, Matrix<T> &product) {
		for (size_t j = 0; j < a.getSize(); j++)
		{
			for (size_t k = 0; k < a.getSize(); k++)
			{
				product.set(i, j, product.get(i, j) + a.get(i, k) * b.get(k, j));
			}
		}
	}

	~Matrix() {
		delete matrix;
	}

};

#endif // MATRIX_HPP_INCLUDED
