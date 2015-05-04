// StringMatch.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <string>
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

	#if defined _M_IX86
		std::string path = "..\\..\\..\\resources\\";
	#elif defined _M_X64
		std::string path = "..\\..\\..\\..\\resources\\";
	#endif

	path += argv[1];

	std::ifstream t;
	int length;
	t.open(path, std::ofstream::in);      // open input file
	t.seekg(0, std::ios::end);    // go to the end
	length = t.tellg();           // report location (this is the length)
	t.seekg(0, std::ios::beg);    // go back to the beginning
	char *buffer = new char[length];    // allocate memory for a buffer of appropriate dimension
	t.read(buffer, length);       // read the whole file into the buffer
	t.close();                    // close file handle

	size_t tmp = strlen(buffer) * 4 + 1;
	char *orig = new char[tmp];
	orig[0] = '\0';
	for (int i = 0; i < 4; i++) {
		strcat_s(orig, tmp, buffer);
	}

	std::cout << strlen(orig) << ";";

	delete[] buffer;

	std::cout << measure(orig, false) << ";" << measure(orig, true) << std::endl;

	delete[] orig;

	//sm.print();

	//const char orig[] = "CGATATATCGG";
	//StringMatch sm(orig);
	//sm.preprocess();
	//std::vector<char*> h = sm.match("TATA");
	//for (int i = 0; i < h.size(); i++) {
	//	std::cout << h[i] << std::endl;
	//}

	/*char c;
	std::cin >> c;*/


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

