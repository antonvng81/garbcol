///////////////////////////////////////////////////////////////////////////////
// File: gcvector.h
// Version: 0.2
// Description:
// stl vector wrapper

#ifndef _GC_VECTOR_H
#define _GC_VECTOR_H

#include "gcsequenceadapter.h"
#include "../pointers/gcpointertype.h"

namespace GCNamespace {

template<class _Type, class _ItemPointerBase = GCSharedPointerCore<GCPointerType::from_container>, class _Allocator=::std::allocator<GCPointer<_Type,_ItemPointerBase>> >
using GCVector = GCSequenceAdapter < ::std::vector, _Type ,_ItemPointerBase, _Allocator> ;

template<class _Type, class _PointerBase = GCSharedPointerCore<GCPointerType::not_from_container>, class _ItemPointerBase = GCSharedPointerCore<GCPointerType::from_container>, class _Allocator=::std::allocator<GCPointer<_Type,_ItemPointerBase>>>
using GCVectorPointer = GCPointer < GCVector< _Type, _ItemPointerBase, _Allocator>, _PointerBase, true > ;

template<class _Type, class _PointerBase = GCSharedPointerCore<GCPointerType::not_from_container,GCPointerType::is_static>, class _ItemPointerBase = GCSharedPointerCore<GCPointerType::from_container>, class _Allocator=::std::allocator<GCPointer<_Type,_ItemPointerBase>>>
using GCStaticVectorPointer = GCPointer < GCVector< _Type, _ItemPointerBase, _Allocator>, _PointerBase, true > ;

}
#endif // _GC_VECTOR_H

