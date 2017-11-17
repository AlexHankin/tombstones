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
public:
	//do I need to take refCount or always init refCount = 1
	void setMyTombstone (T* obj, int count) {
		pointerToObj = obj;
	 	refCount = count;
	}
	int incrementRefCount() {
		refCount++;
		return refCount;
	}
	int decrementRefCount() {
		refCount--;		
		return refCount;
	}
	// int getrefCount() {

	// }
	void deleteMyTombstone () {
		delete this;
	}
	void checkError () {
		//if object tombstone is pointing to is null
		if (!*pointerToObj) {
			error("Your pointer is dangling!");
		}
		//no pointers pointing to tombstone, but object isn't deleted
		if (refCount == 0 && pointerToObj) {
			error("Attention: your memory is leaking.");
		}
		//no pointers pointing to obj, object is deleted -> reclaim tombstone
		if (refCount == 0 && !pointerToObj) {
			deleteMyTombstone();
		}
	}

	T* getObj () const{
		return pointerToObj;
	}
	void printObj() const{
		cout << "printing object" <<*pointerToObj;
	}
	void error(const char *text) {
    	cout << "ERROR: " << text;
    exit(-1);
	}
};
#endif // __TOMBSTONES_H__