///////////////////////////////////////////////////////////////////////////////
// File: childnodebase.h
// Version: 0.2
// Description:
// child interfaces

#ifndef _GC_CHILDNODEBASE_H
#define _GC_CHILDNODEBASE_H

namespace GCNamespace{

class GCObject_B_;


///////////////////////////////////////////////////////////////////////////////
// child interface class

class GCChildNode_B_{
public:

    virtual void                        gc_set_parent(GCObject_B_* obj)=0;
    virtual const GCObject_B_*          gc_get_const_parent() const = 0;

};

}

#endif // _GC_CHILDNODEBASE_H
