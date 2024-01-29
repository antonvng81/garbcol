///////////////////////////////////////////////////////////////////////////////
// File: gcscopestack.cpp
// Version: 0.2
// Description:
// scope stack of current thread

#include <stdexcept>
#include "../collector/gccore.h"
#include "../pointers/gcpointer.h"

namespace GCNamespace {

GCScopeStack::GCScopeStack(){
    
    root_scope = new GCScope;

    current_scope = root_scope;
}

GCScopeStack::~GCScopeStack(){
    
    rvalue_stack.clear();
    delete root_scope;

    root_scope = nullptr;
}

void GCScopeStack::gc_object_on_new(GCObject* object) {

    rvalue_stack.push_front(object);

    current_scope_stack.push_front(current_scope);
    current_scope = object->children;
}

void GCScopeStack::gc_object_on_constructor() {  
    current_scope = root_scope;
}

void GCScopeStack::gc_object_on_exit_constructor(GCObject* object) {  
    current_scope = object->children;
}


void GCScopeStack::gc_object_on_exit_new() {
    current_scope = current_scope_stack.front();
    current_scope_stack.pop_front();
}


void GCScopeStack::gc_object_make_lvalue(GCObject* object){

    if(object == rvalue_stack.front()) {
        rvalue_stack.pop_front();
    } else {
        throw ::std::out_of_range("object does not correspond to rvalue_stack pointer" );        
    }
}


void GCScopeStack::gc_object_on_delete() {
    current_scope_stack.push_front(current_scope);
    current_scope = root_scope;
}


void GCScopeStack::gc_object_on_destructor() {
    current_scope = root_scope;
}

void GCScopeStack::gc_object_on_exit_destructor(GCObject* object) {
    current_scope = object->children;
}

void GCScopeStack::gc_object_on_exit_delete() {
    current_scope = current_scope_stack.front();
    current_scope_stack.pop_front();
}

}
