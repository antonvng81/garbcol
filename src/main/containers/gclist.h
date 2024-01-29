///////////////////////////////////////////////////////////////////////////////
// File: gclist.h
// Version: 0.2
// Description:
// STL list wrapper

#ifndef _GC_LIST_H
#define _GC_LIST_H

#include <list>
#include "gcsequenceadapter.h"
#include "../pointers/gcpointertype.h"

namespace GCNamespace {

template<class _Type, class _ItemPointerBase = GCSharedPointerCore<GCPointerType::from_container>, class _Allocator=::std::allocator<GCPointer<_Type,_ItemPointerBase>> >
using GCList = GCSequenceAdapter < ::std::list, _Type ,_ItemPointerBase, _Allocator> ;

template<class _Type, class _PointerBase = GCSharedPointerCore<GCPointerType::not_from_container>, class _ItemPointerBase = GCSharedPointerCore<GCPointerType::from_container>, class _Allocator=::std::allocator<GCPointer<_Type,_ItemPointerBase>> >
using GCListPointer = GCPointer < GCList< _Type, _ItemPointerBase, _Allocator>, _PointerBase, true > ;

template<class _Type, class _PointerBase = GCSharedPointerCore<GCPointerType::not_from_container,GCPointerType::is_static>, class _ItemPointerBase = GCSharedPointerCore<GCPointerType::from_container>, class _Allocator=::std::allocator<GCPointer<_Type,_ItemPointerBase>> >
using GCStaticListPointer = GCPointer < GCList< _Type, _ItemPointerBase, _Allocator>, _PointerBase, true > ;

}

#endif // _GC_LIST_H

