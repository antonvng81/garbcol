///////////////////////////////////////////////////////////////////////////////
// File: gcpointerbase.h
// Version: 0.2
// Description:
// base pointer

#ifndef _GC_POINTERBASE_H
#define _GC_POINTERBASE_H

#include "gcpointertype.h"

namespace GCNamespace {

class GCNullPointer;
class GCContainer_B_;
class GCObject_B_;

///////////////////////////////////////////////////////////////////////////////
// interface for GC managed objects

class GCPointer_B_{
public:

    virtual                             ~GCPointer_B_() {}

    virtual bool                        gc_is_empty() const = 0;

    virtual void                        gc_copy(const GCPointer_B_&) = 0;
    virtual void                        gc_copy(GCPointer_B_&&) = 0;

    virtual void                        gc_set_object(GCObject_B_*const&) = 0;
    virtual void                        gc_set_object(GCObject_B_*&&) = 0;

    virtual GCObject_B_*                gc_get_object() const = 0;
    virtual const GCObject_B_*          gc_get_const_object() const = 0;

    virtual void                        gc_mark() const = 0;
    virtual bool                        gc_is_marked() const = 0;

    virtual const GCContainer_B_*       gc_get_const_children() const = 0;

    virtual void                        gc_make_nonfinalizable() const = 0;
    virtual void                        gc_make_finalizable() const = 0;
    virtual bool                        gc_is_finalizable() const = 0;

    virtual const GCPointerType         gc_get_pointer_type() const = 0;

    virtual void                        gc_deallocate() = 0;
    virtual void                        gc_force_deallocate() = 0;
    virtual bool                        gc_check_n_clear() const = 0;

    bool                                operator== (const GCNullPointer&) const
                                        { return gc_get_const_object()==nullptr;}

    bool                                operator!= (const GCNullPointer&) const
                                        { return gc_get_const_object()!=nullptr;}

    bool                                operator== (const GCPointer_B_& other) const
                                        { return gc_get_const_object()==other.gc_get_const_object();}

    bool                                operator!= (const GCPointer_B_& other) const
                                        { return gc_get_const_object()!=other.gc_get_const_object();}

    bool                                operator< (const GCPointer_B_& other) const
                                        { return gc_get_const_object()<other.gc_get_const_object();}

    bool                                operator> (const GCPointer_B_& other) const
                                        { return gc_get_const_object()>other.gc_get_const_object();}

    bool                                operator<= (const GCPointer_B_& other) const
                                        { return gc_get_const_object()<=other.gc_get_const_object();}

    bool                                operator>= (const GCPointer_B_& other) const
                                        { return gc_get_const_object()>=other.gc_get_const_object();}

};

///////////////////////////////////////////////////////////////////////////////
// interface for a null pointer type

class GCNullPointer : public GCPointer_B_{
protected:

    friend class                        GCSweepState;

    GCObject_B_*                        gc_get_object() const override {return nullptr;}
    void                                gc_copy(const GCPointer_B_&) override {}
    void                                gc_copy(GCPointer_B_&&) override {}    
    void                                gc_make_nonfinalizable() const override {}
    void                                gc_set_object(GCObject_B_*const&) override {}
    void                                gc_set_object(GCObject_B_*&&) override {}    
    void                                gc_mark() const override {}
    void                                gc_make_finalizable() const override {}
    void                                gc_deallocate() override {}
    void                                gc_force_deallocate() override {}

    
public:

    ~GCNullPointer() override {}
    GCNullPointer(::std::nullptr_t){}
    GCNullPointer(){}


    const GCObject_B_*                  gc_get_const_object() const override {return nullptr;}
    const GCContainer_B_*               gc_get_const_children() const override { return nullptr;}
    bool                                gc_is_empty() const override { return true;}
    bool                                gc_is_marked() const override {return true;}
    bool                                gc_is_finalizable() const override {return false;}
    const GCPointerType                 gc_get_pointer_type() const override {return GCPointerType::null_pointer;}
    bool                                gc_check_n_clear() const override {return true;}

};



}
#endif // _GC_POINTERBASE_H

