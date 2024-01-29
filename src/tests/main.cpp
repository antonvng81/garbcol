#include "../main/gc.h"

using namespace GCNamespace;

void test0();
void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void test8();
void test9();

int main(){
    
    GCCollector new_collector(100);
    
    test0();
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();    
    test8();    
    test9();

    GCDebug::out("exit!", GCDebug::notify);

    return 0;
}