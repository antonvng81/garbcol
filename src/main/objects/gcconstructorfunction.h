///////////////////////////////////////////////////////////////////////////////
// File: gcconstructorfunction.h
// Version: 0.2
// Description:
// GCObject's constructor function


#ifndef _GC_CONSTRUCTORFUNCTION_H
#define _GC_CONSTRUCTORFUNCTION_H

#include <functional>
#include "gcinheritance.h"
#include "../collector/gccollector.h"
#include "../scope/gcscopestack.h"

namespace GCNamespace{

class GCObject;

template<class _ObjectType>
class GCConstructorFunction 
{
    GCInheritance           inh; 
    GCObject*               object;
    static GCCollector*     collector;

public:
    GCConstructorFunction(
        GCInheritance _inh, 
        GCObject* obj, 
        ::std::function<void(void)> fnc=nullptr);    
        
    ~GCConstructorFunction();
};

}

#ifndef _GC_HIDE_METHODS

namespace GCNamespace
{

template<class _ObjectType>
GCConstructorFunction<_ObjectType>::GCConstructorFunction(
    GCInheritance _inh,
    GCObject* obj,
     ::std::function<void(void)> fnc) 
{
    //Setting this to derived type
    if(_inh == GCInheritance::derived){
        obj->class_id = typeid(*obj).hash_code();
    }

    //setting
    inh = _inh;

    // Setting object
    object = obj;

    // Continue at function scope at time of object construction
    GCCollector::collector->get_scope_stack()->gc_object_on_constructor();
    
    if (fnc != nullptr) {
        fnc();
    }
}

template<class _ObjectType>
GCConstructorFunction<_ObjectType>::~GCConstructorFunction() {
    
    if(GCInheritance::derived == inh) {
        GCCollector::collector->get_scope_stack()->gc_object_on_exit_new();
    }
    else{
        GCCollector::collector->get_scope_stack()->gc_object_on_exit_constructor(object);
    }
}

}

#endif

#endif //_GC_CONSTRUCTORFUNCTION_H