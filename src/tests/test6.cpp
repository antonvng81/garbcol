#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "../main/gc.h"
#include "../main/containers/gcset.h"

using namespace GCNamespace;

class Test6 : public GCObject{
public:

    template<class... Args> 
    Test6(Args... args) : Test6(GCInheritance::derived, args...){        
        //nothing
    }

    GCPointer<Test6> p;
    int n;

    Test6(GCInheritance _inh, int _n) : GCObject() {    
        
        GCConstructorFunction<Test6> c(_inh, this);
        n = _n;
        GCDebug::out("Test6 " + ::std::to_string(n) + " created");
    }

    virtual ~Test6() override {
        
        GCDestructorFunction<Test6> destr(this);

        GCDebug::out("Test6 " + ::std::to_string(n) + " deleted");
    }

    void msg(){
        GCDebug::out("hi "  + ::std::to_string(n) + "!");
    }
};

void test6() {

    GCDebug::out("[test 6]************************************");
    GCDebug::out("Dealing with sets:");

   // 6.1. A set of pointers to strings
    GCDebug::out("6.1. A set of pointers to strings");

    GCPointer<Test6> p1 = new Test6(1), p2 = new Test6(2);

    GCSetPointer<Test6> pset = new GCSet<Test6>;

    pset->insert(p1);
    pset->insert(p2);
    pset->insert(p2);

    for (auto p : *pset) {
        p->msg();
    }
    
    ::std::this_thread::sleep_for(::std::chrono::milliseconds(1000));
    GCDebug::out("6.2. Set has Test6 1 and Test6 2 one time only?");

    // Cleaning
    pset = nullptr;
    
    ::std::this_thread::sleep_for(::std::chrono::milliseconds(1000));
}
