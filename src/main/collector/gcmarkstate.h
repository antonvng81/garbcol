///////////////////////////////////////////////////////////////////////////////
// File: gcmarkstate.h
// Version: 0.2
// Description:
// mark manager

#ifndef _GC_MARKSTATE_H
#define _GC_MARKSTATE_H

#include <stack>

namespace GCNamespace {

// Forward declaration
class GCScope;
class GCContainer_B_;
class GCIterator_B_;

///////////////////////////////////////////////////////////////////////////////
// GCMarkState
class GCMarkState {

    ::std::stack<const GCContainer_B_*>       parent_stack;
    const GCContainer_B_*                     parent;

    ::std::stack<GCIterator_B_*>        position_stack;    
    GCIterator_B_*                      position;

    GCIterator_B_*                      end_position;    

public:

    void                                gc_set_scope(GCScope* scope);
    void                                gc_clear();

    bool                                gc_restore_parent();
    void                                gc_enter_children();
    bool                                gc_mark_next();
    void                                gc_mark_all();
};

}

#endif // _GC_MARKSTATE_H