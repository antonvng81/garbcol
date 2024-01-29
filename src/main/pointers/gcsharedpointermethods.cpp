#define _GC_HIDE_METHODS

#include "../collector/gccore.h"
#include <stdexcept>

namespace GCNamespace {

///////////////////////////////////////////////////////////////////////////////
// Shared pointer methods not from container specialization


void GCSharedPointerMethods::gc_copy(const GCPointer_B_& other) {

    if(other.gc_get_pointer_type() == GCPointerType::unique_pointer) {
        throw ::std::invalid_argument( "shared pointer from lvalue unique pointer not allowed" );
    }
    else {
        object = other.gc_get_object();
    }
}


void GCSharedPointerMethods::gc_copy(GCPointer_B_&& other) {

    object = other.gc_get_object();
}


void GCSharedPointerMethods::gc_set_object(GCObject_B_*&& obj) {

    // If you use ::std::move(obj), be sure that obj is not 
    // pushed into heap yet

    if (obj != nullptr) 
    {   
        // Default new objects are rvalue
        obj->gc_make_lvalue();
        GCCollector::collector->object_heap_push(obj);
    }

    // Setting object
    object = obj;
}



void GCSharedPointerMethods::gc_set_object(GCObject_B_ *const& obj) {

    if (obj != nullptr) 
    {
        // Only push to heap when it is not an lvalue
        if (!obj->gc_is_lvalue()) {
            obj->gc_make_lvalue();
            GCCollector::collector->object_heap_push(obj);
        }
    }

    // Setting object
    object = obj;
}


GCObject_B_* GCSharedPointerMethods::gc_get_object() const {
    return object;
}


const GCObject_B_* GCSharedPointerMethods::gc_get_const_object() const {
    return object;
}

void GCSharedPointerMethods::gc_deallocate(){
    object->gc_deallocate();
}

void GCSharedPointerMethods::gc_force_deallocate(){
    object->gc_force_deallocate();
}


void GCSharedPointerMethods::gc_make_nonfinalizable() const{
    object->gc_make_nonfinalizable();
}


void GCSharedPointerMethods::gc_make_finalizable() const{
    object->gc_make_finalizable();
}


bool GCSharedPointerMethods::gc_is_finalizable() const{
    return object->gc_is_finalizable();
}


void GCSharedPointerMethods::gc_mark() const{
    object->gc_mark();
}


bool GCSharedPointerMethods::gc_is_empty() const{
    return (object == nullptr);
}


bool GCSharedPointerMethods::gc_is_marked() const{
    return object->gc_is_marked();
}


const GCContainer_B_* GCSharedPointerMethods::gc_get_const_children() const {
    return object->gc_get_const_children();
}


bool GCSharedPointerMethods::gc_check_n_clear() const {

    if (object == nullptr) {
        return true;
    }
    else if (object->gc_is_force_finalized()) {
        object = nullptr;               
        return true;
        // Object is set to nullptr since it will be deleted
    }

    return false;
}

}

//end
