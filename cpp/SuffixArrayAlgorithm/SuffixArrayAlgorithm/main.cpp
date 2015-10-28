#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

#include "matchablestring.h"

int measure(const char *orig, const char *pat, bool parallel) {
	std::vector<int> l;

	long int start = GetTickCount();

	for (int i = 0; i < 5; i++) {
		MatchAbleString sm(orig);	
		sm.preprocess(parallel);
		l = sm.match(pat);
	}

	long int elapsed = (GetTickCount() - start) / 5;

	/*std::cout << "Preprocessing took " << elapsed / 1000 << " s " << elapsed % 1000 << " ms" << std::endl;
	std::cout << "Occurrences found: " << l.size() << std::endl;*/

	return elapsed;
}

void measureTextFromFile(int argc, char **argv) {

	std::string path = "..\\resources\\";
	path += argv[1];

	std::ifstream t;
	t.open(path, std::ifstream::binary);      // open input file
	t.seekg(0, t.end);    // go to the end
	int length = (int)t.tellg();           // report location (this is the length)
	t.seekg(0, t.beg);    // go back to the beginning
	char *orig = new char[length + 1];    // allocate memory for a buffer of appropriate dimension
	t.read(orig, length);       // read the whole file into the buffer
	orig[length] = '\0';
	t.close();                    // close file handle

	std::cout << strlen(orig) << ";";

	std::cout << measure(orig, argv[2], false) << ";";
	std::cout << measure(orig, argv[2], true) << std::endl;
	//std::cout << measure(orig, "alrightness", false) << ";";
	//std::cout << measure(orig, "alrightness", true) << std::endl;

	delete[] orig;
}

void measureSimple() {
	std::string  orig = "i had to, Hence, i peed the fence. i don't see the adHence";
	MatchAbleString sm(orig.data());
	sm.preprocess(true);

	std::string pat = "ence";
	std::vector<int> h = sm.match(pat.data());

	for (auto i : h) {
		std::cout << i << " : " << orig.substr(i, pat.length()) << std::endl;
	}

	char c;
	std::cin >> c;
}

int main(int argc, char **argv)
{
	//measureSimple();

	measureTextFromFile(argc, argv);
	
	return 0;
}

