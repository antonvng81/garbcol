///////////////////////////////////////////////////////////////////////////////
// File: gcweakpointer.h
// Version: 0.2
// Description:
// weak pointer base

#ifndef _GC_WEAKPOINTERBASE_H
#define _GC_WEAKPOINTERBASE_H

#include "gcpointertype.h"
#include "gcpointerbase.h"

namespace GCNamespace {

///////////////////////////////////////////////////////////////////////////////
// weak pointer base

class GCWeakPointer_B_ : public GCPointer_B_{
public:
    using GCPointer_B_::operator==;
    using GCPointer_B_::operator!=;
    using GCPointer_B_::operator<;
    using GCPointer_B_::operator>;
    using GCPointer_B_::operator<=;
    using GCPointer_B_::operator>=;

    virtual                             ~GCWeakPointer_B_() {}
    const GCPointerType                 gc_get_pointer_type() const override;
};

}

#endif // _GC_WEAKPOINTER_H

