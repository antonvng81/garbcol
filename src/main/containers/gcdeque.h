///////////////////////////////////////////////////////////////////////////////
// File: gcdeque.h
// Description:
// STL deque wrapper

#ifndef _GC_DEQUE_H
#define _GC_DEQUE_H

#include <deque>
#include "gcsequenceadapter.h"
#include "../pointers/gcpointertype.h"

namespace GCNamespace {

template<class _Type, class _ItemPointerBase = GCSharedPointerCore<GCPointerType::from_container>, class _Allocator=::std::allocator<GCPointer<_Type,_ItemPointerBase>>>
using GCDeque = GCSequenceAdapter < ::std::deque, _Type ,_ItemPointerBase, _Allocator> ;

template<class _Type, class _PointerBase = GCSharedPointerCore<GCPointerType::not_from_container>, class _ItemPointerBase = GCSharedPointerCore<GCPointerType::from_container>, class _Allocator=::std::allocator<GCPointer<_Type,_ItemPointerBase>> >
using GCDequePointer = GCPointer < GCDeque< _Type, _ItemPointerBase, _Allocator>, _PointerBase, true > ;

template<class _Type, class _PointerBase = GCSharedPointerCore<GCPointerType::not_from_container,GCPointerType::is_static>, class _ItemPointerBase = GCSharedPointerCore<GCPointerType::from_container>, class _Allocator=::std::allocator<GCPointer<_Type,_ItemPointerBase>> >
using GCStaticDequePointer = GCPointer < GCDeque< _Type, _ItemPointerBase, _Allocator>, _PointerBase, true > ;

}

#endif // _GC_DEQUE_H

