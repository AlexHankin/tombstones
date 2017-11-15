/////////////////////////////////////////////////////////////////////////////
// foo5.cpp, test file for CS254, assignment 5
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

void proc()
{
    Pointer<int> foo(new int(12));
}

int main(int argc, char **argv)
{
    proc();
    error("Didn't blow up when leaking memory!");

    return 0;
}
