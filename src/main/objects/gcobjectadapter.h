///////////////////////////////////////////////////////////////////////////////
// File: gcobjectadapter.h
// Version: 0.2
// Description:
// pointer contents

#ifndef _GC_OBJECTADAPTER_H
#define _GC_OBJECTADAPTER_H

#include "gcchildnodebase.h"
#include "gcobject.h"

namespace GCNamespace {

class GCContainer_B_;

// Forward declare
template<class, class, bool> class GCPointer;

///////////////////////////////////////////////////////////////////////////////
// adapter to use non-GCObject derived classes with pointers

template<class _Type>
class GCObjectAdapter : public GCObject_B_{

    template<class _TypePP, class _PointerBasePP, bool _TypeIsObjectPP>
    friend class GCPointer;

    unsigned char                       flags;

protected:    

    _Type*                              adaptee;

public:
    GCObjectAdapter();
    GCObjectAdapter(_Type*const);
    ~GCObjectAdapter() override;

    ::std::size_t                       gc_get_class_id() const override;

    void                                gc_mark() override;
    bool                                gc_is_marked() const override;

    const GCContainer_B_*               gc_get_const_children() const override;

    void                                gc_make_nonfinalizable() override;
    void                                gc_make_finalizable() override;
    bool                                gc_is_finalizable() const override;

    void                                gc_make_rvalue() override;
    void                                gc_make_lvalue() override;
    bool                                gc_is_lvalue() const override;

    void                                gc_deallocate() override;
    bool                                gc_is_finalized() const override;

    void                                gc_force_deallocate() override;
    bool                                gc_is_force_finalized() const override;

};

}

#ifndef _GC_HIDE_METHODS

#include "../collector/gccollector.h"
#include "../collector/gcflags.h"

namespace GCNamespace {

template<class _Type>
GCObjectAdapter<_Type>::GCObjectAdapter() {
    
    flags = 0;
    adaptee = nullptr;
    // it is rvalue by default
}

template<class _Type>
GCObjectAdapter<_Type>::GCObjectAdapter(_Type*const other) {
    flags = 0;    
    adaptee = other;
    // it is rvalue by default
}

template<class _Type>
GCObjectAdapter<_Type>::~GCObjectAdapter() {
    
    if(adaptee != nullptr) {
        delete adaptee;
        adaptee = nullptr;
    }
}

template<class _Type>
void GCObjectAdapter<_Type>::gc_mark() {
    flags &= ~GCFlags::gc_mark_bit;
    flags |= GCCollector::collector->mark_bit_value;
    flags &= ~GCFlags::gc_deallocate_bit;
}

template<class _Type>
bool GCObjectAdapter<_Type>::gc_is_marked() const {
    return (flags & GCFlags::gc_mark_bit) == (GCCollector::collector->mark_bit_value & GCFlags::gc_mark_bit);
}


template<class _Type>
const GCContainer_B_* GCObjectAdapter<_Type>::gc_get_const_children() const {
    return nullptr;
}

template<class _Type>
void GCObjectAdapter<_Type>::gc_make_finalizable() {
    flags &= ~GCFlags::gc_nonfinalizable_bit;
}

template<class _Type>
void GCObjectAdapter<_Type>::gc_make_nonfinalizable() {
    flags |= GCFlags::gc_nonfinalizable_bit;
}

template<class _Type>
bool GCObjectAdapter<_Type>::gc_is_finalizable() const {
    return !(flags & GCFlags::gc_nonfinalizable_bit);
}

template<class _Type>
void GCObjectAdapter<_Type>::gc_make_rvalue() {
    flags &= ~GCFlags::gc_lvalue_bit;
}

template<class _Type>
void GCObjectAdapter<_Type>::gc_make_lvalue() {
    // it has not children objects
    flags |= GCFlags::gc_lvalue_bit;
}

template<class _Type>
bool GCObjectAdapter<_Type>::gc_is_lvalue() const {
    return flags & GCFlags::gc_lvalue_bit;
}

template<class _Type>
void GCObjectAdapter<_Type>::gc_deallocate(){
    if (gc_is_finalizable()) {
        flags |= GCFlags::gc_deallocate_bit;
    }
}

template<class _Type>
void GCObjectAdapter<_Type>::gc_force_deallocate(){
    if (gc_is_finalizable()) {
        flags |= GCFlags::gc_force_deallocate_bit;
    }
}


template<class _Type>
bool GCObjectAdapter<_Type>::gc_is_force_finalized() const{
    return flags & GCFlags::gc_force_deallocate_bit;    
}

template<class _Type>
bool GCObjectAdapter<_Type>::gc_is_finalized() const {
    return flags & GCFlags::gc_deallocate_bit;
}

template<class _Type>
::std::size_t GCObjectAdapter<_Type>::gc_get_class_id() const {
    return typeid(*this).hash_code();
}


}

#endif


#endif // _GC_OBJECTADAPTER_H

