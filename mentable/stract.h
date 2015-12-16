#include "mtable.h"

class Struct{
	int* f_count;
	int* f_place;
	int f_num;

	Elem* cont;
	Struct* child;

	void load(String);
	String* findDefinedNime(String);
	public:
		Struct();
		void setString(String);
		void setChild(String, int);
		int findChild(String);
		Struct* operator[](String);
		Struct* operator[](int);
		void print();
		~Struct();
	}
