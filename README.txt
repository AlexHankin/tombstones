Xuan Thuong Le
Alex Hankin

CSC 254
Assignment 5: Tombstones


Run instructions:

Running follows the standard gcc procedure for C++ programs. Type, "g++ *filename* -o myFile"
followed by "./myFile". Be sure that the .cpp used is in the same directory as this one and includes
at the top of the file:

#include "tombstones.h"

The directory contains the following files:

README.txt: This file.

tombstones.h
This file contains our template for the Pointer<T> class we were required to implement. More details are provided in the comments
of the code but essentially we appropriately implemented all of our required methods for the template. This included creating all private
parameters, including an additional one for offering a means of switching on and off error checking. We then implemented the rest of
the methods consisting of creating Pointer objects, as well as comparing Pointer objects with themselves or other types. In doing so, 
we consistently reference our tombstones.cc file to access the tombstones properly with our Pointer object.

tombstones.cc
This class contains the description for our tombstone class, containing appropriate private parameters like with our Pointer class.
The methods included were ones that we believed were essential towards a proper tombstone functioning. Including, functions to increment
and decrement the refcount, our entire means of error checking procedure, methods to returns specific parameters, as well as useful debug tools
that would print objects in question. More details in the code and comments.

TEST FILES:

foo1.cpp
foo2.cpp
foo3.cpp
foo4.cpp
foo5.cpp
foo6.cpp
foo7.cpp
foo8.cpp