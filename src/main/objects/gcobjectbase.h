///////////////////////////////////////////////////////////////////////////////
// File: gcobjectbase.h
// Version: 0.2
// Description:
// object base

#ifndef _GC_OBJECTBASE_H
#define _GC_OBJECTBASE_H

namespace GCNamespace{

class GCContainer_B_;

///////////////////////////////////////////////////////////////////////////////
// most object top base class

class GCObject_B_ {
public:

    virtual void                        gc_mark() = 0;
    virtual bool                        gc_is_marked() const = 0;

    virtual const GCContainer_B_*       gc_get_const_children() const = 0;

    virtual void                        gc_make_nonfinalizable() = 0;
    virtual void                        gc_make_finalizable() = 0;
    virtual bool                        gc_is_finalizable() const = 0;

    virtual void                        gc_make_rvalue() = 0;
    virtual void                        gc_make_lvalue() = 0;
    virtual bool                        gc_is_lvalue() const = 0;

    virtual void                        gc_deallocate() = 0;
    virtual bool                        gc_is_finalized() const = 0;

    virtual void                        gc_force_deallocate() = 0;
    virtual bool                        gc_is_force_finalized() const = 0;
    virtual ::std::size_t               gc_get_class_id() const= 0;

    virtual                             ~GCObject_B_() {}
};

}

#endif // _GC_OBJECTBASE_H

