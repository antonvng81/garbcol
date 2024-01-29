#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "../main/gc.h"

using namespace GCNamespace;

// Standard base class
class Test2Base {
public:
    int n;
    virtual ~Test2Base() {
        GCDebug::out( "Test2Base " + ::std::to_string(n) + " deleted");
    }
};

// Standard derived class
class Test2 : public Test2Base
{
public:
    Test2(int a) {
        n = a;
        GCDebug::out( "Test2 " + ::std::to_string(n) + " created");
    }

    ~Test2() override {
        GCDebug::out("Test2 " + ::std::to_string(n) + " deleted");
    }
};

void test2() {

    GCDebug::out("[test 2]************************************");
    GCDebug::out("Casting a pointer to another:");

    // 2.1. Casting to base pointer
    GCDebug::out("2.1. Casting to base pointer");    

    GCPointer<Test2Base> a = new Test2Base();
    GCPointer<Test2> b = new Test2(1);

    // Cast a pointer
    a = (GCPointer<Test2Base>) b;

    // Cleaning 
    a = nullptr;
    b = nullptr;
    
    // Wait some time until garbage collector do cleaning
    ::std::this_thread::sleep_for(::std::chrono::milliseconds(1000));
    GCDebug::out("2.2. Test2 1 deleted?");
}
