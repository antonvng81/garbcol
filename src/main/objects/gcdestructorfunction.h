///////////////////////////////////////////////////////////////////////////////
// File: gcdestructorfunction.h
// Version: 0.2
// Description:
// GCObject's destructor connector to GC


#ifndef _GC_DESTRUCTORFUNCTION_H
#define _GC_DESTRUCTORFUNCTION_H

#include <functional>
#include "gcinheritance.h"

namespace GCNamespace{

class GCObject;

///////////////////////////////////////////////////////////////////////////////
// specialization for GCDestructorFunctionConnector class derived types
template<class _ObjectType>
class GCDestructorFunction{
    GCObject* object;

public:

    GCDestructorFunction(
        GCObject* obj, 
        ::std::function<void(void)> fnc =nullptr);

    ~GCDestructorFunction();
};

}

#ifndef _GC_HIDE_METHODS


namespace GCNamespace
{

// Called inside object's derived constructor 
template<class _ObjectType>
GCDestructorFunction<_ObjectType>::GCDestructorFunction(
    GCObject* obj,
    ::std::function<void(void)> fnc) {

    GCInheritance inh = GCInheritance::base;
    
    if(typeid(*obj).hash_code() == obj->gc_get_class_id()){
        inh = GCInheritance::derived;
    }

    object = obj;
    
    if(inh == GCInheritance::derived) {
        GCCollector::collector->get_scope_stack()->gc_object_on_delete();
    }

    GCCollector::collector->get_scope_stack()->gc_object_on_destructor();

    if (fnc != nullptr) {
        fnc();
    }
}

template<class _ObjectType>
GCDestructorFunction<_ObjectType>::~GCDestructorFunction() {
    GCCollector::collector->get_scope_stack()->gc_object_on_exit_destructor(object);
}

}
#endif

#endif //_GC_DESTRUCTORFUNCTION_H