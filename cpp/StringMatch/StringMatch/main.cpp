// StringMatch.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <Windows.h>

#include "StringMatch.h"

int measure(char *orig, bool parallel) {
	long int start;
	int elapsed = 0;

	for (int i = 0; i < 5; i++) {
		StringMatch sm(orig);

		start = GetTickCount();
		sm.preprocess(parallel);
		elapsed += GetTickCount() - start;

		//std::cout << "Preprocessing took " << elapsed / 1000 << " s " << elapsed % 1000 << " ms\n" << std::endl;
	}
	
	return elapsed / 5;
}

int main(int argc, char **argv)
{
	//const char orig[] = "CGATATATCGG";
	std::ifstream t;
	int length;
	t.open(argv[1], std::ofstream::in);      // open input file
	t.seekg(0, std::ios::end);    // go to the end
	length = t.tellg();           // report location (this is the length)
	t.seekg(0, std::ios::beg);    // go back to the beginning
	char *buffer = new char[length];    // allocate memory for a buffer of appropriate dimension
	t.read(buffer, length);       // read the whole file into the buffer
	t.close();                    // close file handle


	char *orig = new char[strlen(buffer) * 4 + 1];
	orig[0] = '\0';
	for (int i = 0; i < 4; i++) {
		strcat(orig, buffer);
	}

	std::cout << strlen(orig) << ";";

	delete[] buffer;

	std::cout << measure(orig, false) << ";" << measure(orig, true) << std::endl;

	delete[] orig;

	//sm.print();


	/*start = GetTickCount();
	std::vector<char*> h = sm.match("commit");
	elapsed = GetTickCount() - start;

	std::cout << "Matching took " << elapsed / 1000 << " s " << elapsed % 1000 << " ms\n" << std::endl;

	std::cout << h.size() << " matches found." << ::std::endl;*/

	/*if (h.size() != 0) {
		for (int i = 0; i < h.size(); i++) {
			std::cout << h[i] << std::endl;
		}
	}
	else {
		std::cout << "No matches found." << std::endl;
	}*/

	//std::cout << strncmp("GATGTAG", "G", 1) << std::endl;
	
	return 0;
}

