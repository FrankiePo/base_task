#include <iostream>
#include <cstdlib>
#include <string>
#include <stdlib.h>
#include <set>

using namespace std;

class Word:public string{
	int nbk;
	int count();
	void sort();
	string delete_char_after(string, char, size_t);
	int delete_string_after(string, size_t);
	string operator+(int);

public:
	Word();
	Word(string&);
	Word(char*);
	Word(char);

	Word* operator=(string);
	Word* operator=(const char*);
	Word* operator=(char);

	Word operator*(int);
	Word operator!();
	Word operator/(int);

	Word operator&&(Word&);
	Word operator-(Word&);
	void instead(Word&,Word&);

	int getLet();
	size_t clear_spaces(size_t);
	void compress();
};

//********************************************************

Word::Word()
{
	nbk = 0;
}


Word::Word(string& a):string(a)
{
	nbk = count();
}


Word::Word(char* a):string(a)
{
	nbk = count();
}


Word::Word(char a)
{
	(*((string*)this)) = a;
	nbk = 1;
}


int Word::getLet()
{
	return nbk;
}


string Word::delete_char_after(string s, char c, size_t k)
{
	size_t i = k;
	k = s.find(c, i + 1);
	while(k != string::npos) {
		s = s.substr(0, k) + s.substr(k + 1);
		i = k;
		k = s.find(c, i);
	}
	return s;
}


int Word::delete_string_after(string c, size_t k)
{
	size_t i = k, count = 0;
	k = find(c, i);

	while(k != string::npos) {
		*this = substr(0, k) + substr(k + 1);
		i = k;
		k = find(c, i);
		count++;
	}
	return count;
}


int Word::count()
{
	size_t k = 0;
	string s =(*((string *)this));
	while(k < s.length()){
		char c = s[k];
		s = delete_char_after(s, c, k);
		k++;
	}
	return k;
}


Word* Word::operator=(string a)
{
	(*((string*)this)) = string::operator=(a);
	nbk = count();
	return this;
}


Word* Word::operator=(const char* a){
	(*((string*)this)) = string::operator=(a);
	nbk = count();
	return this;
}


Word* Word::operator=(char a)
{
	(*((string*)this)) = string::operator=(a);
	nbk = 1;
	return this;
}


int cmp(const void* a, const void* b)
{
	return *(char*)a - *(char*)b;
}


void Word::sort(){
	qsort( (void*)(*(string*)this).data(),
		   (*(string*)this).length(),
		   sizeof(char), cmp);
}


/* find and return equal symbols */
Word Word::operator&&(Word& a)
{
	string s;
	for(size_t i = 0; i < (*this).length(); i++) {
		char c = (*this)[i];
		if(a.find(c) != string::npos && s.find(c) == string::npos) {
			s += c;
		}
	}
	Word res = s;
	res.sort();
	return res;
}


Word Word::operator-(Word& a)
{
	size_t k = 0;
	string s = (*((string *)this));
	string l = s;
	Word res = (*this)&&a;

	while( k < a.length()) {
		s = delete_char_after(s, a[k], string::npos);
		k++;
	}
	*this = s;

	k = 0;
	while( k < l.length()) {
		a = delete_char_after(a, l[k], string::npos);
		k++;
	}
	a.count();
	count();

	return res;
}


Word Word::operator*(int a)
{
	string l = (*((string *)this));
	string s = "";
	for(int i = 0 ; i < a; i++)
		s += l;
	Word res = s;
	return res;
}


Word Word::operator/(int a)
{
	string s;
	size_t i = 1;
	int count;
	while( i < length() + 1) {
		s = substr(0, i);
		count = 1;
		size_t k, l = i;
		while( (k = find(s, l)) != string::npos) {
			if(k -l != 0) {
				break;
			}
			count++;
			l += i;
		}
		if ((int) count == a) {
			break;
		}
		i++;
	}
	Word res = s;
	return res;
}


Word Word::operator!()
{
	Word res = *this;
	size_t max = res.length();
	for(size_t i = 0; i < max; i++)
		res[i] = at(max - 1 - i);
	return res;
}


void Word::instead(Word& a, Word& b)
{
	size_t i = 0;
	string s = *((string*)this);
	while(i < s.length()){
		char c = s.at(i);
		if(a.find(c) == string::npos) {
			i++;
			continue;
		}
		s = s.substr(0,i)+b+s.substr(i+1);
		i += b.length();
	}
	*this = s;
}


/* clear double spaces */
size_t Word::clear_spaces(size_t i)
{
	size_t st = i;
	char c = at(i);
	while( c == ' ') {
		i++;
		c = at(i);
	}

	if (c >= 'a' && c <= 'z')
		*this = substr(0, st + 1) + substr(i);
	else if (c >= 'A' && c <= 'Z')
		*this = substr(0, st + 1) + substr(i);
	else if (c >= '0' && c <= '9')
		*this = substr(0, st + 1) + substr(i);
	else
		*this = substr(0,st) + substr(i);
	st++;
	return st;
}


string Word::operator+(int a)
{
	string s;
	while( a != 0) {
		char k = a % 10 + '0';
		a = a / 10;
		Word s1 = k;
		s = s1 + s;
	}
	s = s + "(" + *this + ")";
	return s;
}


bool freeP(char* a, int st, int n)
{
	for(int i = 0; i < n; i++) {
		if(a[st+i])
			return false;
	}
	return true;
}


void changeSt(char* a, int n, string s, string sub)
{
	int ind, i = 0;
	while((ind = s.find(sub,i)) >= 0) {
		for(size_t k = 0; k < sub.length(); k++) {
			a[ind + k] = 1;
		}
		i = ind + sub.length();
	}
}


void Word::compress()
{
	string s;
	int n = (*this).length();
	char* a = new char[n];
	for(int i = 0; i < n; i++) {
		a[i] = 0;
	}

	for(int st = 0; st < n; st++){
		if(a[st]){
			continue;
		}
		for(int i = st+2; i < n; i++){
			if( i != n - 1){
				string sub = substr(st,i+1-st);
				int ind = find(sub,i+1);
				if(ind >= 0 && (freeP(a,ind,i-st+1))){
						continue;
				}
			}

			string s1 = substr(st,i-st);
			Word sub = s1;

			int ind = find(sub,i);
			if(!(freeP(a,ind,i-st))) {
	continue;
			}

			int count = 1;
			while(ind >= 0){
				if(freeP(a,ind,i-st)){
					count++;
				}
				ind = find(sub,ind+i-st);
			}
			changeSt(a,n,(*this),s1);
			if(count){
				sub = sub + count;
				s = sub + s;
				}
			break;
			}
		}

	for(int i = 0; i < n; i++){
		if( a[i] == 0){
			s += (*this)[i];
		}
	}
	(*this) = s;
	delete []a;
}

/*
1 - Fixed
2 - Done
3 - 1) +
	2) +
4 - Reworked. Now finds all strings right.
*/

int main(int argc, char **argv) {
	string z ="212212212212";
	string k = "ssa";
	Word a,b,c('a'), d(k);
	a = z;
	b = "513";

	/* 3-1 */
	a = "top";
	b = "AwA";
	c = !a;
	c = a + c + b;
	c = c * 3;
	a = !c;
	c = c + a;
	cout << c << endl;

	/* 3-2 */
	a = "What  is happening .      he  re : 3424sdf ?";
	size_t i = 0;
	while(i != string::npos && i < a.length()) {
		i = a.find(" ", i);
		i = a.clear_spaces(i);
	}
	cout << a << endl;

	//**4**
	a = "asdo32432asd23345dfs432asd345df";
	cout << a << endl;
	a.compress();
	cout << a << endl;
	return 0;
}
