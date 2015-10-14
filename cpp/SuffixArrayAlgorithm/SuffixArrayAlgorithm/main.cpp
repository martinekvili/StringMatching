#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

#include "matchablestring.h"

int measure(const char *orig, const char *pat, bool parallel, int num = 0) {
	long int start;
	int elapsed = 0;

	//std::vector<char*> l;

	for (int i = 0; i < 5; i++) {
		MatchAbleString sm(orig);

		start = GetTickCount();
		sm.preprocess(parallel);
		elapsed += GetTickCount() - start;

		//for (int j = 0; j < num; j++) {
		//	start = GetTickCount();
		//	/*l = */sm.match(pat);
		//	elapsed += GetTickCount() - start;
		//}

	}
	/*std::cout << "Preprocessing took " << elapsed / 1000 << " s " << elapsed % 1000 << " ms\n" << std::endl;*/

	//std::cout << l.size() << std::endl;
	return elapsed / 5;
}

void measureTextFromFile(int argc, char **argv) {

	#if defined _M_IX86
		std::string path = "..\\..\\..\\resources\\";
	#elif defined _M_X64
		std::string path = "..\\..\\..\\..\\resources\\";
	#endif

	path += argv[1];
	//std::string path = "..\\..\\..\\resources\\spacewrecked.txt";

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

	size_t tmp = (length + 1) * 4 + 1;
	char *orig = new char[tmp];
	orig[0] = '\0';
	for (int i = 0; i < 4; i++) {
		strcat_s(orig, tmp, buffer);
	}

	std::cout << strlen(orig) << ";";

	/*int num = atoi(argv[3]);
	std::cout << num << ";";*/

	delete[] buffer;

	//std::cout << measure(orig, argv[2], true, num) << std::endl;

	/*std::cout << measure(orig, argv[2], false) << ";";
	std::cout << measure(orig, argv[2], true) << std::endl;*/
	std::cout << measure(orig, "bla", false) << ";";
	std::cout << measure(orig, "bla", true) << std::endl;

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

