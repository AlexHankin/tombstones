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
        cout << "ERROR: Tried to release uninitialized pointer  " << endl << "Aborting program...\n";
        exit(0);
    } else {
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
        initialized = true;
    }                       
    Pointer<T>(T* object) {// bootstrapping constructor, argument should always be a call to new

        //essentially the same as the copy constructor except we create the tombstone from scratch,
        //using setMyTombstone, and increment its refcount to 1. Again, initializing the Pointer.
        pt = new MyTombstone<T>();
        pt->setMyTombstone(object);
        pt->incrementRefCount();
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
        return *(pt->getObj());
    }               
    T* operator->() const {
        //essentially the same as previous but for different cases
        pt->checkError();
        return pt->getObj();
    }  
                
    Pointer<T>& operator=(const Pointer<T>& otherPointer) {
        //Assigns another Pointers tombstone to this Pointer, if this Pointer is intialized, we decrement the
        //ref count from the old tombstone first, and then increment in the new one. Errors are checked throughout.
        otherPointer.pt->checkError();
        //to avoid seg faults only check errors for this pt, if it was initialized
        if (initialized) {
            pt->checkError();
            pt->decrementRefCount();      
        }
        pt = otherPointer.pt;
        pt->incrementRefCount();
        initialized = true;
    }     
    

    friend void free<T>(Pointer<T>&);

        // This is essentially the inverse of the new inside the call to
        // the bootstrapping constructor.
    //free deletes the tombstone and object and pointer

    // equality comparisons:
    bool operator==(const Pointer<T>& otherPointer) const {
        //Checks for errors, while seeing if two Pointers point to the same tombstone.
        pt->checkError();
        return pt == otherPointer.pt;

    }

        //same as previous only now checks if the two Pointers point to different tombstones.
    bool operator!=(const Pointer<T>& otherPointer) const {
        pt->checkError();
        return pt != otherPointer.pt;

    }
    bool operator==(const int refInt) const {

        //Sees if a Pointer's object is equal to a given int. A special case is included for NULL.
        //Essentially looking to the memory to see if its NULL and checking that case first, to ensure no seg faults.
        pt->checkError();
        if (pt->getObj() == 0) return refInt == 0;
        else return *(pt->getObj()) == refInt;
    }

    bool operator!=(const int refInt) const {

        //Same as previous, but now testing for the inequality of the Pointer and int in question.
        pt->checkError();
        if (pt->getObj() == 0) return refInt != 0;
        else return *(pt->getObj()) != refInt;
    }
    //oprtional error checking for pointers
    void setCheckError(bool check) {
        pt->setCheckError(check);
    }
//only private variable is the Pointer's pointer to a tombstone
private:
    MyTombstone<T>* pt;
    bool initialized;
};


#endif // __TOMBSTONES_H__
