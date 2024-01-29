#define _GC_HIDE_METHODS

#include "../collector/gccore.h"

namespace GCNamespace {

GCObject::GCObject() {

    //create scope object
    children = new GCScope;

    flags = 0;
    // it is rvalue by default

    // Push current context and set this one
    GCCollector::collector->get_scope_stack()->gc_object_on_new(this);    
}

GCObject::~GCObject() {    
    // Push current context and set this one
    GCCollector::collector->get_scope_stack()->gc_object_on_exit_delete();

    // remove object
    delete children;
}

::std::size_t GCObject::gc_get_class_id() const{
    return class_id;
}

void GCObject::gc_mark() {
    flags &= ~GCFlags::gc_mark_bit;
    flags |= GCCollector::collector->mark_bit_value;
    flags &= ~GCFlags::gc_deallocate_bit;
}

bool GCObject::gc_is_marked() const {
    return (flags & GCFlags::gc_mark_bit) == (GCCollector::collector->mark_bit_value & GCFlags::gc_mark_bit);
}

const GCContainer_B_* GCObject::gc_get_const_children() const {
    return children;
}

void GCObject::gc_make_finalizable() {
    flags &= ~GCFlags::gc_nonfinalizable_bit;
}

void GCObject::gc_make_nonfinalizable() {
    flags |= GCFlags::gc_nonfinalizable_bit;
}

bool GCObject::gc_is_finalizable() const {
    return !(flags & GCFlags::gc_nonfinalizable_bit);
}

void GCObject::gc_make_rvalue() {
    flags &= ~GCFlags::gc_lvalue_bit;
}

void GCObject::gc_make_lvalue() {

    // Push current context and set this one
    GCCollector::collector->get_scope_stack()->gc_object_make_lvalue(this);

    flags |= GCFlags::gc_lvalue_bit;
}


bool GCObject::gc_is_lvalue() const {
    return flags & GCFlags::gc_lvalue_bit;
}

void GCObject::gc_deallocate(){    
    if (gc_is_finalizable()) {
        flags |= GCFlags::gc_deallocate_bit;
    }
}

bool GCObject::gc_is_finalized() const {
    return flags & GCFlags::gc_deallocate_bit;
}

bool GCObject::gc_is_force_finalized() const{
    return flags & GCFlags::gc_force_deallocate_bit;    
}

void GCObject::gc_force_deallocate(){    
    if (gc_is_finalizable()) {
        flags |= GCFlags::gc_force_deallocate_bit;
    }
}

}

//end
