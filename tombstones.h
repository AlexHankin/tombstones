/////////////////////////////////////////////////////////////////////////////
// tombstones.h, expected interface for CS254 assignment 5
/////////////////////////////////////////////////////////////////////////////

#if !defined(__TOMBSTONES_H__)
#define __TOMBSTONES_H__
#include "myTombstone.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
template <class T> class Pointer;
template <class T> void free(Pointer<T>& obj)
{
    if (!obj.initialized) {
        cout << "ERROR: Tried to release uninitialized pointer at address " << obj.t.getObj() << endl << "Aborting program...";
        exit(0);
    }
    else{
        obj.t.deleteMyTombstone();
    }
}
//access object the tombstone is pointing to

template <class T>
class Pointer {
public:
    Pointer<T>() {
        initialized = false;
       //init self???  
    }
        // default constructor
                                 
    Pointer<T>(Pointer<T>& otherPointer) {// copy constructor
        initialized = true;
        t = otherPointer.t;
        cout << "From Pointer<T>(Pointer<T>& otherPointer) {\n";
        t.incrementRefCount();
        //t.checkError();
        t.printObj();
    }                       
    Pointer<T>(T* object) {// bootstrapping constructor, argument should always be a call to new
        initialized = true;
        t.setMyTombstone(object, 1);
        cout << "From Pointer<T>(T* object) {\n";
        t.printObj();
        //if pointer was pointed to some object x2 before, and x2 wasn't deleted
        //do I throw error here???
    }                           
    ~Pointer<T>() {// destructor
        cout << "Destruction? \n";
        t.printObj();
        //t.decrementRefCount();
        t.checkError();
        //t = NULL;
    }
     T& operator*() const // deferencing
     {//CHECK
        cout << "From operator*\n";
        t.printObj();
        return *t.getObj(); //CHECK
    }               
    T* operator->() const {
        cout << "From operator->\n";
        t.printObj();
        return t.getObj(); //CHECK
    }                  // field dereferencing
    Pointer<T>& operator=(const Pointer<T>& otherPointer) {
        cout << "From Pointer<T>& operator=(const Pointer<T>& otherPointer) \n";
        t.decrementRefCount();
        t = otherPointer.t; //does it assign same object to this pointer?
        t.incrementRefCount();
        t.printObj();
    }       // assignment
    friend void free<T>(Pointer<T>&);
    //{
    //    t = NULL;
    //    ~Pointer<T>();  
    //}           // delete pointed-at object
        // This is essentially the inverse of the new inside the call to
        // the bootstrapping constructor.
    //free deletes the tombstone and object and pointer
    // equality comparisons:
    bool operator==(const Pointer<T>& otherPointer) const {
        cout << "operator==(const Pointer<T>& otherPointer)\n";
        t.printObj();
        if (t.getObj() == otherPointer.t.getObj() && t.getrefCount() == otherPointer.t.getrefCount())  return true;
        else return false;
    }
    bool operator!=(const Pointer<T>& otherPointer) const {
        cout << "operator!=(const Pointer<T>& otherPointer)\n";
        t.printObj();
        if (t.getObj() != otherPointer.t.getObj()) return true;
        else return false;
    }
    bool operator==(const int refInt) const {
        cout << "operator==(const int refInt)\n";
        t.printObj();
       if (t.getObj() == 0x0)
            if (0 == refInt) return true;
            else return false;
        else{
            if (*(t.getObj()) == refInt) return true;
            else return false;
        }
    }
        // true iff Pointer is null and int is zero
    bool operator!=(const int refInt) const {
        cout << "operator!=(const int refInt)\n";
        t.printObj();
        if (t.getObj() == 0x0)
            if (0 != refInt) return true;
            else return false;
        else{
            if (*(t.getObj()) != refInt) return true;
            else return false;
        }
    }
        // false iff Pointer is null and int is zero
private:
    MyTombstone<T> t;
    bool initialized;
};


#endif // __TOMBSTONES_H__
