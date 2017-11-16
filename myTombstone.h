#if !defined(__MYTOMBSTONE_H__)
#define __MYTOMBSTONE_H__
class MyTombstone {
private:
	T* pointerToObj;
	int refCount;
public:
	//do I need to take refcount or always init refCount = 1
	MyTombstone(T* obj, int count) {
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
	// int getRefCount() {

	// }
	// deleteMyTombstone () {
	//	delete this;
	// }
	void checkError () {
		//if object tombstone is pointing to is null
		if (!*pointerToObj) {
			error("Your pointer is dangling!")
		}
		//no pointers pointing to tombstone, but object isn't deleted
		if (refcount == 0 && pointerToObj) {
			error("Attention: your memory is leaking.")
		}
		//no pointers pointing to obj, object is deleted -> reclaim tombstone
		if (refcount == 0 && !pointerToObj) {
			deleteMyTombstone();
		}
	}
	T* getObj () {
		return pointerToObj;
	}
	void error(const char *text) {
    	cout << "ERROR: " << text << endl;
    exit(-1);
	}
}
#endif // __TOMBSTONES_H__