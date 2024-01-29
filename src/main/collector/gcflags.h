///////////////////////////////////////////////////////////////////////////////
// File: gcflags.h
// Version: 0.2
// Description:
// Marking flags for a garbage collector pointer

#ifndef _GC_FLAGS_H
#define _GC_FLAGS_H

namespace GCNamespace {

namespace GCFlags {

    // Flags for marking algorithms
    constexpr unsigned char gc_lvalue_bit                  = 0b000001; // object not stored in a pointer yet
    constexpr unsigned char gc_mark_bit                    = 0b000010; // GC marks as connected here
    constexpr unsigned char gc_nonfinalizable_bit          = 0b000100; // not to delete by garbage mark&sweep algorithm
    constexpr unsigned char gc_deallocate_bit              = 0b001000; // force to deallocate}
    constexpr unsigned char gc_force_deallocate_bit        = 0b010000; // force to deallocate}
}

}
#endif // _GC_FLAGS_H