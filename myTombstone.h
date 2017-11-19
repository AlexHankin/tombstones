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
	int getrefCount() const{
		return refCount;
	}
	void deleteMyTombstone () {
		pointerToObj = 0;
		refCount = 0;
	}
	void checkError () {
		//if object tombstone is pointing to is null
		if (pointerToObj == 0) {
			cout << "Tester1" << endl;
			error("There is a dangling pointer concerning address: ");
		}
		//no pointers pointing to tombstone, but object isn't deleted
		printObj();
		if (refCount == 0 && pointerToObj) {
			cout << "Tester2" << endl;
			error("There is a memory leak concerning address: ");
		}
		//no pointers pointing to obj, object is deleted -> reclaim tombstone
		if (refCount == 0 && !pointerToObj) {
			{cout << "Tester3" << endl;
			deleteMyTombstone();}
		}
	}

	T* getObj () const{
		return pointerToObj;
	}

	void printObj() const{
		if (pointerToObj == 0)
			cout << "printing object: " << "NULL refCount: " << refCount << " \n\n";
		else
			cout << "printing object: " << *pointerToObj << " refCount: " << refCount << " \n\n";
	}
	void error(const char *text) {
    	cout << "ERROR: " << text << getObj() << endl;
    exit(-1);
	}
};
#endif // __TOMBSTONES_H__