#include "../main/gc.h"

using namespace GCNamespace;

class Member{
public:

    static int c;
    int n;

    Member(){
        n= ++c;
        GCDebug::out("Member constructor" + ::std::to_string(n));
    }

    virtual ~Member(){
        GCDebug::out("Member destructor" + ::std::to_string(n));
    }
};

int Member::c = 0;

class Base{
public:
    Member p0;
    int n;

    Base(int _n)
    {
        n=_n;
        GCDebug::out("Base constructor" + ::std::to_string(n));
    }


    virtual ~Base()
    {
        GCDebug::out("Base destructor" + ::std::to_string(n));
    }
};

class Derived : public Base{
public:
    Member p1;
    
    Derived(int _n) : Base(_n)
    {
        GCDebug::out("Derived constructor" + ::std::to_string(n));
    }


    virtual ~Derived() override
    {
        GCDebug::out("Derived destructor" + ::std::to_string(n));
    }
};

void test0(){
    Derived d(1);
}

