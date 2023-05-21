## Function Signature(s)
Functions should be in `lower_underscore_case`.<br/>
where the no letters are capitalized but each word is seperated by underscores.

```cpp
void some_function_name()
{

}
```

## Classes and Interfaces
---
Classes Should be created with `RAII` in mind so the rule of 5 should be followed all dynamic memory should
be tracked and deallocated properly


Classes should be in `camelCase`.<br/>
Where each of the first letters in compound words is capitalized.<br/>
<br/>

Interfaces should follow the `camelCase` pattern where the first word is always i, symbolizing an interface 

```cpp    
// dynamic resource
class resource {
  int x = 0;
};

// demo class
class foo
{
  public:
    // constructor, 
    // always initilize variables
    foo()
      : p{new resource{}}
    { }
    // copy constructor
    foo(const foo& other)
      : p{new resource{*(other.p)}}
    { }
    // move constructor
    foo(foo&& other)
      : p{other.p}
    {
      other.p = nullptr;
    }

    // copy assignment operator
    foo& operator=(const foo& other)
    {
      if (&other != this) {
        delete p;
        p = nullptr;
        p = new resource{*(other.p)};
      }
      return *this;
    }
    // move assignment operator
    foo& operator=(foo&& other)
    {
      if (&other != this) {
        delete p;
        p = other.p;
        other.p = nullptr;
      }
      return *this;
    }

    // destructor
    ~foo()
    {
      delete p;
    }
    
  private:
    resource* p;
};
```