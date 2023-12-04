#pragma once
#include <sstream>
#include <iostream>
using namespace std;

struct File {

	string name;
	string type;
	int size=0;
	
};

ostream& operator<<(ostream& out, File*& f)
{
	return out << f->name << "(" << f->size << ")" << f->type;

}