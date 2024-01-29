#define _GC_HIDE_METHODS

#include "../collector/gccore.h"

namespace GCNamespace {

///////////////////////////////////////////////////////////////////////////////
// Weak pointer methods not from container specialization non static

#define _GC_SELF                        GCWeakPointerCore<GCPointerType::not_from_container,GCPointerType::is_non_static>
#define _GC_TEMPLATE                    template<>


_GC_TEMPLATE
void _GC_SELF::constructor() {
    object = nullptr;
}

_GC_TEMPLATE
void _GC_SELF::destructor() {
    // nothing
}

_GC_TEMPLATE
_GC_SELF::GCWeakPointerCore() {
    constructor();
}

_GC_TEMPLATE
_GC_SELF::~GCWeakPointerCore() {
    destructor();
}
#undef _GC_SELF
#undef _GC_TEMPLATE

///////////////////////////////////////////////////////////////////////////////
// Weak pointer methods not from container specialization static

#define _GC_SELF                        GCWeakPointerCore<GCPointerType::not_from_container,GCPointerType::is_static>
#define _GC_TEMPLATE                    template<>


_GC_TEMPLATE
void _GC_SELF::constructor() {
    object = nullptr;
}

_GC_TEMPLATE
void _GC_SELF::destructor() {
    // nothing
}

_GC_TEMPLATE
_GC_SELF::GCWeakPointerCore() {
    GCCollector::static_pointer_heap.push_back(this);
}

_GC_TEMPLATE
_GC_SELF::~GCWeakPointerCore() {
    destructor();
}
#undef _GC_SELF
#undef _GC_TEMPLATE


///////////////////////////////////////////////////////////////////////////////
// Weak pointer methods  from container specialization

#define _GC_SELF                        GCWeakPointerCore<GCPointerType::from_container,GCPointerType::is_non_static>
#define _GC_TEMPLATE                    template<>


_GC_TEMPLATE
void _GC_SELF::constructor() {
    object = nullptr;
}

_GC_TEMPLATE
void _GC_SELF::destructor() {
    // nothing
}

_GC_TEMPLATE
_GC_SELF::GCWeakPointerCore() {
    constructor();
}

_GC_TEMPLATE
_GC_SELF::~GCWeakPointerCore() {
    destructor();
}

}