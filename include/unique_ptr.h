#ifndef UNIQUE_PTR
#define UNIQUE_PTR
template<typename T>
class UniquePtr{
public:
    UniquePtr(){ _p = nullptr;};

    explicit UniquePtr(T* pointer):_p(pointer){};

    ~UniquePtr()
    {
        delete _p;
        _p = nullptr;
    }

    //delete Copy Constructor
    UniquePtr(const UniquePtr&) = delete;

    //delete Operator=
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& pointer) noexcept
    {
        _p = pointer._p;
        pointer._p = nullptr;
    }

    UniquePtr &operator=(UniquePtr&& pointer) noexcept
    {
        if(this != &pointer)
        {
            delete _p;
            _p = pointer;
            pointer = nullptr;
        }
        return *this;
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
        delete _p;
        _p = nullptr;
    }
    void reset(T* pointer)
    {
        delete _p;
        _p = pointer;
    }
    T* release()
    {
        T* old = _p;
        _p = nullptr;
        return old;
    }
    
    explicit operator bool() const{
        return _p != nullptr;
    }
private:
    T* _p;
};

template <typename T>
T* make_unique(T x)
{
    return new T(x);
}
#endif //UNIQUE_PTR