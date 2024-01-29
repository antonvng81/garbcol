#define _GC_HIDE_METHODS

#include "../collector/gccore.h"

namespace GCNamespace {

const GCPointerType GCUniquePointer_B_::gc_get_pointer_type() const{
    return GCPointerType::unique_pointer;
}

}
