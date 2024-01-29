///////////////////////////////////////////////////////////////////////////////
// File: gcpointer.h
// Version: 0.2
// Description:
// smart pointer

#ifndef _GC_POINTER_H
#define _GC_POINTER_H

#include <type_traits>
#include "gcsharedpointercore.h"
#include "gcweakpointercore.h"
#include "gcuniquepointercore.h"
#include "../objects/gcobjectadapter.h"


namespace GCNamespace {


// 'Generic template' pointer class
template<class _Type, class _PointerBase = GCSharedPointerCore<GCPointerType::not_from_container,GCPointerType::is_non_static>, bool _TypeIsObject = ::std::is_convertible<_Type*, GCObject_B_*>::value>
class GCPointer;

///////////////////////////////////////////////////////////////////////////////
// specialization for GCObject class derived types (true)

#define _GC_SELF GCPointer<_Type, _PointerBase, true>
#define _GC_TEMPLATE template<class _Type, class _PointerBase>

_GC_TEMPLATE class GCPointer<_Type, _PointerBase, true> : public _PointerBase{
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


    GCPointer();
    GCPointer(_Type*const& other);
    GCPointer(_Type*&& other);

    GCPointer(const _GC_SELF& other);
    GCPointer(_GC_SELF&& other);

    _GC_SELF&                           operator= (_Type*const& other);
    _GC_SELF&                           operator= (_Type*&& other);

    _GC_SELF&                           operator= (const _GC_SELF& other);
    _GC_SELF&                           operator= (_GC_SELF&& other);

    _Type&                              operator*();
    const _Type&                        operator*() const;

    _Type*                              operator->();
    const _Type*                        operator->() const;

    _Type&                              operator[](int);
    const _Type&                        operator[](int) const;


    template<class _OtherType, class _OtherPointerBase>
    operator GCPointer<_OtherType, _OtherPointerBase, true>()&;

    template<class _OtherType, class _OtherPointerBase>
    operator const GCPointer<_OtherType, _OtherPointerBase, true>() const &;

    template<class _OtherType, class _OtherPointerBase>
    operator GCPointer<_OtherType, _OtherPointerBase, true>() &&;

};

#ifndef _GC_HIDE_METHODS

_GC_TEMPLATE _GC_SELF::GCPointer() : _PointerBase() {}

_GC_TEMPLATE _GC_SELF::GCPointer(_Type*const& other) : _PointerBase() {

    static_assert(!::std::is_base_of<GCUniquePointer_B_,_PointerBase>::value,
                "unique pointer initialization from lvalue" );

    static_assert(!::std::is_base_of<GCWeakPointer_B_,_PointerBase>::value,
                "weak pointer from raw pointer not allowed");

    gc_set_object(other);
}

_GC_TEMPLATE _GC_SELF::GCPointer(_Type*&& other) : _PointerBase() {

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

_GC_TEMPLATE _GC_SELF& _GC_SELF::operator = (_Type*const& other) {
    
    static_assert(!::std::is_base_of<GCUniquePointer_B_,_PointerBase>::value,
                "unique pointer initialization from lvalue" );

    static_assert(!::std::is_base_of<GCWeakPointer_B_,_PointerBase>::value,
                "weak pointer from raw pointer not allowed");

    gc_set_object(other);
    return *this;
}


_GC_TEMPLATE _GC_SELF& _GC_SELF::operator = (_Type*&& other) {

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

_GC_TEMPLATE _Type& _GC_SELF::operator*() {
    return *static_cast<_Type*>(gc_get_object());
}

_GC_TEMPLATE const _Type& _GC_SELF::operator*() const {
    return *static_cast<_Type*>(gc_get_const_object());
}

_GC_TEMPLATE _Type* _GC_SELF::operator->() {
    return static_cast<_Type*>(gc_get_object());
}

_GC_TEMPLATE const _Type* _GC_SELF::operator->() const {
    return static_cast<_Type*>(gc_get_const_object());
}

_GC_TEMPLATE
_Type& _GC_SELF::operator[](int i) {    
    return static_cast<_Type*>(gc_get_object())[i];
}

_GC_TEMPLATE const _Type& _GC_SELF::operator[](int i) const {
    return static_cast<_Type*>(gc_get_const_object())[i];
}

_GC_TEMPLATE template<class _OtherType, class _OtherPointerBase>
        _GC_SELF::operator GCPointer<_OtherType, _OtherPointerBase, true>() &
{

    // (shared)shared ok
    // (shared)unique ok rvalue
    // (shared)weak ok
    // (weak)shared ok
    // (weak)unique ko
    // (weak)weak ok
    // (unique)unique ok rvalue
    // (unique)shared ko
    // (unique)weak ko
    
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

_GC_TEMPLATE template<class _OtherType, class _OtherPointerBase>
        _GC_SELF::operator const GCPointer<_OtherType, _OtherPointerBase, true>() const &
{
   
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

_GC_TEMPLATE template<class _OtherType, class _OtherPointerBase>
        _GC_SELF::operator GCPointer<_OtherType, _OtherPointerBase, true>() && 
{
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

#endif
#undef _GC_SELF
#undef _GC_TEMPLATE

#define _GC_SELF GCPointer<_Type, _PointerBase, false>
#define _GC_TEMPLATE template<class _Type, class _PointerBase>

///////////////////////////////////////////////////////////////////////////////
// specialization for non-GCObject derived types

_GC_TEMPLATE class GCPointer<_Type, _PointerBase, false> : public _PointerBase{
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

    GCPointer();
    GCPointer(_Type*const& other);
    GCPointer(_Type*&& other);

    GCPointer(const _GC_SELF& other);
    GCPointer(_GC_SELF&& other);

    _GC_SELF&                           operator= (_Type*const& other);
    _GC_SELF&                           operator= (_Type*&& other);
    _GC_SELF&                           operator= (const _GC_SELF& other);
    _GC_SELF&                           operator= (_GC_SELF&& other);

    _Type&                              operator*();
    _Type*                              operator->();
    _Type&                              operator[](int);

    const _Type&                        operator*() const;
    const _Type*                        operator->() const;
    const _Type&                        operator[](int) const;


    template<class _OtherType, class _OtherPointerBase>
    operator const GCPointer<_OtherType, _OtherPointerBase, false>() const &;

    template<class _OtherType, class _OtherPointerBase>
    operator GCPointer<_OtherType, _OtherPointerBase, false>()&;

    template<class _OtherType, class _OtherPointerBase>
    operator GCPointer<_OtherType, _OtherPointerBase, false>()&&;

    bool                                operator== (const _GC_SELF& other) const;
    bool                                operator!= (const _GC_SELF& other) const;
    bool                                operator< (const _GC_SELF& other) const;
    bool                                operator> (const _GC_SELF& other) const;
    bool                                operator<= (const _GC_SELF& other) const;
    bool                                operator>= (const _GC_SELF& other) const;
};

#ifndef _GC_HIDE_METHODS

_GC_TEMPLATE _GC_SELF::GCPointer() : _PointerBase() {}


_GC_TEMPLATE _GC_SELF::GCPointer(_Type*const& other) : _PointerBase(){

    static_assert(!::std::is_base_of<GCUniquePointer_B_,_PointerBase>::value,
                "unique pointer initialization from lvalue" );

    static_assert(!::std::is_base_of<GCWeakPointer_B_,_PointerBase>::value,
                "weak pointer from raw pointer not allowed");

    gc_set_object(new GCObjectAdapter<_Type>(other));
}

_GC_TEMPLATE _GC_SELF::GCPointer(_Type*&& other) : _PointerBase(){

    static_assert(!::std::is_base_of<GCWeakPointer_B_,_PointerBase>::value,
                "weak pointer from raw pointer not allowed");

    gc_set_object(new GCObjectAdapter<_Type>(::std::move(other)));
}

_GC_TEMPLATE _GC_SELF::GCPointer(const _GC_SELF& other) : _PointerBase() {

    static_assert(!::std::is_base_of<GCUniquePointer_B_,_PointerBase>::value,
                "unique pointer from lvalue not allowed");

    gc_copy(other);
}

_GC_TEMPLATE _GC_SELF::GCPointer(_GC_SELF&& other) : _PointerBase() {
    gc_copy(::std::move(other));
}

_GC_TEMPLATE _GC_SELF& _GC_SELF::operator = (_Type*const& other) {

    static_assert(!::std::is_base_of<GCUniquePointer_B_,_PointerBase>::value,
                "unique pointer initialization from lvalue" );

    static_assert(!::std::is_base_of<GCWeakPointer_B_,_PointerBase>::value,
                "weak pointer from raw pointer not allowed");

    gc_set_object(new GCObjectAdapter<_Type>(other));
    return *this;
}

_GC_TEMPLATE _GC_SELF& _GC_SELF::operator = (_Type*&& other) {

    static_assert(!::std::is_base_of<GCWeakPointer_B_,_PointerBase>::value,
                "weak pointer from raw pointer not allowed");

    gc_set_object(new GCObjectAdapter<_Type>(::std::move(other)));
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

_GC_TEMPLATE _Type& _GC_SELF::operator*() {
    return *(static_cast<GCObjectAdapter<_Type>*>(gc_get_object())->adaptee);
}

_GC_TEMPLATE _Type* _GC_SELF::operator->() {
    return static_cast<GCObjectAdapter<_Type>*>(gc_get_object())->adaptee;
}

_GC_TEMPLATE _Type& _GC_SELF::operator[](int i) {
    return (static_cast<GCObjectAdapter<_Type>*>(gc_get_object())->adaptee)[i];
}

_GC_TEMPLATE const _Type& _GC_SELF::operator*() const {
    return *(static_cast<const GCObjectAdapter<_Type>*>(gc_get_const_object())->adaptee);
}

_GC_TEMPLATE const _Type* _GC_SELF::operator->() const{
    return static_cast<const GCObjectAdapter<_Type>*>(gc_get_const_object())->adaptee;
}

_GC_TEMPLATE const _Type& _GC_SELF::operator[](int i) const {
    return (static_cast<const GCObjectAdapter<_Type>*>(gc_get_const_object())->adaptee)[i];
}


_GC_TEMPLATE template<class _OtherType, class _OtherPointerBase>
        _GC_SELF::operator GCPointer<_OtherType, _OtherPointerBase, false>()&
{

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

    GCPointer<_OtherType, _OtherPointerBase, false> tmp;
    tmp.gc_copy(*this);
    return tmp;
}

_GC_TEMPLATE template<class _OtherType, class _OtherPointerBase>
        _GC_SELF::operator const GCPointer<_OtherType, _OtherPointerBase, false>() const &
{
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

    GCPointer<_OtherType, _OtherPointerBase, false> tmp;
    tmp.gc_copy(*this);
    return tmp;

}

_GC_TEMPLATE template<class _OtherType, class _OtherPointerBase>
        _GC_SELF::operator GCPointer<_OtherType, _OtherPointerBase, false>() &&
{
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

    GCPointer<_OtherType, _OtherPointerBase, false> tmp;
    tmp.gc_copy(::std::move(*this));
    return tmp;

}

_GC_TEMPLATE
bool _GC_SELF::operator == (const _GC_SELF& other) const{
    return static_cast<const GCObjectAdapter<_Type>*>(gc_get_const_object())->adaptee ==
            static_cast<const GCObjectAdapter<_Type>*>(other.gc_get_const_object())->adaptee;
}

_GC_TEMPLATE
bool _GC_SELF::operator != (const _GC_SELF& other) const{
    return static_cast<const GCObjectAdapter<_Type>*>(gc_get_const_object())->adaptee !=
            static_cast<const GCObjectAdapter<_Type>*>(other.gc_get_const_object())->adaptee;
}

_GC_TEMPLATE
bool _GC_SELF::operator < (const _GC_SELF& other) const{
    return static_cast<const GCObjectAdapter<_Type>*>(gc_get_const_object())->adaptee <
            static_cast<const GCObjectAdapter<_Type>*>(other.gc_get_const_object())->adaptee;
}

_GC_TEMPLATE
bool _GC_SELF::operator > (const _GC_SELF& other) const{
    return static_cast<const GCObjectAdapter<_Type>*>(gc_get_const_object())->adaptee >
            static_cast<const GCObjectAdapter<_Type>*>(other.gc_get_const_object())->adaptee;
}

_GC_TEMPLATE
bool _GC_SELF::operator <= (const _GC_SELF& other) const{
    return static_cast<const GCObjectAdapter<_Type>*>(gc_get_const_object())->adaptee <=
            static_cast<const GCObjectAdapter<_Type>*>(other.gc_get_const_object())->adaptee;
}

_GC_TEMPLATE
bool _GC_SELF::operator >= (const _GC_SELF& other) const{
    return static_cast<const GCObjectAdapter<_Type>*>(gc_get_const_object())->adaptee >=
            static_cast<const GCObjectAdapter<_Type>*>(other.gc_get_const_object())->adaptee;
}

#endif
#undef _GC_SELF
#undef _GC_TEMPLATE

///////////////////////////////////////////////////////////////////////////////
// alias

template<class _Type> using GCSharedPointer = GCPointer <_Type, GCSharedPointerCore<>>;
template<class _Type> using GCWeakPointer = GCPointer <_Type, GCWeakPointerCore<>>;
template<class _Type> using GCUniquePointer = GCPointer <_Type, GCUniquePointerCore<>>;

template<class _Type>
using GCStaticSharedPointer = GCPointer <_Type, GCSharedPointerCore<GCPointerType::not_from_container,GCPointerType::is_static>>;

template<class _Type>
using GCStaticWeakPointer = GCPointer <_Type, GCWeakPointerCore<GCPointerType::not_from_container,GCPointerType::is_static>>;

template<class _Type>
using GCStaticUniquePointer = GCPointer <_Type, GCUniquePointerCore<GCPointerType::not_from_container,GCPointerType::is_static>>;

}

#endif // _GC_POINTER_H
