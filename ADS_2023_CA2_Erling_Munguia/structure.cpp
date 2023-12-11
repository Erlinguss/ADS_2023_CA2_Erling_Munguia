#include "Structure.h"


ostream& operator<<(ostream& out, File*& f)
{
    if(f->type!= "dir")
        return out << f->name << "(" << f->size << ")" << f->type;
    return out << f->name ;
}