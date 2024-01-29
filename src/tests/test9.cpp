#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "../main/gc.h"

using namespace GCNamespace;


void test9() {

    GCDebug::out("[test 9]************************************");
    GCDebug::out("Testing speed performance:");

    int time_tick_max = 0;
    int time_tick_min = 1000000;
    int MAX_TICKS = 20;

    GCDebug::out("[Please, wait. Testing GC interruptions time]");



    ///////////////////////////////////////////////////////////////////////////////

    auto
    time_start = ::std::chrono::steady_clock::now();

    for (int n=0;n<MAX_TICKS; n++)
    {
        auto
        time_tick_start = ::std::chrono::steady_clock::now();

        for (int i=0;  i<10;  i++)
        {
            GCPointer<int>  x = new int;
            for(int ii=0; ii<10; ii++) {
               GCPointer<int>  y = new int;
               x = y;
            }
        }

        auto
        time_tick_end = ::std::chrono::steady_clock::now();

        int
        time_tick_length =  ::std::chrono::duration_cast<::std::chrono::microseconds>(
                time_tick_end - time_tick_start
                ).count();

        if (time_tick_length > time_tick_max){
            time_tick_max = time_tick_length;
        }

        if (time_tick_length < time_tick_min){
            time_tick_min = time_tick_length;
        }
    }

    auto
    time_end = ::std::chrono::steady_clock::now();


    int
    time_length = ::std::chrono::duration_cast<::std::chrono::microseconds>(
                time_end - time_start
                ).count();

    GCDebug::out( ::std::string("gc-RESULTS:\n") +
    ::std::string("total mcs)  = ") + ::std::to_string(time_length) + "\n" +
    ::std::string("max tick   = ") + ::std::to_string(time_tick_max) + "\n" +
    ::std::string("min tick   = ") + ::std::to_string(time_tick_min) + "\n" +
    ::std::string("max - min  = ") + ::std::to_string(time_tick_max-time_tick_min) + "\n");

    ///////////////////////////////////////////////////////////////////////////////

    time_tick_max = 0;
    time_tick_min = 1000000;

    GCDebug::out("[Please, wait. Testing standard C++ time]");
    ::std::this_thread::sleep_for(::std::chrono::milliseconds(1000));

    auto
    time_start_std = ::std::chrono::steady_clock::now();

    for (int n=0;n<MAX_TICKS; n++) {

        // TICK PROCESS
        auto
        time_tick_start_std = ::std::chrono::steady_clock::now();

        for (int i=0;  i<10;  i++){
            int*  x = new int;
            for (int ii=0; ii<10; ii++) {
               int*  y = new int;
               delete y;
               y = x;
            }
            delete x;
        }

        auto
        time_tick_end_std = ::std::chrono::steady_clock::now();

        int
        time_tick_length_std =  ::std::chrono::duration_cast<::std::chrono::microseconds>(
                    time_tick_end_std-time_tick_start_std
                    ).count();

        if (time_tick_length_std > time_tick_max){
            time_tick_max = time_tick_length_std;
        }

        if (time_tick_length_std < time_tick_min){
            time_tick_min = time_tick_length_std;
        }
    }

    auto
    time_end_std = ::std::chrono::steady_clock::now();

    time_length = ::std::chrono::duration_cast<::std::chrono::microseconds>(
                time_end_std-time_start_std
                ).count();

    GCDebug::out( ::std::string("STD-RESULTS:\n") +
    ::std::string("total mcs)  = ") + ::std::to_string(time_length) + "\n" +
    ::std::string("max tick   = ") + ::std::to_string(time_tick_max) + "\n" +
    ::std::string("min tick   = ") + ::std::to_string(time_tick_min) + "\n" +
    ::std::string("max - min  = ") + ::std::to_string(time_tick_max-time_tick_min) + "\n");

}