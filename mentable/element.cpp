#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include "Element.h"

using namespace std;

Elem::Elem(){
	mass = nondef;
	num = nondef;
	};
void Elem::setV( string n, float ms, int nm){
	if(ms < 0 || nm <= 0){
		errno = 1;
		return;	
		}
	name = n;
	mass = ms;
	num = nm;
	};
float Elem::getmass(){
	return mass;
	};
string Elem::getname(){
	return name;
	};
int Elem::getnum(){
	return num;
	};
void Elem::print(){
	cout << num << " " << name << " " << mass << endl; 		};		
