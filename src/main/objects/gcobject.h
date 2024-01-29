///////////////////////////////////////////////////////////////////////////////
// File: gcobject.h
// Version: 0.2
// Description:
// pointer contents

#ifndef _GC_OBJECT_H
#define _GC_OBJECT_H

#include "gcobjectbase.h"

namespace GCNamespace {

class GCScope;

///////////////////////////////////////////////////////////////////////////////
// A class that have GCPointer type members must be derived from this class

class GCObject : public GCObject_B_{

    friend class                                    GCScopeStack;
    friend class                                    GCCollector;
    template<class> friend class                    GCConstructorFunction;
    template<class> friend class                    GCDestructorFunction;
    
    unsigned char                                   flags;
    GCScope*                                        children;
    ::std::size_t                                   class_id;

public:

    GCObject();
    virtual ~GCObject() override;

    ::std::size_t                       gc_get_class_id() const override;

    void                                gc_mark() override;
    bool                                gc_is_marked() const override;

    const GCContainer_B_*               gc_get_const_children() const override;

    void                                gc_make_nonfinalizable() override;
    void                                gc_make_finalizable() override;
    bool                                gc_is_finalizable() const override;

    void                                gc_make_rvalue() override;
    void                                gc_make_lvalue() override;
    bool                                gc_is_lvalue() const override;

    void                                gc_deallocate() override;
    bool                                gc_is_finalized() const override;

    void                                gc_force_deallocate() override;
    bool                                gc_is_force_finalized() const override;
 };
  
}

#endif // _GC_OBJECT_H
