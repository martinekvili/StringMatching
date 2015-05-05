#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>

#include "matchablestring.h"

//int main()
//{
//	const char *s = "i had to, Hence, i peed the fence. i don't see the adHence";
//	const char *pat = "ence";
//	MatchAbleString str(s);
//    Pattern p(pat);
//    p.preprocess();
//
//	std::vector<int> l = str.match(p, true);
//	size_t patlen = strlen(pat);
//	char *tmp = new char[patlen + 1];
//	for (std::vector<int>::iterator p = l.begin(); p != l.end(); p++) {
//		strncpy_s(tmp, patlen + 1, s + *p, patlen);
//		std::cout << *p << " : '" << tmp << "'" << std::endl;
//	}
//	delete[] tmp;
//
//	char c;
//	std::cin >> c;
//   
//	
//	/*for (int c = 0; c < 256; c++) {
//        if (p.getDelta1(c) != p.getLength()) {
//            std::cout << (char)c << " (" << c << ") : " << p.getDelta1(c) << std::endl;
//        }
//    }
//    std::cout << std::endl;*/
//   /* for (size_t i = 0; i < p.getLength(); i++) {
//        std::cout << p.getDelta2(i) << ' ';
//    }
//    std::cout << std::endl;
//
//    Pattern p("AT");
//    const char *c = "WHICH FINALLY HALTS.  AT THAT POINT";
//    MatchAbleString s(c);
//
//    std::list<int> m = s.match(p);
//    for (typename std::list<int>::iterator p = m.begin(); p != m.end(); p++) {
//        std::cout << *p << " : '" << c + *p << "'" << std::endl;
//    }*/
//
//    return 0;
//}

int measure(const char *orig, const char *pat, bool parallel, int num) {
	long int start;
	int elapsed = 0;
	std::vector<int> l;

	MatchAbleString str(orig);

	for (int i = 0; i < 5 * num; i++) {
		Pattern p(pat);

		start = GetTickCount();
		p.preprocess();
		l = str.match(p, parallel);
		elapsed += GetTickCount() - start;

		//std::cout << "Matching took " << elapsed / 1000 << " s " << elapsed % 1000 << " ms" << std::endl;
		//std::cout << "Found " << l.size() << " occurrences." << std::endl;
	/*	char *szo = new char[strlen(pat) + 1];
		strncpy(szo, orig + l.front(), strlen(pat));
		szo[strlen(pat)] = '\0';
		std::cout << l.front() << ": " << szo << "\n" <<std::endl;
		delete[] szo;*/
	}

	//std::cout << (parallel ? "Parallel" : "Single thread") << " matching took " << elapsed / 1000 << " s " << elapsed % 1000 << " ms" << std::endl;
	//std::cout << "Found " << l.size() << " matches." << std::endl;
	/*for (int i = 0; i < l.size(); i++) {
		std::cout << l[i] << " ";
	}
	std::cout << std::endl;*/
	return elapsed / 5;
}

int main(int argc, char **argv)
{
#if defined _M_IX86
	std::string path = "..\\..\\..\\resources\\";
#elif defined _M_X64
	std::string path = "..\\..\\..\\..\\resources\\";
#endif

	path += argv[1];

	std::ifstream t;
	t.open(path, std::ifstream::binary);      // open input file
	t.seekg(0, t.end);    // go to the end
	int length = t.tellg();           // report location (this is the length)

	//std::cout << length << std::endl;

	t.seekg(0, t.beg);    // go back to the beginning
	char *buffer = new char[length + 1];    // allocate memory for a buffer of appropriate dimension
	t.read(buffer, length);       // read the whole file into the buffer
	buffer[length] = '\0';
	t.close();                    // close file handle

	/*int i = 1;
	for (char *c = buffer; *c != '\0'; c++, i++) {
		std::cout << i << ". " << (int)*c << ": " << *c << std::endl;
	}*/

	 
    //const char *buffer = "i had to, Hence, i peed the fence. i don't see the adHence ";
	//size_t length = strlen(buffer);

	size_t tmp = (length + 1) * 4 + 1;
	char *orig = new char[tmp];
	orig[0] = '\0';
	for (int i = 0; i < 4; i++) {
		strcat_s(orig, tmp, buffer);
	}

	delete[] buffer;

	std::cout << strlen(orig) << ";";

	int num = atoi(argv[3]);
	std::cout << num << ";";

	//std::cout << measure(orig, argv[2], false) << ";";
	std::cout << measure(orig, argv[2], true, num) << std::endl;

	delete[] orig;

	/*char c;
	std::cin >> c;*/

	/*if (c == 'w') {
		std::ofstream fil;
		fil.open("bla.txt", std::ios_base::out);
		fil << orig;
		fil.close();
	}*/

	return 0;
}
