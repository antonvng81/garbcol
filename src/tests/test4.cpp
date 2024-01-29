#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "../main/gc.h"
#include "../main/containers/gclist.h"


using namespace GCNamespace;

// Multi derived classes must be created/destroyed whith
// GCConstructorFunction/GCDestructorFunction to be GC managed

class Test4Base : public GCObject{
public:

    template<class... Args> 
    Test4Base(Args... args) : Test4Base(GCInheritance::derived, args...){  
        //nothing      
    }

    int n;
    // Example

    Test4Base(GCInheritance _inh, int _n) : GCObject() {

        GCConstructorFunction<Test4Base> constr(_inh, this);

        // Setting constructor
        n = _n;

        if(typeid(Test4Base).hash_code() == this->gc_get_class_id())
        {
            GCDebug::out("Test4Base " + ::std::to_string(n) + " created as complete class");
        }
        else{
            GCDebug::out("Test4Base " + ::std::to_string(n) + " created as base class");
        }
    }

    virtual ~Test4Base() override {

        GCDestructorFunction<Test4Base> destr(this);

        // Setting destructor
        GCDebug::out("Test4Base " + ::std::to_string(n) + " deleted as base class");
    }

    void msg(){
        GCDebug::out("hi "  + ::std::to_string(n) + "!");
    }

};

// derived class inherits a base type
class Test4 : public Test4Base{
public:
    
    template<class... Args> 
    Test4(Args... args) : Test4(GCInheritance::derived, args...){  
        //nothing      
    }

    GCPointer<Test4> p;

    Test4(GCInheritance _inh, int _n) : Test4Base(GCInheritance::base, _n) {

        GCConstructorFunction<Test4> constr(_inh, this);

        GCDebug::out("Test4 " + ::std::to_string(n) + " created");
    }

    virtual ~Test4() override {        
       
        GCDestructorFunction<Test4> destr(this);
                
        GCDebug::out("Test4 " + ::std::to_string(n) + " deleted");
    }
};

void test4() {

    GCDebug::out("[test 4]************************************");
    GCDebug::out("Dealing with inheritnce of GCObjects. Create a list of objects:");

    // 4.1. A base class as complete object
    GCDebug::out("4.1. A base class as complete object");

    GCPointer<Test4> pb = 
        new Test4(-1);

    GCPointer<Test4> pb2 = 
        new Test4(-2);

    pb->p = pb;
    pb = pb2;

    ::std::this_thread::sleep_for(::std::chrono::milliseconds(1000));
    GCDebug::out("Test4base -1 deleted?");

    // 4.2. A list of pointers of derived classes
    GCDebug::out("4.2. A list of pointers of derived classes");

    // A list of pointers of derived classes
    GCListPointer<Test4> plist = new GCList<Test4>;

    for (int n = 0; n < 5; n++)
        plist->push_back( new Test4(n) );

    // Change Test4 1
    GCList<Test4>::iterator i = plist->begin();
    *(++i) = new Test4(10000);

    for (auto p : *plist) {
        p->msg();
    }

    ::std::this_thread::sleep_for(::std::chrono::milliseconds(1000));
    GCDebug::out("4.3. Test4 1 deleted?");


    // Cleaning
    plist = nullptr;
    ::std::this_thread::sleep_for(::std::chrono::milliseconds(1000));
}
