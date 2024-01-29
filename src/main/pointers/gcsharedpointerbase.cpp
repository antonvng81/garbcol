#define _GC_HIDE_METHODS

#include "../collector/gccore.h"

namespace GCNamespace {

const GCPointerType GCSharedPointer_B_::gc_get_pointer_type() const{
    return GCPointerType::shared_pointer;
}

}

//end
