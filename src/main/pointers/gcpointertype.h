///////////////////////////////////////////////////////////////////////////////
// File: gcpointertype.h
// Version: 0.2
// Description:
// pointer type

#ifndef _GC_POINTERTYPE_H_
#define _GC_POINTERTYPE_H_

namespace GCNamespace{    
    // Argument to pass to constructor connector
    enum class GCPointerType {shared_pointer, unique_pointer, weak_pointer, null_pointer, 
    not_from_container, from_container, is_non_static, is_static};
}

#endif //_GC_POINTERTYPE_H_