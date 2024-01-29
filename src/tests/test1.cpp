#include <iostream>
#include <string>
#include <thread>
#include <chrono>


#include "../main/gc.h"

using namespace GCNamespace;

void test1() {

    GCDebug::out("[test 1]************************************");
    GCDebug::out("Dealing with basic GCPointer functions:");

    // 1.1. Setting a object
    GCDebug::out("1.1. Setting a object");

    // Create a pointer and store in GCPointer
    GCPointer<int> i = new int;

    // Access to content
    *i = 3;

    GCDebug::out("*i = " + ::std::to_string(*i));    

    // 1.2. Creating an array of pointers
    GCDebug::out("1.2. Creating an array of pointers");    
    
    // Create an array of pointers
    GCPointer<::std::string> s[3];

    s[0] = new ::std::string("Hello...");
    s[1] = new ::std::string("...");
    s[2] = new ::std::string("...World?");
    
    // Change object
    s[2] = new ::std::string("..World!"); // "world?" will ve removed automatically

    // Use indices
    for(*i = 0; *i < 3; (*i)++ )
        GCDebug::out(*s[*i]);


    // 1.3. Generating temporally reachable objects
    GCDebug::out("1.3. Generating temporally reachable objects");    

    // Generate temporally reachable objects
    for(int n = 0; n < 6; n++ ) {
        i = new int{n};
        GCDebug::out("*i = " + ::std::to_string(*i));    
    }


    // 1.4. Access to function members of object
    GCDebug::out("1.4. Access to function members of object");    

    // Access to function members of object
    GCPointer<::std::string> s2 = new ::std::string("New ");
    s2->append("hello World!");
    GCDebug::out(*s2);

    // 1.5. An unique pointer only can ::std::move to other pointer
    GCDebug::out("1.5. An unique pointer only can ::std::move to other pointer");    

    // An unique pointer only can ::std::move to other pointer
    GCUniquePointer<::std::string> us = new ::std::string("Unique pointer");
    s2 = ::std::move(us); // s2 = us; --> compile time error
    GCDebug::out(*s2);

    // Weak pointer does nothing
    GCWeakPointer<::std::string> ws = s2;
    s2 = nullptr;

    ::std::this_thread::sleep_for(::std::chrono::milliseconds(1000));
}

