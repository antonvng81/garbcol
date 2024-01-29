#define _GC_HIDE_METHODS

#include "../collector/gccore.h"
#include <functional>

namespace GCNamespace {

thread_local GCThreadFunction* GCThreadFunction::thread_function;

GCThreadFunction::GCThreadFunction(std::function<void(void)> fnc)
{
    // one local thread
    thread_function = this;

    // setting scope
    scope_stack = new GCScopeStack;

    GCCollector::collector->thread_heap_push(this);

    if (fnc != nullptr) {
        fnc();
    }
}

GCThreadFunction::~GCThreadFunction()
{       
    GCCollector::collector->thread_heap_remove(this);
    
    if (scope_stack != nullptr) {
        delete scope_stack;
    }

    scope_stack = nullptr;
    thread_function = nullptr;
}

}