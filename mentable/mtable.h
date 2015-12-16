#include <iostream>
#include <cstdlib>
#include <string>
#include "Element.h"

using namespace std;

class TMend{
	Elem* m;
	int N;
	public:
		TMend(istream&);
		Elem* operator[](int);
		void insEl(Elem&);
		Elem* operator[](string);
		void print();
};
