#define _GC_HIDE_METHODS

#include "../collector/gccore.h"

namespace GCNamespace {

///////////////////////////////////////////////////////////////////////////////
// Shared pointer core not from container specialization non static

#define _GC_SELF                        GCSharedPointerCore<GCPointerType::not_from_container,GCPointerType::is_non_static>
#define _GC_TEMPLATE                    template<>

_GC_TEMPLATE
void _GC_SELF::constructor() {

    // Connect pointer to current scope
    // RAII method

    object = nullptr;

    GCScopeStack* scope_stack = GCCollector::collector->get_scope_stack();  
    GCScope* scope = scope_stack->current_scope;
    scope->gc_push_front(this);

}

_GC_TEMPLATE
void _GC_SELF::destructor() {    

    // Disconnect pointer from scope
    // RAII method

    GCScopeStack* scope_stack = GCCollector::collector->get_scope_stack();  
    static_cast<GCScope*>(scope_stack->current_scope)->gc_pop_front();
}

_GC_TEMPLATE
_GC_SELF::GCSharedPointerCore() {    
    constructor();
}

_GC_TEMPLATE
_GC_SELF::~GCSharedPointerCore() {    
    destructor();
}

#undef _GC_SELF
#undef _GC_TEMPLATE

///////////////////////////////////////////////////////////////////////////////
// Shared pointer core not from container specialization static

#define _GC_SELF                        GCSharedPointerCore<GCPointerType::not_from_container,GCPointerType::is_static>
#define _GC_TEMPLATE                    template<>

_GC_TEMPLATE
void _GC_SELF::constructor() {

    // Connect pointer to current scope
    // RAII method

    object = nullptr;
    GCThreadFunction* thread_function = GCCollector::collector->main_thread_function;
    GCScopeStack* scope_stack = thread_function->scope_stack;  
    GCScope* scope = scope_stack->root_scope;
    scope->gc_push_front(this);

}

_GC_TEMPLATE
void _GC_SELF::destructor() {    

    // root_scope no longer exists

}

_GC_TEMPLATE
_GC_SELF::GCSharedPointerCore(){
    GCCollector::static_pointer_heap.push_back(this);
}


_GC_TEMPLATE
_GC_SELF::~GCSharedPointerCore(){
    destructor();
}


#undef _GC_SELF
#undef _GC_TEMPLATE

///////////////////////////////////////////////////////////////////////////////
// Shared pointer core from container specialization non static

#define _GC_SELF                        GCSharedPointerCore<GCPointerType::from_container, GCPointerType::is_non_static>
#define _GC_TEMPLATE                    template<>

_GC_TEMPLATE
void _GC_SELF::constructor() {

    // Connect pointer to current scope
    // RAII method

    object = nullptr;
}

_GC_TEMPLATE
void _GC_SELF::destructor() {    
    // nothing
}

_GC_TEMPLATE
_GC_SELF::GCSharedPointerCore() {    
    constructor();
}
_GC_TEMPLATE
_GC_SELF::~GCSharedPointerCore() {    
    destructor();
}

#undef _GC_SELF
#undef _GC_TEMPLATE

}

//end
