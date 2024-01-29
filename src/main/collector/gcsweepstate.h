///////////////////////////////////////////////////////////////////////////////
// File: gcsweepstate.h
// Version: 0.2
// Description:
// sweep state

#ifndef _GC_SWEEPSTATE_H
#define _GC_SWEEPSTATE_H

#include <vector>
#include "gctypes.h"
#include <thread>
#include <mutex>

namespace GCNamespace{

class GCObject_B_;

///////////////////////////////////////////////////////////////////////////////
// GCSweepState

class GCSweepState {

    gc_object_heap_t*                   object_heap;
    gc_object_heap_t::iterator          position;

public:

    GCSweepState(gc_object_heap_t* hp);
    ~GCSweepState();

    bool                                gc_sweep_next();
    void                                gc_position_erase();
    void                                gc_position_next();
    void                                gc_sweep_all();

};

}

#endif // _GC_SWEEPSTATE_H