#include <iostream>
#include <cstdlib>
#include <string>
#include <stdlib.h>
#include <set>

using namespace std;

const string avaiable_symbols = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string special_symbols = ".,!?:";
class Word:public string{
    int nbk;
    int count();
    void sort();
    string delete_char_after(string, char, size_t);
    int delete_string_after(string, size_t);

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

    Word operator+(Word&);
    Word operator&&(Word&);
    Word operator-(Word&);
    void instead(Word&,Word&);

    int getLet();
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
    while(k != npos) {
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

    while(k != npos) {
        *this = substr(0, k) + substr(k + 1);
        i = k;
        k = find(c, i);
        count++;
    }
    return count;
}


int Word::count()
{
    int num = 0;
    for (size_t k = 0; k < avaiable_symbols.length(); k++) {
        char c = avaiable_symbols.at(k);
        if (find(c) != npos)
            num ++;
    }
    return num;
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


/* find and return equal symbols soted array */
Word Word::operator&&(Word& a)
{
    string s;
    for(size_t i = 0; i < (*this).length(); i++) {
        char c = (*this)[i];
        if(a.find(c) != npos && s.find(c) == npos)
            s += c;
    }
    Word res = s;
    res.sort();
    return res;
}


/* */
Word Word::operator-(Word& a)
{
    size_t k = 0;
    string s = (*((string *)this));
    string l = s;
    Word res = (*this)&&a;

    while( k < a.length()) {
        s = delete_char_after(s, a[k], npos);
        k++;
    }
    *this = s;

    k = 0;
    while( k < l.length()) {
        a = delete_char_after(a, l[k], npos);
        k++;
    }
    a.count();
    count();

    return res;
}


Word Word::operator*(int a)
{
    string l = (*((string *)this));
    Word s;
    for (int i = 0 ; i < a; i++)
        s += *this;
    Word res = s;
    return res;
}


Word Word::operator/(int a)
{
    Word tmp;
    bool is_good = false;
    if ((length() % a) != 0) {
        cout << "Wrong length: " << length() % a << endl;
        //return this;
    }

    for (int i = 0 ; i < a; i++) {

        //tmp = substr(a);
    }

    //return res;
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
        if(a.find(c) == npos) {
            i++;
            continue;
        }
        s = s.substr(0,i)+b+s.substr(i+1);
        i += b.length();
    }
    *this = s;
}


Word Word::operator+(Word& a)
{
    Word tmp;
    tmp = ((string)(data()) + (string)(a.data()) );
    return tmp;
}

void Word::compress()
{
    /*
    string s;
    size_t length = (*(string*)this).length();
    size_t step = length / 2;
    for (; step > 1; step--) {
        //s = replase();
    }*/
    return;
}

/*
1 - Fixed, nbk was wrong
2 - Done
3 - 1) +
    2) +
*/

string test_sum()
{
    Word a1, b1, sum;
    a1 = "12345";
    b1 = "abcde";
    sum = a1 + b1;
    if (sum.getLet() != 10)
        return "FAILED";
    if (sum != "12345abcde")
        return "FAILED";
    return "PASSED";
}


void task3()
{
    Word a, b, c;
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
    Word newstr;
    newstr = "What  is     happening  here?I   don't know !";
    cout << "BEFORE CLEANING: " << newstr << endl;
    size_t i = 0;
    /* Multiple spaces */
    while(i < newstr.length()) {
        i = newstr.find("  ", 0);
        if (i == Word::npos)
            break;
        newstr.erase(i, 1);
    }
    /* Space before special symbol */
    string::const_iterator iter = special_symbols.begin();
    while (iter != special_symbols.end()) {
        i = 0;
        while (i < newstr.length()) {
            i = newstr.find(*iter + ' ', 0);
            string tmp_str;
            cout << (*iter) << endl;
            if (i == Word::npos)
                break;
            newstr.erase(i + 1, 1);
        }
        iter++;
    }
    /* No space after special symbol */
    iter = special_symbols.begin();
    while (iter != special_symbols.end()) {
        i = 0;
        while (i < newstr.length()) {
            i = newstr.find(' ' + *iter, 0);
            if (i == Word::npos)
                break;
            newstr.erase(i, 1);
        }
        iter++;
    }
    cout << "AFTER CLEANING : " << newstr << endl;
}

void task4()
{
    Word a;
    a = "toppotAwAtoppotAwAtoppotAwAAwAtoppotAwAtoppotAwAtoppot";
    cout << "BEFORE COMPRESS: " << a << endl;
    a.compress();
    cout << "AFTER COMPRESS : " << a << endl;
}


//bool test_operators

int main(int argc, char **argv) {
    cout << "test_sum: " << test_sum() << endl;
    // test_funcs(); // all funcs
    task3();
    task4();
}
