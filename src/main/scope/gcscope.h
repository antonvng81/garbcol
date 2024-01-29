///////////////////////////////////////////////////////////////////////////////
// File: gcscope.h
// Version: 0.2
// Description:
// scope container interfaces

#ifndef _GC_SCOPE_H
#define _GC_SCOPE_H

#include  <forward_list>
#include "../objects/gcchildnodebase.h"
#include "../pointers/gcpointerbase.h"
#include "../containers/gccontainerbase.h"

namespace GCNamespace{

///////////////////////////////////////////////////////////////////////////////
// scope iterator

template<class _Iterator>
class GCScopeIterator : public GCIterator_B_{

    _Iterator                           adaptee;

public:

    ~GCScopeIterator() override;
    GCScopeIterator(const _Iterator&);

    GCIterator_B_*                      gc_next() override;
    const GCPointer_B_*                 gc_get_const_pointer() const override;
    bool                                gc_is_equal(const GCIterator_B_* other) const override;
};

///////////////////////////////////////////////////////////////////////////////
// scope container

class GCScope : public GCContainer_B_ {

    ::std::forward_list<const GCPointer_B_*>      adaptee;

public:

    typedef typename ::std::forward_list<const GCPointer_B_*>::iterator iterator;
    typedef typename ::std::forward_list<const GCPointer_B_*>::const_iterator const_iterator;
    typedef typename ::std::forward_list<const GCPointer_B_*> container;

    GCScope();
    ~GCScope() override;

    GCIterator_B_*                      gc_begin() override;
    GCIterator_B_*                      gc_begin() const override;

    GCIterator_B_*                      gc_end() override;
    GCIterator_B_*                      gc_end() const override;

    void                                gc_free() override;
    bool                                gc_is_empty() const override;

    // Specific function members
    
    virtual void                        gc_push_front(const GCPointer_B_* val);
    virtual void                        gc_pop_front();
};

}

#endif // _GC_SCOPE_H
