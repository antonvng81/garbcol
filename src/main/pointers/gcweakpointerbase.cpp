#define _GC_HIDE_METHODS

#include "../collector/gccore.h"

namespace GCNamespace{

// Weak smart pointer
const GCPointerType GCWeakPointer_B_::gc_get_pointer_type() const{
    return GCPointerType::weak_pointer;
}

}

