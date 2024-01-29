///////////////////////////////////////////////////////////////////////////////
// File: gcuniquepointerbase.h
// Version: 0.2
// Description:
// unique pointer base

#ifndef _GC_UNIQUEPOINTERBASE_H
#define _GC_UNIQUEPOINTERBASE_H

#include "gcpointertype.h"
#include "gcpointerbase.h"

namespace GCNamespace {

///////////////////////////////////////////////////////////////////////////////
// unique pointer base

class GCUniquePointer_B_ : public GCPointer_B_ {
public:

    using GCPointer_B_::operator==;
    using GCPointer_B_::operator!=;
    using GCPointer_B_::operator<;
    using GCPointer_B_::operator>;
    using GCPointer_B_::operator<=;
    using GCPointer_B_::operator>=;

    virtual                             ~GCUniquePointer_B_() {}
    const GCPointerType                 gc_get_pointer_type() const override;
};

}

#endif // _GC_UNIQUEPOINTERBASE_H

