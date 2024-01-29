#define _GC_HIDE_METHODS

#include "../collector/gccore.h"
#include <stdexcept>

namespace GCNamespace {


void GCUniquePointerMethods::gc_copy(const GCPointer_B_&) {
    throw ::std::invalid_argument("unique pointer from lvalue not allowed");
}


void GCUniquePointerMethods::gc_copy(GCPointer_B_&& other) {

    if(other.gc_get_pointer_type() == GCPointerType::unique_pointer) {
        
        // Setting object
        object = other.gc_get_object();
    }
    else{
        throw ::std::invalid_argument( "unique pointer from another type rvalue not allowed");
    }
}


void GCUniquePointerMethods::gc_set_object(GCObject_B_*&& obj) {

    // If you use ::std::move(obj), be sure that obj is not 
    // pushed to heap yet

    if (obj != nullptr) {
        // Default new objects are rvalue
        obj->gc_make_lvalue();
        GCCollector::collector->object_heap_push(obj);
    }

    // Setting object
    object = obj;
 
}


void GCUniquePointerMethods::gc_set_object(GCObject_B_*const&) {
    throw ::std::invalid_argument( "unique pointer initialization from lvalue");
}


GCObject_B_* GCUniquePointerMethods::gc_get_object() const{
    return object;
}


const GCObject_B_* GCUniquePointerMethods::gc_get_const_object() const{
    return object;
}

void GCUniquePointerMethods::gc_deallocate(){
    object->gc_deallocate();
}

void GCUniquePointerMethods::gc_force_deallocate(){
    object->gc_force_deallocate();
}

void GCUniquePointerMethods::gc_make_nonfinalizable() const{
    object->gc_make_nonfinalizable();
}


void GCUniquePointerMethods::gc_make_finalizable() const{
    object->gc_make_finalizable();
}


bool GCUniquePointerMethods::gc_is_finalizable() const{
    return object->gc_is_finalizable();
}


void GCUniquePointerMethods::gc_mark() const{
    object->gc_mark();
}


bool GCUniquePointerMethods::gc_is_empty() const{
    return (object == nullptr);
}


bool GCUniquePointerMethods::gc_is_marked() const{
    return object->gc_is_marked();
}


const GCContainer_B_* GCUniquePointerMethods::gc_get_const_children() const {
    return object->gc_get_const_children();
}


bool GCUniquePointerMethods::gc_check_n_clear() const {

    if (object == nullptr)
        return true;

    if (object->gc_is_force_finalized()) {
        object = nullptr;
        return true;
    }
    return false;
}


}
