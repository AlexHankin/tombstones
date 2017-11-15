/////////////////////////////////////////////////////////////////////////////
// foo6.cpp, test file for CS254, assignment 5
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

Pointer<int> &rec(int n, Pointer<int> foo)
{
    static Pointer<int> result(new int(*foo));
    if (0 == n)
	return result;
    result = (Pointer<int>&)(rec(n-1, foo));
    *result += 1;
    return result;
}

Pointer<int> &recref(int n, Pointer<int> &foo)
{
    if (0 == n)
	return foo;
    *foo += 1;
    return rec(n-1, foo);
}

void proc()
{
    Pointer<int> foo(new int(0));
    Pointer<int> bar(rec(100, foo));

    if (*bar != 100 || *foo != 0)
	error("Foo or bar incorrect after rec()!");

    foo = recref(100, bar);
    if (*foo != 200)
	error("Foo incorrect after recref()!");
    if (foo != bar)
	error("Foo not an alias for bar after recref()!");

    free(foo);
}

int main(int argc, char **argv)
{
    proc();
    error("Didn't blow up when leaking memory!");

    return 0;
}
