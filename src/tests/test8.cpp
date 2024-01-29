#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "../main/gc.h"
#include "../main/containers/gcarray.h"

using namespace GCNamespace;

class Test8 : public GCObject{
public:

    template<class... Args> 
    Test8(Args... args) : Test8(GCInheritance::derived, args...){        
        //nothing
    }

    GCPointer<Test8> p;
    int n;

    Test8(GCInheritance _inh, int _n) : GCObject() {        
        
        GCConstructorFunction<Test8> c(_inh, this,
        [&](){
            n = _n;
            GCDebug::out("Test8 " + ::std::to_string(n) + " created");
        });
    }

    virtual ~Test8() override {
        
        GCDestructorFunction<Test8> c(this, [&](){
            GCDebug::out("Test8 " + ::std::to_string(n) + " deleted");
        });
    }

    void msg(){
        GCDebug::out("hi "  + ::std::to_string(n) + "!");
    }
};

void test8() {

    GCDebug::out("[test 8]************************************");
    GCDebug::out("Dealing with weak pointers:");

    GCPointer<Test8> p1 = new Test8(1);
    GCWeakPointer<Test8> wp = p1;

    p1 = nullptr;

    ::std::this_thread::sleep_for(::std::chrono::milliseconds(1000));
    GCDebug::out("8.1. Test8 deleted?");
}
