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
public:
	//do I need to take refCount or always init refCount = 1
	// void setMyTombstone (T* obj, int count) {
	// 	pointerToObj = obj;
	//  	refCount = count;
	// }
	MyTombstone(){
		pointerToObj = 0;
		refCount = 0;
		deleted = false;
	}

	void setMyTombstone(T* obj) {
		pointerToObj = obj;
	}
	void incrementRefCount() {
		char const *cn = "call increment refcount \n";
		
		refCount++;
		printObj(cn);
		// return refCount;
	}
	void decrementRefCount() {
		char const *cn = "call decrement refCount\n";
		refCount--;	
		checkError();
		printObj(cn);	
		// return refCount;
	}
	int getrefCount() const{
		return refCount;
	}
	void deleteMyTombstone () {
		cout << "deleting tombstone\n";
		deleted = true;
		pointerToObj = 0;
		refCount = 0;
	}
	void checkError () {
		//if object tombstone is pointing to is null
		if (deleted) {
			cout << "Tester0" << endl;
			cout << pointerToObj;
		// 	error("Attempted to double delete: ");
		// }
		// if (pointerToObj == 0 && refCount > 0) {
		// 	cout << "Tester1" << endl;
			error("There is a dangling pointer concerning address: ");
		}
		//no pointers pointing to tombstone, but object isn't deleted
		printObj("checkError ");
		//if (0 == pointerToObj)
		//	cout << pointerToObj;
		if (refCount <= 0 && pointerToObj) {
			cout << "Tester2" << endl;
			error("There is a memory leak concerning address: ");
		}
		//no pointers pointing to obj, object is deleted -> reclaim tombstone
		// if (refCount == 0 && !pointerToObj) {
		// 	{cout << "Tester3" << endl;
		// 	 deleteMyTombstone();
		// 	 printObj();
		// }
		// }
	}
	bool getDeleted() const {
		return deleted;
	}
 
	T* getObj () const{
		if (pointerToObj == 0)
			return 0;
		else
			return pointerToObj;
	}

	void printObj(char const* funcname) const{
		if (pointerToObj == 0)
			cout << funcname << " printing object: " << "NULL refCount: " << refCount << " \n\n";
		else
			cout << "printing object: " << pointerToObj << " refCount: " << refCount << " \n\n";
	}
	void error(const char *text) {
    	cout << "ERROR: " << text << getObj() << endl;
    exit(-1);
	}
};
#endif // __TOMBSTONES_H__