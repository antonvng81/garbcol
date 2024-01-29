#define _GC_HIDE_METHODS

#include "../collector/gccore.h"
#include <chrono>
#include <thread>
#include <functional>
#include "gccollector.h"

namespace GCNamespace {

GCCollector* GCCollector::collector;
gc_static_pointer_heap_t GCCollector::static_pointer_heap;

void GCCollector::object_heap_push(GCObject_B_* object)
{
    ::std::lock_guard<::std::mutex> l(mutex);

    if (object != nullptr) {
        // Push object 
        object_heap.push_back(object);
    }
}

void GCCollector::thread_heap_push(GCThreadFunction *thread_function)
{
    thread_function_heap.push_back(thread_function);
    thread_function->position=--(thread_function_heap.end());
}

void GCCollector::thread_heap_remove(GCThreadFunction *thread_function)
{
    *(thread_function->position) = thread_function_heap.back();
    thread_function_heap.pop_back();
}

GCScopeStack* GCCollector::get_scope_stack()
{
    return GCThreadFunction::thread_function->scope_stack;
}

void GCCollector::free_object_heap()
{
    // delete all objects
    for(auto object: object_heap)
    {
        delete object;
    }
    static_pointer_heap.clear();  
    delete main_thread_function;  
}

void GCCollector::mark() {

    for(GCThreadFunction* thread_function : thread_function_heap)
    {
        // setting local thread temporally
        GCThreadFunction::thread_function = thread_function;

        // Create a object for iterate over tree of containers
        GCMarkState mark_state;

        // root scope object
        mark_state.gc_set_scope(get_scope_stack()->root_scope);
        mark_state.gc_mark_all();

        // rvalue objects
        for( GCObject* obj : get_scope_stack()->rvalue_stack)
        {
            obj->gc_mark();
            if(!obj->gc_get_const_children()->gc_is_empty()) {
                mark_state.gc_clear();
                mark_state.gc_set_scope(obj->children);
                mark_state.gc_mark_all();
            }
        }
    }

    // change mark bit value of collector
    mark_bit_value ^= GCFlags::gc_mark_bit;
}

void GCCollector::sweep()
{
    // Create sweep state object
    GCSweepState sweep_state(&object_heap);

    // Sweep all objects
    sweep_state.gc_sweep_all(); 
}

void GCCollector::collect()
{  
    bool first = true;

    while (!collector->exit_flag) {
        
        if (!first) {
            collector->mark();
            collector->sweep();
        }

        auto step_time = ::std::chrono::milliseconds(collector->gc_get_sleep_time());
        ::std::this_thread::sleep_for(step_time);
        first = false;
    }

}

GCCollector::GCCollector(int _sleep_time, ::std::function<void(void)> fnc)
{
    collector = this;
    mark_bit_value = GCFlags::gc_mark_bit;
    exit_flag = false;
    sleep_time = _sleep_time;
    main_thread_function = new GCThreadFunction();

    // Custom thread for collect function
    garbcol_std_thread = std::thread(&GCCollector::collect);

    // create static objects
    for(auto position_static_pointer: static_pointer_heap) {
        (*position_static_pointer).constructor();
    }

    if (fnc != nullptr) {
        fnc();
    }
}

GCCollector::~GCCollector()
{
    sleep_time = 0;
    exit_flag = true;
    if(garbcol_std_thread.joinable()){
        garbcol_std_thread.join();
    }    
    free_object_heap();

}

void GCCollector::gc_set_sleep_time(::std::size_t _sleep_time)
{
    sleep_time = _sleep_time;
}

::std::size_t GCCollector::gc_get_sleep_time() const
{
    return sleep_time;
}

}

//end
