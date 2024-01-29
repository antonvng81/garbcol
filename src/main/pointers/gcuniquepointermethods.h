///////////////////////////////////////////////////////////////////////////////
// File: gcuniquepointermethods.h
// Version: 0.2
// Description:
// unique pointer

#ifndef _GC_UNIQUEPOINTERMETHODS_H
#define _GC_UNIQUEPOINTERMETHODS_H

#include "gcuniquepointerbase.h"

namespace GCNamespace {

class GCObject_B_;
class GCContainer_B_;


///////////////////////////////////////////////////////////////////////////////
// unique pointer methods

class GCUniquePointerMethods : public GCUniquePointer_B_{
protected:
    mutable GCObject_B_*                    object;
public:

    virtual                                 ~GCUniquePointerMethods() {}

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

#endif // _GC_UNIQUEPOINTERMETHODS_H

