#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

#include "matchablestring.h"

int measure(const char *orig, const char *pat, bool parallel, int num = 0) {
	std::vector<int> l;

	long int start = GetTickCount();

	for (int i = 0; i < 5; i++) {
		MatchAbleString sm(orig);	
		sm.preprocess(parallel);
		l = sm.match(pat);
	}

	long int elapsed = (GetTickCount() - start) / 5;

	std::cout << "Preprocessing took " << elapsed / 1000 << " s " << elapsed % 1000 << " ms" << std::endl;
	std::cout << "Occurrences found: " << l.size() << std::endl;

	return elapsed;
}

void measureTextFromFile(int argc, char **argv) {

	//#if defined _M_IX86
	//	std::string path = "..\\..\\..\\resources\\";
	//#elif defined _M_X64
	//	std::string path = "..\\..\\..\\..\\resources\\";
	//#endif

	//path += argv[1];
	std::string path = "..\\..\\..\\resources\\new\\ulysses.txt";

	std::ifstream t;
	t.open(path, std::ifstream::binary);      // open input file
	t.seekg(0, t.end);    // go to the end
	int length = (int)t.tellg();           // report location (this is the length)

	//std::cout << length << std::endl;

	t.seekg(0, t.beg);    // go back to the beginning
	char *buffer = new char[length + 1];    // allocate memory for a buffer of appropriate dimension
	t.read(buffer, length);       // read the whole file into the buffer
	buffer[length] = '\0';
	t.close();                    // close file handle

	int multiplier = 1;

	size_t tmp = (length + 1) * multiplier + 1;
	char *orig = new char[tmp];
	orig[0] = '\0';
	for (int i = 0; i < multiplier; i++) {
		strcat_s(orig, tmp, buffer);
	}

	std::cout << strlen(orig) << ";";

	/*int num = atoi(argv[3]);
	std::cout << num << ";";*/

	delete[] buffer;

	//std::cout << measure(orig, argv[2], true, num) << std::endl;

	/*std::cout << measure(orig, argv[2], false) << ";";
	std::cout << measure(orig, argv[2], true) << std::endl;*/
	std::cout << measure(orig, "alrightness", false) << ";";
	std::cout << measure(orig, "alrightness", true) << std::endl;

	delete[] orig;

	char c;
	std::cin >> c;
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

