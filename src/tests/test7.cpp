#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "../main/gc.h"
#include "../main/containers/gcarray.h"

using namespace GCNamespace;

class Test7 : public GCObject{
public:
    
    template<class... Args> 
    Test7(Args... args) : Test7(GCInheritance::derived, args...){        
        //nothing
    }

    GCPointer<Test7> p;
    int n;

    Test7(GCInheritance _inh, int _n) : GCObject() {        
        
        GCConstructorFunction<Test7> c(_inh, this);

        n = _n;
        GCDebug::out("Test7 " + ::std::to_string(n) + " created");
    }

    virtual ~Test7() override {
        
        GCDestructorFunction<Test7> destr(this);

        GCDebug::out("Test7 " + ::std::to_string(n) + " deleted");
    }

    void msg(){
        GCDebug::out("hi "  + ::std::to_string(n) + "!");
    }
};

void test7() {

    GCDebug::out("[test 7]************************************");
    GCDebug::out("Dealing with arrays:");

   // 7.1. An array of pointers to gcobjects
    GCDebug::out("7.1. An array of pointers to gcobjects");

    GCPointer<Test7> p1 = new Test7(1), p2 = new Test7(2);

    GCArrayPointer<Test7,2> parr = new GCArray<Test7,2>;

    if(parr == parr){
    parr[0]=p1;
    parr[1]=p2;}

    for (GCPointer<Test7> p : *parr) {
        p->msg();
    }

    p1 = nullptr;
    p2 = nullptr;

    ::std::this_thread::sleep_for(::std::chrono::milliseconds(1000));
    GCDebug::out("7.2. Test7 1 and Test7 2 not deleted?");

    // Cleaning
    parr = nullptr;

    ::std::this_thread::sleep_for(::std::chrono::milliseconds(1000));
    GCDebug::out("7.2. Test7 1 and Test7 2  deleted?");
}
