/////////////////////////////////////////////////////////////////////////////
// foo8.cpp, test file for CS254, assignment 5
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

void fun(Pointer<int> &foo, int n)
{
    Pointer<int> bar(foo);

    if (n == 0)
	*bar = 100;
    else
    {
	fun(bar, n-1);
	if (n == 10)
	{
	    if (*foo != 100)
		error("Linking of pointers not correct!");
	    free(foo);
	}
    }
}

int main(int argc, char **argv)
{
    Pointer<int> foo(new int(0));
    fun(foo, 10);
    Pointer<int> bar(foo);
    error("Didn't complain about use of dangling pointer foo!");

    return 0;
}
