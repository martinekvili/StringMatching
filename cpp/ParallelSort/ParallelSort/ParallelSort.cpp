#include <iostream>
#include <Windows.h>

#include "IntArray.h"

using namespace std;

long measurement(int size, int depth, bool verbose) {
	long time = 0;

	if (verbose) {
		cout << "Starting measurement ( ";
		if (depth == 0) {
			cout << "non - parallel";
		}
		else {
			cout << "parallel - " << pow(2, depth) << " pieces";
		}
		cout << " algorithm, size of the array: " << (double)size / 1000000 << " M )\n" << endl;
	}
	

	for (int i = 0; i < 5; i++) {
		IntArray a(size, true);

		if (verbose) {
			cout << "Measurement number " << i + 1 << "...";
		}

		long int start = GetTickCount();
		a.sort(depth);
		int elapsed = GetTickCount() - start;

		if (verbose) {
			cout << "DONE ( " << elapsed / 1000 << " s " << elapsed % 1000 << " ms )" << endl;
		}

		time += elapsed;
	}

	time /= 5;
	return time;
}

int main(int argc, char** argv) {
	IntArray::init();

	if (argc < 2) {
		return 1;
	}
	int size = 0;
	sscanf(argv[1], "%d", &size);
	bool verbose = (argc >= 3 && strcmp(argv[2], "-v") == 0);

	long times[7];

	for (int i = 0; i < 7; i++) {
		times[i] = measurement(size, i, verbose);
		if (verbose) {
			cout << "\nSorting took on average " << times[i] / 1000 << " seconds, and " << times[i] % 1000 << " milliseconds.\n" << endl;
		}
	}

	if (!verbose) {
		cout << (double)size / 1000000 << ";";
		for (int i = 0; i < 7; i++) {
			cout << times[i] << ";";
		}
		cout << endl;
	}
	
	return 0;
}

