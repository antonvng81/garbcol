///////////////////////////////////////////////////////////////////////////////
// File: gcweakpointermethods.h
// Version: 0.2
// Description:
// weak pointer methods

#ifndef _GC_WEAKPOINTERMETHODS_H
#define _GC_WEAKPOINTERMETHODS_H

#include "gcweakpointerbase.h"

namespace GCNamespace {

class GCObject_B_;
class GCContainer_B_;

///////////////////////////////////////////////////////////////////////////////
// weak pointer base

class GCWeakPointerMethods : public GCWeakPointer_B_{
protected:
    mutable GCObject_B_*                    object;
public:

    virtual                                 ~GCWeakPointerMethods() {}

    bool                                    gc_is_empty() const override;

    void                                    gc_copy(const GCPointer_B_&) override;
    void                                    gc_copy(GCPointer_B_&&) override;

    void                                    gc_set_object(GCObject_B_*const&) override;
    void                                    gc_set_object(GCObject_B_*&&) override;

    GCObject_B_*                            gc_get_object() const override;
    const GCObject_B_*                      gc_get_const_object() const override;

    void                                    gc_deallocate() override;
    void                                    gc_force_deallocate() override;

    bool                                    gc_check_n_clear() const override;

    void                                    gc_mark() const override;
    bool                                    gc_is_marked() const override;

    const GCContainer_B_*                   gc_get_const_children() const override;

    void                                    gc_make_nonfinalizable() const override;
    void                                    gc_make_finalizable() const override;
    bool                                    gc_is_finalizable() const override;
};

}

#endif // _GC_WEAKPOINTERMETHODS_H

