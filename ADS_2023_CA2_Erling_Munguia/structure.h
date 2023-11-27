#pragma once
#include <sstream>
#include <iostream>
using namespace std;

struct File {

	string name;
	string type;
	int size;
	

};

ostream& operator<<(ostream& out, File*& f)
{
	return out << f->name << "(" << f->size << ")" << f->type;

}