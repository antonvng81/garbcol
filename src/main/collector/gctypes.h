///////////////////////////////////////////////////////////////////////////////
// File: gctypes.h
// Version: 0.2
// Description:
// renaming some types

#ifndef _GC_TYPES_H
#define _GC_TYPES_H

#include <vector>

namespace GCNamespace {

    class GCObject_B_;
    class GCThreadFunction;
    class GCContructorMethods;

    using gc_object_heap_t = ::std::vector<GCObject_B_*>;
    using gc_thread_heap_t = ::std::vector<GCThreadFunction*>;
    using gc_static_pointer_heap_t = ::std::vector<GCContructorMethods*>;
}

#endif