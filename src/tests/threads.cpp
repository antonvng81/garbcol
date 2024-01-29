#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "../main/gc.h"

using namespace GCNamespace;

void test10();

int main() {

    GCCollector collector_start(100, []{
        test10();
        GCDebug::out("exit!", GCDebug::notify);
    });
}