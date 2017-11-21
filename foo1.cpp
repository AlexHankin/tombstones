/////////////////////////////////////////////////////////////////////////////
// foo1.cpp, test file for CS254, assignment 5
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

int main(int argc, char **argv)
{
    Pointer<int> foo(new int(12));
    Pointer<int> tmp((int*)NULL);
    
    cout << "hlo\n";
    Pointer<int> bar = tmp;
    cout << "hlo1\n";
// foo 12, tmp NULL, bar NULL
    if (foo == 0)
     error("Foo shouldn't be null!");

    if (bar != 0)
	 error("Bar should be null!");
    
    bar = new int(12);
    // bar = new int(32);
//foo 12, bar 12, tmp NULL 
    if (foo == bar)
	 error("Foo and bar are distinct pointers!");

    

    if (*foo != *bar)
	 error("Foo and bar should have the same value here!");
    
    free(foo);
    free(bar);
    free(tmp);
    cout << "foo1: OK" << endl;
    return 0;
}
