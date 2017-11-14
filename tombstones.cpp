template <class T>
class Pointer {
public:
    Pointer<T>();                               // default constructor
    Pointer<T>(Pointer<T>&);                    // copy constructor
    Pointer<T>(T*);                             // bootstrapping constructor
        // argument should always be a call to new
    ~Pointer<T>();                              // destructor
    T& operator*() const;                       // deferencing
    T* operator->() const;                      // field dereferencing
    Pointer<T>& operator=(const Pointer<T>&);   // assignment
    friend void free(Pointer<T>&);              // delete pointed-at object
        // This is essentially the inverse of the new inside the call to
        // the bootstrapping constructor.
    // equality comparisons:
    bool operator==(const Pointer<T>&) const;
    bool operator!=(const Pointer<T>&) const;
    bool operator==(const int) const;
        // true iff Pointer is null and int is zero
    bool operator!=(const int) const;
        // false iff Pointer is null and int is zero
};