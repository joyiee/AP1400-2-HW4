#ifndef SHARED_PTR
#define SHARED_PTR
template<typename T>
class SharedPtr
{
public:
    //Construct
    SharedPtr(T* pointer)
    {
        _p = pointer;
        count = new size_t(1);
    }

    //Default Construct
    SharedPtr()
    {
        _p = nullptr;
        count = new size_t(0);
    }

    //Destructor
    ~SharedPtr()
    {
        if(--(*count)==0)
            delete _p;
        _p = nullptr;
    }

    //Copy Constructor
    SharedPtr(const SharedPtr &pointer)
    {
        _p = pointer._p;
        count = pointer.count;
        (*count)++;
    }

    //Operaror =
    SharedPtr& operator=(const SharedPtr &pointer)
    {
        if(this != &pointer)
        {
            _p = pointer._p;
            count = pointer.count;
            (*count)++;
        }
        return *this;
    }

    //use count
    size_t use_count() const
    {
        return *count;
    }

    T* get() const
    {
        return _p;
    }

    T& operator*() const
    {
        return *_p;
    }

    T* operator->() const
    {
        return _p;
    }

    void reset()
    {
        if(--(*count)==0)
            delete _p;
        _p = nullptr;
        count = new size_t(0);
    }

    void reset(T* pointer)
    {
        if(--(*count)==0)
            delete _p;
        _p = pointer;
        count = new size_t(1);
    }

    //bool
    explicit operator bool()
    {
        return _p!=nullptr;
    }

private:
    T* _p;
    size_t *count;
};


template<typename T>
T* make_shared(T x)
{
    return new T(x);
}
#endif //SHARED_PTR