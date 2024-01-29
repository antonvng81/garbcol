///////////////////////////////////////////////////////////////////////////////
// File: gcmap.h
// Version: 0.2
// Description:
// stl map wrapper

#ifndef _GC_MAP_H
#define _GC_MAP_H

#include <map>

#include "gccontainerbase.h"
#include "../objects/gcobjectadapter.h"
#include "../pointers/gcpointer.h"
#include "../scope/gcscopestack.h"
#include "../objects/gcchildnodebase.h"
#include "../pointers/gcpointertype.h"

namespace GCNamespace
{

///////////////////////////////////////////////////////////////////////////////
// iterator wrapper

template<class _Iterator>
class GCMapIteratorAdapter : public GCIterator_B_ {

    _Iterator                           adaptee;

public:

    ~GCMapIteratorAdapter() override;
    GCMapIteratorAdapter(const _Iterator&);

    GCIterator_B_*                      gc_next() override;
    const GCPointer_B_*                 gc_get_const_pointer() const override;
    bool                                gc_is_equal(const GCIterator_B_* other) const override;
};

#ifndef _GC_HIDE_METHODS

template<class _Iterator>
GCMapIteratorAdapter<_Iterator>::GCMapIteratorAdapter(const _Iterator& other){
    adaptee = other;
}

template<class _Iterator>
GCMapIteratorAdapter<_Iterator>::~GCMapIteratorAdapter(){
    //nothing
}

template<class _Iterator>
GCIterator_B_* GCMapIteratorAdapter<_Iterator>::gc_next() {
    ++adaptee;
    return this;
}

template<class _Iterator>
const GCPointer_B_* GCMapIteratorAdapter<_Iterator>::gc_get_const_pointer() const {
    return &((*adaptee).second);
}

template<class _Iterator>
bool GCMapIteratorAdapter<_Iterator>::gc_is_equal(const GCIterator_B_* other) const {
    return ((static_cast<const GCMapIteratorAdapter<_Iterator>*>(other)->adaptee) == adaptee);
}

#endif

///////////////////////////////////////////////////////////////////////////////
// STL map wrapper

#define _GC_ALLOCATOR                   ::std::allocator<::std::pair<const _Key, GCPointer<_Type, _ItemPointerBase>>>
#define _GC_TEMPLATE                    template <class _Key, class _Type, class _Compare, class _ItemPointerBase, class _Allocator>
#define _GC_ADAPTEE                     ::std::map<_Key, GCPointer<_Type, _ItemPointerBase>, _Compare, _Allocator>
#define _GC_ITERATOR                    typename _GC_ADAPTEE::iterator
#define _GC_CONST_ITERATOR              typename _GC_ADAPTEE::const_iterator
#define _GC_SELF                        GCMap< _Key, _Type, _Compare, _ItemPointerBase, _Allocator>

template <class _Key, class _Type, class _Compare=::std::less<_Key>, class _ItemPointerBase = GCSharedPointerCore<GCPointerType::from_container>, class _Allocator=_GC_ALLOCATOR>
class GCMap : public GCObjectAdapter<_GC_ADAPTEE>, public GCContainer_B_, public GCChildNode_B_{

    using GCObjectAdapter<_GC_ADAPTEE>::adaptee;

    template<class _TypePP, class _PointerBasePP, bool _TypeIsObjectPP>
    friend class GCPointer;

    const GCObject_B_*                  parent;

public:

    typedef _GC_ADAPTEE container;
    typedef _GC_ITERATOR iterator;
    typedef _GC_CONST_ITERATOR const_iterator;

    template<class ..._Args>            GCMap(_Args...);
    ~GCMap() override;

    bool                                gc_is_empty() const override;
    void                                gc_free() override;

    GCIterator_B_*                      gc_begin() override;
    GCIterator_B_*                      gc_begin() const override;

    GCIterator_B_*                      gc_end() override;
    GCIterator_B_*                      gc_end() const override;

    const GCContainer_B_*               gc_get_const_children() const override;

    void                                gc_set_parent(GCObject_B_* obj) override;
    const GCObject_B_*                  gc_get_const_parent() const override;

    GCPointer<_Type,_ItemPointerBase>&
    operator[](const _Key &);

    const GCPointer<_Type,_ItemPointerBase>&
    operator[](const _Key &) const;

    bool                                operator== (const _GC_SELF& other) const;
    bool                            	operator!= (const _GC_SELF& other) const;
    bool                        		operator> (const _GC_SELF& other) const;
    bool                        		operator< (const _GC_SELF& other) const;
    bool                        		operator>= (const _GC_SELF& other) const;
    bool                        		operator<= (const _GC_SELF& other) const;

};

#ifndef _GC_HIDE_METHODS

_GC_TEMPLATE bool _GC_SELF::gc_is_empty() const{
    return adaptee->empty();
}

_GC_TEMPLATE void _GC_SELF::gc_free() {
    adaptee->clear();
}

_GC_TEMPLATE GCIterator_B_* _GC_SELF::gc_begin() {
    return new GCMapIteratorAdapter<_GC_ITERATOR>(adaptee->begin());
}

_GC_TEMPLATE GCIterator_B_* _GC_SELF::gc_begin() const {
    return new GCMapIteratorAdapter<_GC_CONST_ITERATOR>(adaptee->begin());
}

_GC_TEMPLATE GCIterator_B_* _GC_SELF::gc_end() {
    return new GCMapIteratorAdapter<_GC_ITERATOR>(adaptee->end());
}

_GC_TEMPLATE GCIterator_B_* _GC_SELF::gc_end() const {
    return new GCMapIteratorAdapter<_GC_CONST_ITERATOR>(adaptee->end());
}

_GC_TEMPLATE _GC_SELF::~GCMap() {
    delete adaptee;
    adaptee = nullptr;
}

_GC_TEMPLATE template<class ..._Args> _GC_SELF::GCMap(_Args... args) : GCObjectAdapter<_GC_ADAPTEE>() {
    adaptee = new _GC_ADAPTEE(args...);
}

_GC_TEMPLATE void _GC_SELF::gc_set_parent(GCObject_B_* obj) {
    parent = obj;
}

_GC_TEMPLATE const GCObject_B_* _GC_SELF::gc_get_const_parent() const {
    return parent;
}

_GC_TEMPLATE GCPointer<_Type,_ItemPointerBase>& _GC_SELF::operator[](const _Key& k) {
    return (*adaptee)[k];
}

_GC_TEMPLATE const GCPointer<_Type,_ItemPointerBase>& _GC_SELF::operator[](const _Key& k) const {
    return (*adaptee)[k];
}

_GC_TEMPLATE bool _GC_SELF::operator == (const _GC_SELF& other) const {
    return (*adaptee) == *(other.adaptee);
}

_GC_TEMPLATE bool _GC_SELF::operator != (const _GC_SELF& other) const {
    return (*adaptee) != *(other.adaptee);
}

_GC_TEMPLATE bool _GC_SELF::operator > (const _GC_SELF& other) const {
    return (*adaptee) > *(other.adaptee);
}

_GC_TEMPLATE bool _GC_SELF::operator < (const _GC_SELF& other) const {
    return (*adaptee) < *(other.adaptee);
}

_GC_TEMPLATE bool _GC_SELF::operator >= (const _GC_SELF& other) const {
    return (*adaptee) >= *(other.adaptee);
}

_GC_TEMPLATE bool _GC_SELF::operator <= (const _GC_SELF& other) const {
    return (*adaptee) <= *(other.adaptee);
}

_GC_TEMPLATE const GCContainer_B_* _GC_SELF::gc_get_const_children() const {
    return this;
}



#endif
#undef _GC_ALLOCATOR
#undef _GC_TEMPLATE
#undef _GC_SELF
#undef _GC_ADAPTEE
#undef _GC_ITERATOR
#undef _GC_CONST_ITERATOR

///////////////////////////////////////////////////////////////////////////////
// GCPointer specialization

#define _GC_ALLOCATOR                   ::std::allocator<::std::pair<const _Key, GCPointer<_Type, _ItemPointerBase>>>
#define _GC_TEMPLATE                    template< class _Key, class _Type, class _Compare, class _PointerBase, class _ItemPointerBase, class _Allocator>
#define _GC_ADAPTEE                     ::std::map<_Key, GCPointer<_Type, _ItemPointerBase>, _Compare, _Allocator>
#define	_GC_CONTAINER                   GCMap<_Key, _Type, _Compare, _ItemPointerBase, _Allocator>
#define _GC_SELF                        GCPointer<_GC_CONTAINER, _PointerBase, true>
#define _GC_CONTAINER_M_                static_cast<_GC_CONTAINER*>(gc_get_object())
#define _GC_CONST_CONTAINER_M_          static_cast<_GC_CONTAINER*>(gc_get_const_object())

_GC_TEMPLATE
class GCPointer< _GC_CONTAINER, _PointerBase, true>
        : public _PointerBase{
public:

    using _PointerBase::gc_is_empty;
    using _PointerBase::gc_copy;
    using _PointerBase::gc_set_object;
    using _PointerBase::gc_get_object;
    using _PointerBase::gc_get_const_object;
    using _PointerBase::gc_mark;
    using _PointerBase::gc_is_marked;
    using _PointerBase::gc_get_const_children;
    using _PointerBase::gc_make_nonfinalizable;
    using _PointerBase::gc_make_finalizable;
    using _PointerBase::gc_is_finalizable;
    using _PointerBase::gc_get_pointer_type;
    using _PointerBase::gc_deallocate;
    using _PointerBase::gc_check_n_clear;
    using _PointerBase::operator==;
    using _PointerBase::operator!=;
    using _PointerBase::operator<;
    using _PointerBase::operator>;
    using _PointerBase::operator<=;
    using _PointerBase::operator>=;

    typedef _GC_ADAPTEE container;
    typedef typename _GC_ADAPTEE::iterator iterator;
    typedef typename _GC_ADAPTEE::const_iterator const_iterator;

    GCPointer();
    GCPointer(_GC_CONTAINER*const& other);
    GCPointer(_GC_CONTAINER*&& other);
    GCPointer(const _GC_SELF& other);
    GCPointer(_GC_SELF&& other);

    _GC_SELF&                           operator= (_GC_CONTAINER*const& other);
    _GC_SELF&                           operator= (_GC_CONTAINER*&& other);

    _GC_SELF&                           operator= (const _GC_SELF& other);
    _GC_SELF&                           operator= (_GC_SELF&& other);

    _GC_ADAPTEE&                        operator*();
    const _GC_ADAPTEE&                  operator*() const;

    _GC_ADAPTEE*                        operator->();
    const _GC_ADAPTEE*                  operator->() const;

    template<class _Other, class _OtherPointerBase>
    operator GCPointer<_Other,_OtherPointerBase>()&;

    template<class _Other, class _OtherPointerBase>
    operator const GCPointer<_Other,_OtherPointerBase>() const&;

    template<class _Other, class _OtherPointerBase>
    operator GCPointer<_Other,_OtherPointerBase>()&&;

    GCPointer<_Type, _ItemPointerBase>&
    operator[] (const _Key&);

    const GCPointer<_Type, _ItemPointerBase>&
    operator[] (const _Key&) const;
};

#ifndef _GC_HIDE_METHODS

_GC_TEMPLATE _GC_SELF::GCPointer() : _PointerBase() {}

_GC_TEMPLATE _GC_SELF::GCPointer(_GC_CONTAINER*const& other) : _PointerBase() {

    static_assert(!::std::is_base_of<GCUniquePointer_B_,_PointerBase>::value,
                "unique pointer initialization from lvalue" );

    static_assert(!::std::is_base_of<GCWeakPointer_B_,_PointerBase>::value,
                "weak pointer from raw pointer not allowed");

    gc_set_object(other);
}

_GC_TEMPLATE _GC_SELF::GCPointer(_GC_CONTAINER*&& other) : _PointerBase() {

    static_assert(!::std::is_base_of<GCWeakPointer_B_,_PointerBase>::value,
                "weak pointer from raw pointer not allowed");

    gc_set_object(::std::move(other));
}

_GC_TEMPLATE _GC_SELF::GCPointer(const _GC_SELF& other) : _PointerBase() {

    static_assert(!::std::is_base_of<GCUniquePointer_B_,_PointerBase>::value,
                "unique pointer from lvalue not allowed");

    gc_copy(other);
}

_GC_TEMPLATE _GC_SELF::GCPointer(_GC_SELF&& other) : _PointerBase() {
    gc_copy(::std::move(other));
}

_GC_TEMPLATE _GC_SELF& _GC_SELF::operator = (_GC_CONTAINER*const& other) {

    static_assert(!::std::is_base_of<GCUniquePointer_B_,_PointerBase>::value,
                "unique pointer initialization from lvalue" );

    static_assert(!::std::is_base_of<GCWeakPointer_B_,_PointerBase>::value,
                "weak pointer from raw pointer not allowed");

    gc_set_object(other);
    return *this;
}

_GC_TEMPLATE _GC_SELF& _GC_SELF::operator = (_GC_CONTAINER*&& other) {

    static_assert(!::std::is_base_of<GCWeakPointer_B_,_PointerBase>::value,
                "weak pointer from raw pointer not allowed");

    gc_set_object(::std::move(other));
    return *this;
}

_GC_TEMPLATE _GC_SELF& _GC_SELF::operator = (const _GC_SELF& other) {

    static_assert(!::std::is_base_of<GCUniquePointer_B_,_PointerBase>::value,
                "unique pointer from lvalue not allowed");

    gc_copy(other);
    return *this;
}

_GC_TEMPLATE _GC_SELF& _GC_SELF::operator = (_GC_SELF&& other) {
    gc_copy(::std::move(other));
    return *this;
}

_GC_TEMPLATE _GC_ADAPTEE& _GC_SELF::operator*() {
    return *(_GC_CONTAINER_M_->adaptee);
}

_GC_TEMPLATE const _GC_ADAPTEE& _GC_SELF::operator*() const{   
    return *(_GC_CONST_CONTAINER_M_->adaptee);
}

_GC_TEMPLATE _GC_ADAPTEE* _GC_SELF::operator->() {
    return _GC_CONTAINER_M_->adaptee;
}

_GC_TEMPLATE const _GC_ADAPTEE* _GC_SELF::operator->() const{
    return _GC_CONST_CONTAINER_M_->adaptee;
}

_GC_TEMPLATE
template<class _OtherType, class _OtherPointerBase> _GC_SELF::operator GCPointer<_OtherType,_OtherPointerBase>()&{

    static_assert(::std::is_convertible<_Type*,_OtherType*>::value,
                    "object type is not convertible to other object type");

    static_assert(!(::std::is_base_of<GCSharedPointer_B_,_OtherPointerBase>::value&&
                    ::std::is_base_of<GCUniquePointer_B_,_PointerBase>::value),
                  "lvalue unique pointer casting to shared pointer not allowed");

    static_assert(!(::std::is_base_of<GCWeakPointer_B_,_OtherPointerBase>::value&&
                    ::std::is_base_of<GCUniquePointer_B_,_PointerBase>::value),
                  "unique pointer casting to weak pointer not allowed");

    static_assert(!(::std::is_base_of<GCUniquePointer_B_,_OtherPointerBase>::value&&
                    ::std::is_base_of<GCUniquePointer_B_,_PointerBase>::value),
                  "lvalue unique pointer casting to unique pointer not allowed");

    static_assert(!(::std::is_base_of<GCUniquePointer_B_,_OtherPointerBase>::value&&
                    ::std::is_base_of<GCSharedPointer_B_,_PointerBase>::value),
                  "shared pointer casting to unique pointer not allowed");


    static_assert(!(::std::is_base_of<GCUniquePointer_B_,_OtherPointerBase>::value&&
                    ::std::is_base_of<GCWeakPointer_B_,_PointerBase>::value),
                  "weak pointer casting to unique pointer not allowed");

    GCPointer<_OtherType, _OtherPointerBase, true> tmp;
    tmp.gc_copy(*this);
    return tmp;
}

_GC_TEMPLATE
template<class _OtherType, class _OtherPointerBase> _GC_SELF::operator const GCPointer<_OtherType,_OtherPointerBase>() const &{
   
    static_assert(::std::is_convertible<_Type*,_OtherType*>::value,
                    "object type is not convertible to other object type");

    static_assert(!(::std::is_base_of<GCSharedPointer_B_,_OtherPointerBase>::value&&
                    ::std::is_base_of<GCUniquePointer_B_,_PointerBase>::value),
                  "lvalue unique pointer casting to shared pointer not allowed");

    static_assert(!(::std::is_base_of<GCWeakPointer_B_,_OtherPointerBase>::value&&
                    ::std::is_base_of<GCUniquePointer_B_,_PointerBase>::value),
                  "unique pointer casting to weak pointer not allowed");

    static_assert(!(::std::is_base_of<GCUniquePointer_B_,_OtherPointerBase>::value&&
                    ::std::is_base_of<GCUniquePointer_B_,_PointerBase>::value),
                  "lvalue unique pointer casting to unique pointer not allowed");

    static_assert(!(::std::is_base_of<GCUniquePointer_B_,_OtherPointerBase>::value&&
                    ::std::is_base_of<GCSharedPointer_B_,_PointerBase>::value),
                  "shared pointer casting to unique pointer not allowed");


    static_assert(!(::std::is_base_of<GCUniquePointer_B_,_OtherPointerBase>::value&&
                    ::std::is_base_of<GCWeakPointer_B_,_PointerBase>::value),
                  "weak pointer casting to unique pointer not allowed");

    GCPointer<_OtherType, _OtherPointerBase, true> tmp;
    tmp.gc_copy(*this);
    return tmp;
}

_GC_TEMPLATE
template<class _OtherType, class _OtherPointerBase> _GC_SELF::operator GCPointer<_OtherType,_OtherPointerBase>()&&{

   static_assert(::std::is_convertible<_Type*,_OtherType*>::value,
                    "object type is not convertible to other object type");

    static_assert(!(::std::is_base_of<GCWeakPointer_B_,_OtherPointerBase>::value&&
                    ::std::is_base_of<GCUniquePointer_B_,_PointerBase>::value),
                  "unique pointer casting to weak pointer not allowed");

    static_assert(!(::std::is_base_of<GCUniquePointer_B_,_OtherPointerBase>::value&&
                    ::std::is_base_of<GCSharedPointer_B_,_PointerBase>::value),
                  "shared pointer casting to unique pointer not allowed");


    static_assert(!(::std::is_base_of<GCUniquePointer_B_,_OtherPointerBase>::value&&
                    ::std::is_base_of<GCWeakPointer_B_,_PointerBase>::value),
                  "weak pointer casting to unique pointer not allowed");

    GCPointer<_OtherType, _OtherPointerBase, true> tmp;
    tmp.gc_copy(::std::move(*this));
    return tmp;
}


_GC_TEMPLATE GCPointer<_Type, _ItemPointerBase>& _GC_SELF::operator[](const _Key& k) {
    return (*(_GC_CONTAINER_M_->adaptee))[k];
}

_GC_TEMPLATE const GCPointer<_Type, _ItemPointerBase>& _GC_SELF::operator[](const _Key& k) const {
    return (*(_GC_CONST_CONTAINER_M_->adaptee))[k];
}

#endif

#undef _GC_TEMPLATE
#undef _GC_CONTAINER
#undef _GC_SELF
#undef _GC_ADAPTEE
#undef _GC_CONTAINER_M_
#undef _GC_CONST_CONTAINER_M_

///////////////////////////////////////////////////////////////////////////////
// alias

template<class _Key, class _Type, class _Compare=::std::less<_Key> ,
         class _PointerBase = GCSharedPointerCore<GCPointerType::not_from_container>, class _ItemPointerBase = GCSharedPointerCore<GCPointerType::from_container>, class _Allocator=_GC_ALLOCATOR >
using GCMapPointer = GCPointer< GCMap<_Key,_Type,_Compare,_ItemPointerBase, _Allocator>, _PointerBase, true >;


template<class _Key, class _Type, class _Compare=::std::less<_Key> ,
         class _PointerBase = GCSharedPointerCore<GCPointerType::not_from_container,GCPointerType::is_static>, class _ItemPointerBase = GCSharedPointerCore<GCPointerType::from_container>, class _Allocator=_GC_ALLOCATOR >
using GCStaticMapPointer = GCPointer< GCMap<_Key,_Type,_Compare,_ItemPointerBase, _Allocator>, _PointerBase, true >;

}

#endif
