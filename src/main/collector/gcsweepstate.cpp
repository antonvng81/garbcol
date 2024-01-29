#define _GC_HIDE_METHODS

#include "../collector/gccore.h"
#include <thread>
#include <mutex>

namespace GCNamespace {

GCSweepState::GCSweepState(::std::vector<GCObject_B_*>* hp)
{
    object_heap = hp;
    position = object_heap->begin();
}

GCSweepState::~GCSweepState()
{
    // nothing
}

void GCSweepState::gc_position_erase()
{   
    ::std::lock_guard<::std::mutex> l(GCCollector::collector->mutex);
    
    auto object = *position;

    if (object != nullptr) 
    {       
        delete object;
    }

    *position = object_heap->back();
    object_heap->pop_back(); 

    if (object_heap->empty()) {
        position = object_heap->end();
    }
}

void GCSweepState::gc_position_next() {
    ++position;  
}

bool GCSweepState::gc_sweep_next()
{
    if (position == object_heap->end()){
        return false;
    }

    auto object = *position;

    if (object->gc_is_finalized() || object->gc_is_force_finalized())
    {
        // Externally finalized object
        gc_position_erase();
        return true;
    }
    else 
    // Check object is lvalue
    if (object->gc_is_lvalue())
    {
        // Check object is marked to be deleted
        if (object->gc_is_marked())
        {
            // Check that object is finalizable
            if (object->gc_is_finalizable())
            {                
                // Finalized from GC
                object->gc_deallocate();
            }    
        }
    }

    gc_position_next();
    return true;
}

void GCSweepState::gc_sweep_all() {
    while (gc_sweep_next()) {
        // go next
    }
}

}

//end
