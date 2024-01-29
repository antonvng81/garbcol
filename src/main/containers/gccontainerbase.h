///////////////////////////////////////////////////////////////////////////////
// File: gccontainerbase.h
// Version: 0.2
// Description:
// container interfaces

#ifndef _GC_CONTAINERBASE_H
#define _GC_CONTAINERBASE_H

namespace GCNamespace{

class GCPointer_B_;

///////////////////////////////////////////////////////////////////////////////
// iterator interface class

class GCIterator_B_{
public:

    virtual                             ~GCIterator_B_() {}
    virtual const GCPointer_B_*         gc_get_const_pointer() const = 0;
    virtual GCIterator_B_*              gc_next() = 0;
    virtual bool		                gc_is_equal(const GCIterator_B_* other) const = 0;
};

///////////////////////////////////////////////////////////////////////////////
// container interface class

class GCContainer_B_{
public:

    virtual								~GCContainer_B_() {}

    virtual GCIterator_B_*              gc_begin() = 0;
    virtual GCIterator_B_*              gc_begin() const = 0;

    virtual GCIterator_B_*              gc_end() = 0;
    virtual GCIterator_B_*              gc_end() const = 0;

    virtual void                        gc_free()=0;

    virtual bool                        gc_is_empty() const=0;
};

}

#endif // _GC_CONTAINERBASE_H
