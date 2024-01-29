///////////////////////////////////////////////////////////////////////////////
// File: gccollector.h
// Version: 0.2
// Description:
// collector manager

#ifndef _GC_COLLECTOR_H
#define _GC_COLLECTOR_H

#include <vector>
#include <list>
#include <functional>
#include <thread>
#include <mutex>

#include "gctypes.h"
#include "../pointers/gcpointertype.h"

namespace GCNamespace {

class GCObject_B_;
class GCThreadFunction;
class GCScopeStack;

///////////////////////////////////////////////////////////////////////////////
// garbage collector main object

class GCCollector {

    //friends
    friend class                        GCThreadFunction;
    template<class> friend class        GCConstructorFunction;
    template<class> friend class        GCDestructorFunction;
    template<GCPointerType,GCPointerType> friend class GCSharedPointerCore;
    template<GCPointerType,GCPointerType> friend class GCWeakPointerCore;
    template<GCPointerType,GCPointerType> friend class GCUniquePointerCore;
    friend class                        GCSharedPointerMethods;
    friend class                        GCWeakPointerMethods;
    friend class                        GCUniquePointerMethods;
    friend class                        GCObject; 
    template<class> friend class        GCObjectAdapter; 
    friend class                        GCSweepState;

    //data members
    gc_thread_heap_t                    thread_function_heap;
    ::std::thread                       garbcol_std_thread;
    ::std::mutex                        mutex;
    unsigned char                       mark_bit_value;
    bool                                exit_flag; 
    ::std::size_t                       sleep_time;
    GCThreadFunction*                   main_thread_function;
    gc_object_heap_t                    object_heap;
    static GCCollector*                 collector;
    static gc_static_pointer_heap_t     static_pointer_heap;

    //methods
    void                                mark();
    void                                sweep();
    static void                         collect();
    void                                free_object_heap();
    void                                free_static_pointer_heap();

    void                                object_heap_push(GCObject_B_*);
    void                                thread_heap_push(GCThreadFunction*);
    void                                thread_heap_remove(GCThreadFunction*);
    GCScopeStack*                       get_scope_stack();

public:

    // Methods
    void                                gc_set_sleep_time(::std::size_t );
    ::std::size_t                       gc_get_sleep_time() const;

    // Cts. Dts.
    GCCollector(int n=100,::std::function<void(void)> fnc=nullptr);
    ~GCCollector();
};

}

#endif // _GC_COLLECTOR_H