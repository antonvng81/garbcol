#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "../main/gc.h"

using namespace GCNamespace;

class Other {

    int n;

public:

    Other(int _n){
        n = _n;
    }

    ~Other() {
        GCDebug::out("Other "+::std::to_string(n)+" deleted");
    }

    void msg(){
        GCDebug::out("hi Other "  + ::std::to_string(n) + "!");
    }
};

// An GCObject derived class
class Test3 : public GCObject{
public:

    GCPointer<Test3> p;
    int n;

    static GCStaticSharedPointer<Other> s;

    template<class... Args> 
    Test3(Args... args) : Test3(GCInheritance::derived, args...){        
        //nothing
    }

    Test3(GCInheritance _inh, int _n) : GCObject() { 
                
        GCConstructorFunction<Test3> constr(_inh, this);
        
        n = _n;
        GCDebug::out("Test3 " + ::std::to_string(n) + " created");
    }

    virtual ~Test3() override {

        GCDestructorFunction<Test3> destr(this);        

        GCDebug::out("Test3 " + ::std::to_string(n) + " deleted");
    }

    void msg(){
        GCDebug::out("hi Test3 "  + ::std::to_string(n) + "!");
    }
};

GCStaticSharedPointer<Other> Test3::s;


void test3_sub1(const GCPointer<Test3>& c3){

    // A normal pointer
    GCPointer<Test3> nonscoped = c3;
}

void test3_sub2(GCUniquePointer<Test3>&& c3){

    // A unique pointer
    GCUniquePointer<Test3> scoped = ::std::move(c3);
}

void test3() {

    GCDebug::out("[test 3]************************************");
    GCDebug::out("Dealing with derived GCObjects. Finalize objects:");

    // 3.1. Creating new GCObject with circular references
    GCDebug::out("3.1. Creating new GCObject with circular references");    

    GCPointer<Test3> p;

    p = new Test3(1);
    p->p = new Test3(2);
    p->p->p = new Test3(3);
    p->p->p->msg();
    
    p->p->p->p = p->p;		// circular link
    p->p = new Test3(4);    // unlink object 3 from root

    ::std::this_thread::sleep_for(::std::chrono::milliseconds(1000));
    GCDebug::out("3.2. Test3 2,3 deleted?");

    // 3.3. Method calls"
    GCDebug::out("3.3. Method calls");    

    p->msg();                // method calls
    p->p->msg();

    // 3.4. Force deallocate"
    GCDebug::out("3.4. Force deallocate");    
    
    // Test3 5 now is lvalue and finalizable
    GCPointer<Test3> c1 = new Test3(5);

    // Add a reference
    GCPointer<Test3> c2 = c1;

    // make Test3 not finalizable
    c1.gc_make_nonfinalizable();
    c1.gc_force_deallocate();

    ::std::this_thread::sleep_for(::std::chrono::milliseconds(1000));
    GCDebug::out("3.5. Test3 5 NOT deleted?");

    // Finalize object
    c1.gc_make_finalizable();
    c1.gc_force_deallocate();

    ::std::this_thread::sleep_for(::std::chrono::milliseconds(1000));
    GCDebug::out("3.6. Test3 5 deleted?");

    // 3.7. Scoped pointers
    GCDebug::out("3.7. Scoped pointers");
    
    // A pointer function
    GCPointer<Test3> c3 = new Test3(1000);
    test3_sub1(c3);

    // A unique pointer function
    GCUniquePointer<Test3> c4(new Test3(2000));
    test3_sub2(::std::move(c4));


    // 3.8. Generating temporally reachable objects
    GCDebug::out("3.8. Generating temporally reachabe objects");

    GCPointer<Test3> q;
    for(int n = 6; n < 12; n++ ) {
        q = new Test3(n);
    }

    GCDebug::out("3.9. accessing to objects of static pointers");
    
    Test3::s = new Other(111);
    Test3::s->msg();

    // Cleaning

    q = nullptr;
    p = nullptr;
    c3 = nullptr;
    c4 = nullptr;

    ::std::this_thread::sleep_for(::std::chrono::milliseconds(1000));
}
