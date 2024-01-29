#define _GC_HIDE_METHODS

#include "../collector/gccore.h"
#include <stdexcept>

namespace GCNamespace {

void GCWeakPointerMethods::gc_copy(const GCPointer_B_& other) {

    if(other.gc_get_pointer_type() == GCPointerType::unique_pointer) 
    {
        throw ::std::invalid_argument( "weak pointer from unique pointer not allowed" );
    }
    else{
        object = other.gc_get_object();
    }
}


void GCWeakPointerMethods::gc_copy(GCPointer_B_&& other) {

    if(other.gc_get_pointer_type() == GCPointerType::unique_pointer) 
    {
        throw ::std::invalid_argument( "weak pointer from unique pointer not allowed" );
    }
    else{
        object = other.gc_get_object();
    }
}


void GCWeakPointerMethods::gc_set_object(GCObject_B_*const& obj) {
    throw ::std::invalid_argument( "weak pointer from raw pointer not allowed" );
}


void GCWeakPointerMethods::gc_set_object(GCObject_B_*&& obj) {
    throw ::std::invalid_argument( "weak pointer from raw pointer not allowed" );
}


GCObject_B_* GCWeakPointerMethods::gc_get_object() const {
    return object;
}


const GCObject_B_* GCWeakPointerMethods::gc_get_const_object() const {
    return object;
}

void GCWeakPointerMethods::gc_force_deallocate(){
    object->gc_force_deallocate();
}

void GCWeakPointerMethods::gc_deallocate(){
    object->gc_deallocate();
}

void GCWeakPointerMethods::gc_make_nonfinalizable() const{
    object->gc_make_nonfinalizable();
}


void GCWeakPointerMethods::gc_make_finalizable() const{
    object->gc_make_finalizable();
}


bool GCWeakPointerMethods::gc_is_finalizable() const{
    return object->gc_is_finalizable();
}



void GCWeakPointerMethods::gc_mark() const{
    object->gc_mark();
}


bool GCWeakPointerMethods::gc_is_empty() const{
    return (object == nullptr);
}


bool GCWeakPointerMethods::gc_is_marked() const{
    return object->gc_is_marked();
}


const GCContainer_B_* GCWeakPointerMethods::gc_get_const_children() const {
    return object->gc_get_const_children();
}


bool GCWeakPointerMethods::gc_check_n_clear() const {

    if (object == nullptr)
        return true;

    if (object->gc_is_force_finalized()) {
        object = nullptr;
        return true;
        // object will not be deleted automatically since it is weak pointer
    }
    return false;
}

}