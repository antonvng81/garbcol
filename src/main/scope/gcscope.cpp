#define _GC_HIDE_METHODS

#include "../collector/gccore.h"

namespace GCNamespace{

template<class _Iterator>
GCScopeIterator<_Iterator>::GCScopeIterator(const _Iterator& other){
    adaptee = other;
}

template<class _Iterator>
GCScopeIterator<_Iterator>::~GCScopeIterator(){
    //nothing
}
template<class _Iterator>
GCIterator_B_* GCScopeIterator<_Iterator>::gc_next(){
    ++adaptee;
    return this;
}

template<class _Iterator>
const GCPointer_B_* GCScopeIterator<_Iterator>::gc_get_const_pointer() const {
    return *adaptee;
}

template<class _Iterator>
bool GCScopeIterator<_Iterator>::gc_is_equal(const GCIterator_B_* other) const{
    return (static_cast<const GCScopeIterator<_Iterator>*>(other)->adaptee == adaptee);
}


GCScope::GCScope(){
    //nothing
}

GCScope::~GCScope(){
    //nothing
}

GCIterator_B_* GCScope::gc_begin() {
    return new GCScopeIterator<typename GCScope::iterator>(adaptee.begin());
}

GCIterator_B_* GCScope::gc_begin() const {
    return new GCScopeIterator<typename GCScope::const_iterator>(adaptee.begin());
}

GCIterator_B_* GCScope::gc_end() {
    return new GCScopeIterator<typename GCScope::iterator>(adaptee.end());
}

GCIterator_B_* GCScope::gc_end() const {
    return new GCScopeIterator<typename GCScope::const_iterator>(adaptee.end());
}

void GCScope::gc_push_front(const GCPointer_B_ *val) {
    adaptee.push_front(val);
}

void GCScope::gc_pop_front() {
    adaptee.pop_front();
}

void GCScope::gc_free() {
    adaptee.clear();
}

bool GCScope::gc_is_empty() const {
    return adaptee.empty();
}

}
