/////////////////////////////////////////////////////////////////////////////
// tombstones.h, expected interface for CS254 assignment 5
/////////////////////////////////////////////////////////////////////////////

#if !defined(__TOMBSTONES_H__)
#define __TOMBSTONES_H__
#include "myTombstone.h"
template <class T> class Pointer;
template <class T> void free(Pointer<T>& obj);
//access object the tombstone is pointing to

template <class T>
class Pointer {
public:
    Pointer<T>() {
        // default constructor
        //init self???
    }                             
    Pointer<T>(Pointer<T>& otherPointer) {// copy constructor
        this->t = otherPointer->t; //CHECK
    }                       
    Pointer<T>(T* object) {// bootstrapping constructor, argument should always be a call to new
        this->t = new Tombstone(object, 1);
        //if pointer was pointed to some object x2 before, and x2 wasn't deleted
        //do I throw error here???
    }                           
    ~Pointer<T>();                              // destructor
    T& operator*() const {
        return (t->pointerToObj)&; //CHECK
    }                // deferencing
    T* operator->() const {
        return t->pointerToObj; //CHECK
    }                  // field dereferencing
    Pointer<T>& operator=(const Pointer<T>& otherPointer) {
        this->t = otherPointer->t; //does it assign same object to this pointer?
    }       // assignment
    friend void free<T>(Pointer<T>&);           // delete pointed-at object
        // This is essentially the inverse of the new inside the call to
        // the bootstrapping constructor.
    //free deletes the tombstone and object and pointer
    // equality comparisons:
    bool operator==(const Pointer<T>& otherPointer) const {
        if (this->t == otherPointer->t) return true;
        else return false;
    }
    bool operator!=(const Pointer<T>&) const {
        if (this->t == otherPointer->t) return false;
        else return true;
    }
    bool operator==(const int) const;
        // true iff Pointer is null and int is zero
    bool operator!=(const int) const;
        // false iff Pointer is null and int is zero
private:
    Tombstone t;
};


#endif // __TOMBSTONES_H__
