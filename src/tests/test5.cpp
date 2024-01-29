#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "../main/gc.h"
#include "../main/containers/gcmap.h"

using namespace GCNamespace;


class Test5 : public GCObject{
public:

    GCPointer<Test5> p;
    int n;

    template<class... Args> 
    Test5(Args... args) : Test5(GCInheritance::derived, args...){        
        //nothing
    }

    Test5(GCInheritance _inh, int _n) : GCObject() { 

        GCConstructorFunction<Test5> c(_inh, this); 
        n = _n;
        GCDebug::out("Test5 " + ::std::to_string(n) + " created");
    }

    virtual ~Test5() override {
                
        GCDestructorFunction<Test5> destr(this);
        
        GCDebug::out("Test5 " + ::std::to_string(n) + " deleted");
    }

    void msg(){
        GCDebug::out("hi "  + ::std::to_string(n) + "!");
    }
};

void test5() {

    GCDebug::out("[test 5]************************************");
    GCDebug::out("Dealing with maps:");

   // 5.1. A map of strings to pointers to gcobjects
    GCDebug::out("5.1. A map of strings to pointers");

    GCMapPointer<::std::string,Test5> pmap = new GCMap<::std::string,Test5>;

    pmap["KEY"] = new Test5(1);
    pmap["KEY"] = new Test5(2);
    
    ::std::this_thread::sleep_for(::std::chrono::milliseconds(1000));
    GCDebug::out("5.2. Test5 1 deleted?");
    pmap["KEY"]->p=pmap["KEY"];
    pmap = nullptr;
    
    ::std::this_thread::sleep_for(::std::chrono::milliseconds(1000));
    GCDebug::out("5.3. Test5 2 deleted?");
}
