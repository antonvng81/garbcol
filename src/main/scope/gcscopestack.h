///////////////////////////////////////////////////////////////////////////////
// File: gcscopestack.h
// Version: 0.2
// Description:
// scope state information of current thread

#ifndef _GC_SCOPESTACK_H
#define _GC_SCOPESTACK_H

#include <forward_list>
#include <list>
#include "../objects/gcinheritance.h"

namespace GCNamespace {

class GCObject;
class GCScope;


///////////////////////////////////////////////////////////////////////////////
// scope state information

class GCScopeStack{
    
    ::std::forward_list<GCScope*>       current_scope_stack;
    GCScope*                            current_scope;
    GCScope*                            root_scope;
    
    ::std::forward_list<GCObject*>      rvalue_stack;

    template<GCPointerType,GCPointerType> friend class GCUniquePointerCore; 
    template<GCPointerType,GCPointerType> friend class GCSharedPointerCore; 
    template<GCPointerType,GCPointerType> friend class GCWeakPointerCore; 

    friend class                        GCMarkState; 
    friend class                        GCCollector;
    
public:

    // Events
    void                                gc_object_on_new(GCObject*);
    void                                gc_object_on_constructor();
    void                                gc_object_on_exit_constructor(GCObject*);
    void                                gc_object_on_exit_new();

    void                                gc_object_on_exit_delete();
    void                                gc_object_on_delete();
    void                                gc_object_on_destructor();
    void                                gc_object_on_exit_destructor(GCObject*);

    
    void                                gc_object_make_lvalue(GCObject* object);


    GCScopeStack();
    ~GCScopeStack();
};
}
#endif // _GC_SCOPESTACK_H