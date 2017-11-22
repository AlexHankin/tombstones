/////////////////////////////////////////////////////////////////////////////
// tombstones.h, expected interface for CS254 assignment 5
/////////////////////////////////////////////////////////////////////////////

#if !defined(__TOMBSTONES_H__)
#define __TOMBSTONES_H__
#include "tombstones.cc"
#include <iostream>
#include <stdlib.h>
using namespace std;
template <class T> class Pointer;
template <class T> void free(Pointer<T>& obj)
{
    //free a pointer the approriate and designated way, by checking for an error first, then deleting the tombstone
    //safely, unless it was never initialized to begin with, returning an error.
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
        //only default constructor is whether it has been initialized or not, starting at false
        initialized = false;
    }
                                 
    Pointer<T>(Pointer<T>& otherPointer) {// copy constructor

        //we first make sure the Pointer taken as an argument has no errors, then
        //we have this Pointer point to the tombstone of the other Pointer, followed by incrementing its refcount.
        //We then make sure the Pointer has been initialized.
        otherPointer.pt->checkError();
        pt = otherPointer.pt;
        pt->incrementRefCount();
        pt->printObj(cn);
        otherPointer.pt->printObj(cn);
        initialized = true;
    }                       
    Pointer<T>(T* object) {// bootstrapping constructor, argument should always be a call to new

        //essentially the same as the copy constructor except we create the tombstone from scratch,
        //using setMyTombstone, and increment its refcount to 1. Again, initializing the Pointer.

        pt = new MyTombstone<T>();
        pt->setMyTombstone(object);
        pt->incrementRefCount();
        pt->printObj(cn);
        initialized = true;
    }                           
    ~Pointer<T>() {// destructor

        //The destructor which almost always does an error check when automatically called,
        //only ignored when the tombstone is not deleted and null, as this is safe, but would be detected asa dangling pointer other wise.
        if (pt->getDeleted() != true || pt->getObj() != 0) {
            pt->checkError();
            pt->decrementRefCount();
        }        

    }
     T& operator*() const // deferencing
     {
        //simply checks for an error, and returns the object of the tombstone in question.
        pt->checkError();
        pt->printObj(cn);
        return *(pt->getObj());
    }               
    T* operator->() const {
        //essentially the same as previous but for different cases
        pt->checkError();
        pt->printObj(cn);
        return pt->getObj();
    }  
                
    Pointer<T>& operator=(const Pointer<T>& otherPointer) {
        //Assigns another Pointers tombstone to this Pointer, if this Pointer is intialized, we decrement the
        //ref count from the old tombstone first, and then increment in the new one. Errors are checked throughout.

        otherPointer.pt->checkError();

        if (initialized) {
            pt->checkError();
            pt->decrementRefCount();      
        }
        pt = otherPointer.pt;
        pt->incrementRefCount();
        initialized = true;
        pt->printObj(cn);
    }     
    

    friend void free<T>(Pointer<T>&);

        // This is essentially the inverse of the new inside the call to
        // the bootstrapping constructor.
    //free deletes the tombstone and object and pointer

    // equality comparisons:
    bool operator==(const Pointer<T>& otherPointer) const {

        //Checks for errors, while seeing if two Pointers point to the same tombstone.

        pt->checkError();
        pt->printObj(cn);
        return pt == otherPointer.pt;

    }
    bool operator!=(const Pointer<T>& otherPointer) const {

        //same as previous only now checks if the two Pointers point to different tombstones.

        pt->checkError();
        pt->printObj(cn);
        return pt != otherPointer.pt;

    }
    bool operator==(const int refInt) const {

        //Sees if a Pointer's object is equal to a given int. A special case is included for NULL.
        //Essentially looking to the memory to see if its NULL and checking that case first, to ensure no seg faults.

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
    }
        // true iff Pointer is null and int is zero
    bool operator!=(const int refInt) const {

        //Same as previous, but now testing for the inequality of the Pointer and int in question.

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
    }
        // false iff Pointer is null and int is zero
//only private variable is the Pointer's pointer to a tombstone
private:
    MyTombstone<T>* pt;
    bool initialized;
};


#endif // __TOMBSTONES_H__
