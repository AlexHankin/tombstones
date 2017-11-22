#if !defined(__MYTOMBSTONE_H__)
#define __MYTOMBSTONE_H__
#include <iostream>
#include <stdlib.h>
using namespace std;

template <class T>
class MyTombstone {
private:
	T* pointerToObj;
	int refCount;
	bool deleted;
	bool check; 
public:
	//initialize tombstone
	MyTombstone(){
		pointerToObj = 0;
		refCount = 0;
		deleted = false;
		check = true; //defaults to true, turning off is optional
	}
	//point tombstone to object
	void setMyTombstone(T* obj) {
		pointerToObj = obj;
	}
	//enable/disable error checking
	void setCheckError(bool c) {
		check = c;
	}
	void incrementRefCount() {
		refCount++;
	}
	void decrementRefCount() {
		refCount--;	
		//checks for memory leaks after decrementation
		checkError();	
	}
	int getrefCount() const{
		return refCount;
	}
	void deleteMyTombstone () {
		if (!deleted) {
		deleted = true;
		pointerToObj = 0;
		refCount = 0;
		} else {
		error("Attempt to double delete: ");
		}
	}
	void checkError () {
		//if user wants error checking to be used				
		if (check) {
			//if a deleted tombstone is getting used again
			if (deleted) {
				error("There is a dangling pointer concerning address: ");			
			}
			//no pointers pointing to tombstone, but object isn't deleted
			if (refCount <= 0 && pointerToObj) {
				error("There is a memory leak concerning address: ");
			}
		}
	}
	//get boolean to see if tombstone was deleted
	bool getDeleted() const {
		return deleted;
	}
	//get pointer to object
	T* getObj () const{
		if (pointerToObj == 0) return 0;
		else return pointerToObj;
	}

	void error(const char *text) {
    	cout << "ERROR: " << text << getObj() << endl;
    exit(-1);
	}
};
#endif // __TOMBSTONES_H__