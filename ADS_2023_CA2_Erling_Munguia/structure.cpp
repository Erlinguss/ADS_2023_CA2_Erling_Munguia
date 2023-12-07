#include "Structure.h"


ostream& operator<<(ostream& out, File*& f)
{
    return out << f->name << "(" << f->size << ")" << f->type;
}