#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <string>

using namespace std;

#define nondef -111

class Elem{
	string name;
	float mass;
	int num;
	public:
		Elem();
		void setV(string,float,int);
		float getmass();
		string getname();
		int getnum();
		void print();
		};	
