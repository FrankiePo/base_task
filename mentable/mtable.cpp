#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include "MTable.h"

using namespace std;

TMend::TMend(istream& stream){
	if(stream.bad()){
		errno = 1;
	}
	else{
		N = 100
		m = new Elem[N];

		while(!stream.eof()){
			int i;
			float b;
			string s;
			stream>>i>>s>>b;

			if(i > N){
				Elem* f = new Elem[i];
				memcpy(f,m,N*sizeof(Elem));
				N = i;
				delete []m;
				m = f;
			}
			if(i > 0){
				m[i-1].setV(s,b,i);
			}
		}
	}
};

Elem* TMend::operator[](int num){
	return (num <= N && num > 0)? m+num-1: NULL;
	};

void TMend::insEl(Elem& el){
	int in = el.getnum();
	if( in <= 0){
		errno = 1;
		return;	
	}	

	if(in > N){
		Elem* f = new Elem[in];
		memcpy(f,m,N*sizeof(Elem));
		N = in;
		delete []m;
		m = f;
	}
	m[in-1].setV(el.getname(),el.getmass(),el.getnum());
	};

Elem* TMend::operator[](string name){
	if(name == ""){
		errno = 1;
		return NULL;
	}
	for(int i = 0; i < N; i++){
		if( m[i].getname() == name){
			return m+i;
		}
	}
	return NULL;
};

void TMend::print(){
	cout << "***************" << endl;
	for(int i = 0; i < N; i++){
		m[i].print();
		}
	cout << "***************" << endl; 
};

