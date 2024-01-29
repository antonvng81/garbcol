#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "../main/gc.h"

using namespace GCNamespace;

thread_local int thread_x;
int thread_count = 0;
const int THREAD_MAX =4;

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void test8();
void test9();

GCStaticSharedPointer<int> s;

void thread_fn() {
    
    // Each thread Must be conneccted to grabage collector
    GCThreadFunction thread_start([&](){

    thread_count++;
    thread_x = thread_count;
    
    ::std::this_thread::sleep_for(::std::chrono::milliseconds(rand()%20));
    if(rand()%20 > 10){
        *s = thread_count;
    }
    else {
        s = new int;
    }

    test1();
    GCDebug::out("exit test1",GCDebug::notify);

    test2();
    GCDebug::out("exit test2",GCDebug::notify);

    test3();
    GCDebug::out("exit test3",GCDebug::notify);

    test4();
    GCDebug::out("exit test4",GCDebug::notify);

    test5();
    GCDebug::out("exit test5",GCDebug::notify);

    test6();
    GCDebug::out("exit test6",GCDebug::notify);

    test7();
    GCDebug::out("exit test7",GCDebug::notify);

    test8();
    GCDebug::out("exit test8",GCDebug::notify);

    test9();
    GCDebug::out("exit test9",GCDebug::notify);
    });
}


void test10() {

    GCDebug::out("[test 10]************************************");
    GCDebug::out("Testing threads performance:");
    GCDebug::set_mode(GCDebug::notify);

    s = new int;

    std::thread new_thread[THREAD_MAX];

    for (int n = 0; n < THREAD_MAX; n++){
        new_thread[n] = std::thread(&thread_fn);
    }

    for (int n = 0; n < THREAD_MAX; n++){
        while(true) {
            if( new_thread[n].joinable()) {
                new_thread[n].join();
                break;
            }
        }
    }

}