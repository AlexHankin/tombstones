/////////////////////////////////////////////////////////////////////////////
// foo3.cpp, test file for CS254, assignment 5
/////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdlib.h>
#include "tombstones.h"

using namespace std;

void error(const char *text)
{
    cout << "ERROR: " << text << endl;
    exit(-1);
}

typedef struct str
{
    int a;
    int b;
    str(int x, int y) : a(x), b(y) {}
}
twoints;

int main(int argc, char **argv)
{
    Pointer<int> foo(new int(12));
    Pointer<twoints> bar(new twoints(12,12));

    if (*foo != bar->a || *foo != bar->b)
	error("Foo, bar->a, and bar->b should all be 12");

    free(foo);
    free(bar);
    cout << "foo3: OK" << endl;
    return 0;
}
