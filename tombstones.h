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
    // if (!obj.initialized) {
    //     cout << "ERROR: Tried to release uninitialized pointer at address " << obj.t.getObj() << endl << "Aborting program...";
    //     exit(0);
    // }
    // else{
    //     cout << "From free\n";
    //     obj.t.deleteMyTombstone();
    // }
    if (!obj.initialized) {
        cout << "ERROR: Tried to release uninitialized pointer  " << endl << "Aborting program...";
        exit(0);
    } else {
        char const* cn = "template <class T> void free(Pointer<T>& obj)";
        cout << cn << "\n";
        obj.pt->checkError();
        obj.pt->printObj(cn);
        obj.pt->deleteMyTombstone();
    }
}
//access object the tombstone is pointing to

template <class T>
class Pointer {
public:
    Pointer<T>() {
        initialized = false;
        cout << "Pointer<T>()\n";
       //init self???  
    }
        // default constructor
                                 
    Pointer<T>(Pointer<T>& otherPointer) {// copy constructor
        // initialized = true;
        char const *cn =  "From Pointer<T>(Pointer<T>& otherPointer) {\n";
        cout << cn << "\n";
        // // t.checkError();
        // if (otherPointer.initialized) {
        //     otherPointer.t.checkError();
        //     pt = otherPointer.pt;
        //     pt->incrementRefCount();
        // }
        //  t = otherPointer.t;
        // t.incrementRefCount();
        otherPointer.pt->checkError();
        //DO I CHECK PT ERROR???
        pt = otherPointer.pt;
        pt->incrementRefCount();
        cout << "pt\n";
        pt->printObj(cn);
        cout << "otherPointer\n";
        otherPointer.pt->printObj(cn);
        initialized = true;
    }                       
    Pointer<T>(T* object) {// bootstrapping constructor, argument should always be a call to new
        // initialized = true;
        // t.setMyTombstone(object);
        // t.incrementRefCount();
        // t.printObj();
        char const *cn =  "From Pointer<T>(T* object) { ";
        cout << cn << "\n";
        pt = new MyTombstone<T>();
        pt->setMyTombstone(object);
        pt->incrementRefCount();
        pt->printObj(cn);
        initialized = true;
    }                           
    ~Pointer<T>() {// destructor
        char const *cn =  "Destruction ";
        cout << cn << "\n";
        // t.printObj();
        // if (!t.getDeleted()) {
        //     t.decrementRefCount();
        //     t.checkError();
        // }
        //t = NULL;
        if (pt->getDeleted() != true || pt->getObj() != 0) {
            pt->checkError();
            pt->decrementRefCount();
        }        
        cout << "print end destruct\n";
        pt->printObj(cn);
    }
     T& operator*() const // deferencing
     {//CHECK
        // t.checkError();
        char const *cn = "From operator* ";
        cout << cn << "\n";
        pt->checkError();
        pt->printObj(cn);
        return *(pt->getObj());
        // t.printObj();
        // return *t.getObj(); //CHECK
    }               
    T* operator->() const {
        char const* cn = "From operator-> ";
        cout << cn << "\n";
        pt->checkError();
        pt->printObj(cn);
        return pt->getObj();
        // t.checkError();
        // t.printObj();
        // return t.getObj(); //CHECK
    }  
                    // field dereferencing
    Pointer<T>& operator=(const Pointer<T>& otherPointer) {
        char const *cn =  "From Pointer<T>& operator=(const Pointer<T>& otherPointer) ";
        cout << cn << "\n";
        otherPointer.pt->checkError();
        // cout << "after check eq\n";
        if (initialized) {
            pt->checkError();
            pt->decrementRefCount();      
        }
        pt = otherPointer.pt;
        pt->incrementRefCount();
        initialized = true;
        cout << "end of = op\n";
        pt->printObj(cn);
        // t.decrementRefCount();
        // t = otherPointer.t; //does it assign same object to this pointer?
        // t.incrementRefCount();
        // t.printObj();
        // initialized = true;
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
        char const* cn = "operator==(const Pointer<T>& otherPointer)\n";
        cout << cn << "\n";
        // t.checkError();
        pt->checkError();
        pt->printObj(cn);
        return pt == otherPointer.pt;

        // t.printObj();
        // if (t.getObj() == otherPointer.t.getObj() && t.getrefCount() == otherPointer.t.getrefCount())  return true;
        // else return false;
    }
    bool operator!=(const Pointer<T>& otherPointer) const {
        char const* cn = "operator!=(const Pointer<T>& otherPointer)";
        cout << cn << "\n";
        pt->checkError();
        //cout << "Made it through error check \n";
        pt->printObj(cn);
        return pt != otherPointer.pt;
        // t.checkError();
        // t.printObj();
        // if (t.getObj() != otherPointer.t.getObj()) return true;
        // else return false;
    }
    bool operator==(const int refInt) const {
        char const* cn =  "operator==(const int refInt)";
        cout << cn << "\n";
        pt->printObj(cn);
        pt->checkError();
        if (pt->getObj() == 0) {
            if (refInt == 0)
                return true;
            else
                return false;
        }
        else
            return *(pt->getObj()) == refInt;
       //  t.checkError();
       //  t.printObj();
       // if (t.getObj() == 0x0)
       //      if (0 == refInt) return true;
       //      else return false;
       //  else{
       //      if (*(t.getObj()) == refInt) return true;
       //      else return false;
       //  }
    }
        // true iff Pointer is null and int is zero
    bool operator!=(const int refInt) const {
       char const* cn =  "operator!=(const int refInt)";
        cout << cn << "\n";
        pt->printObj(cn);
        pt->checkError();
        if (pt->getObj() == 0) {
            if (refInt == 0)
                return false;
            else
                return true;
        }
        else
            return *(pt->getObj()) != refInt;
        //     if (0 != refInt) return true;
        //     else return false;
        // else{
        //     if (*(t.getObj()) != refInt) return true;
        //     else return false;
        // }
    }
        // false iff Pointer is null and int is zero
private:
    // MyTombstone<T> t;
    MyTombstone<T>* pt;
    bool initialized;
};


#endif // __TOMBSTONES_H__
