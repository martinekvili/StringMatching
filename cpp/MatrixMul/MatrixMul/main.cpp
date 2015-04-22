#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <windows.h>

#include "matrix.hpp"

using namespace std;

int randInt() {
	return rand() % 100;
}

//template <class T>
//void printMatrix(Matrix<T> &m) {
//	for (int i = 0; i < m.getSize(); i++) {
//		for (int j = 0; j < m.getSize(); j++) {
//			cout << m.get(i, j) << ' ';
//		}
//		cout << endl;
//	}
//}

long measurement(int size, bool parallel) {
	long time = 0;

	cout << "Starting measurement ( " << (parallel ? "parallel" : "non - parallel");
	cout << " algorithm, " << size << " * " << size << " matrices )\n" << endl;

	for (int i = 0; i < 5; i++) {
		Matrix<int> m1(size, true, &randInt);
		Matrix<int> m2(size, true, &randInt);
		Matrix<int> m3(size);

		cout << "Measurement number " << i + 1 << "...";

		long int start = GetTickCount();
		Matrix<int>::multiply(m1, m2, m3, parallel);
		int elapsed = GetTickCount() - start;

		cout << "DONE ( " << elapsed / 1000 << " s " << elapsed % 1000 << " ms )" << endl;

		time += elapsed;
	}

	time /= 5;
	return time;
}

int main(int argc, char** argv)
{
	srand(time(NULL));

	if (argc < 3) {
		return 1;
	}
	int size = 0;
	sscanf(argv[1], "%d", &size);
	bool inFile = strcmp(argv[2], "file") == 0;
	bool first = false;

	if (inFile) {
		first = strcmp(argv[3], "first") == 0;
	}

	long time1 = measurement(size, false);
	cout << "\nMatrix multiplication took " << time1 / 1000 << " seconds, and " << time1 % 1000 << " milliseconds.\n" << endl;

	long time2 = measurement(size, true);
	cout << "\nMatrix multiplication took " << time2 / 1000 << " seconds, and " << time2 % 1000 << " milliseconds." << endl;

	if (inFile) {
		FILE* file = fopen("data.csv", first ? "w" : "a");

		fprintf(file, "%d;%d;%d;\n", size, time1, time2);

		fclose(file);
	}
	
	//printMatrix(m1);
	//cout << endl;
	//printMatrix(m2);
	//cout << endl;
	//printMatrix(m3);
	//  cout << "what" << endl;
	return 0;
}
