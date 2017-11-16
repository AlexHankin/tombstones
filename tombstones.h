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
    Pointer<T>();                               // default constructor
    Pointer<T>(Pointer<T>&);                        // copy constructor
    Pointer<T>(T* pointee) : pointee_ (pointee);                             // bootstrapping constructor
        // argument should always be a call to new
    ~Pointer<T>();                              // destructor
    T& operator*() const {
        return *pointee_;
    }                // deferencing
    T* operator->() const {
        return pointee_;
    }                  // field dereferencing
    Pointer<T>& operator=(const Pointer<T>&);       // assignment
    friend void free<T>(Pointer<T>&);           // delete pointed-at object
        // This is essentially the inverse of the new inside the call to
        // the bootstrapping constructor.
    // equality comparisons:
    bool operator==(const Pointer<T>&) const;
    bool operator!=(const Pointer<T>&) const;
    bool operator==(const int) const;
        // true iff Pointer is null and int is zero
    bool operator!=(const int) const;
        // false iff Pointer is null and int is zero
private:
    T* pointee_;
};


#endif // __TOMBSTONES_H__
