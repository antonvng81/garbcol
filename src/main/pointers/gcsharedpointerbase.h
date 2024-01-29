///////////////////////////////////////////////////////////////////////////////
// File: gcsharedpointerbase.h
// Versin 0.2
// Description:
// shared pointer

#ifndef _GC_SHAREDPOINTERBASE_H
#define _GC_SHAREDPOINTERBASE_H

#include "gcpointertype.h"
#include "gcpointerbase.h"

namespace GCNamespace {

///////////////////////////////////////////////////////////////////////////////
// shared pointer base

class GCSharedPointer_B_ : public GCPointer_B_{
public:

    virtual                             ~GCSharedPointer_B_() {}
    const GCPointerType                 gc_get_pointer_type() const override;
};

}

#endif // _GC_SHAREDPOINTERBASE_H
