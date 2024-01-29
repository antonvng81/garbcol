#define _GC_HIDE_METHODS

#include <stack>
#include "gccore.h"
#include "../containers/gccontainerbase.h"

namespace GCNamespace {

void GCMarkState::gc_set_scope(GCScope* scope) 
{
    // Initialize to root iteration
    parent = scope;
    position = parent->gc_begin();
    end_position = parent->gc_end();
}


void GCMarkState::gc_clear() 
{
    if (position != nullptr) {
        delete position;
        position = nullptr;
    }

    if (end_position != nullptr) {
        delete end_position;
        end_position = nullptr;
    }

    position_stack = ::std::stack<GCIterator_B_*>();
    parent_stack = ::std::stack<const GCContainer_B_*>();

    parent = nullptr;
}

void GCMarkState::gc_enter_children() {

    // Iterate over object's children
    auto pointer = position->gc_get_const_pointer();
    auto children = pointer->gc_get_const_children();

    if (children != nullptr)
    {
        // Save to stack the state of iteration. We save only
        // position and parent. We can get end iterator from parent            
        position_stack.push(position);
        parent_stack.push(parent);

        parent = children;

        // There are children pointers, iterate into it
        position = parent->gc_begin();
        
        if (end_position != nullptr) {
            delete end_position;
        }

        end_position = parent->gc_end();
        return;
    }        
    else{
        // move to shallow next
        position->gc_next();
        return;
    }
}

bool GCMarkState::gc_mark_next(){

    if (position->gc_is_equal(end_position)) {
        return false;
    }

    auto pointer = position->gc_get_const_pointer();

    if (pointer == nullptr)
    {
        // It cannot be marked
        position->gc_next();
        return true;
    }
    else if (pointer->gc_get_pointer_type() == GCPointerType::weak_pointer)
    {
        // This pointer is configured already to be not managed by
        // garbage collector
        
        position->gc_next();
        return true;
    }    
    else if (pointer->gc_check_n_clear())
    {
        // This pointer is configured already to be not managed by
        // garbage collector
        
        position->gc_next();
        return true;
    }
    else if (!pointer->gc_is_marked())
    {
        // Change pointer's object to marked
        pointer->gc_mark();
        gc_enter_children();
        return true;
    }
    else {                    
        // Object is already marked, change to next
        position->gc_next();
        return true;
    }

}


bool GCMarkState::gc_restore_parent() {

    if (position_stack.empty()) {
        return false;
    }

    if (position != nullptr) {
        delete position;
    }

    parent = parent_stack.top();
    position = position_stack.top();

    if (end_position != nullptr) {
        delete end_position;
    }

    end_position = parent->gc_end();

    position_stack.pop();
    parent_stack.pop();

    return true;
}

void GCMarkState::gc_mark_all() {

    // Recursive loop over each container
    while (true)
    {
        // Loop over each pointer of the container an mark it
        while (gc_mark_next()) {
            // go next   
        }

        // restore to shallow scope
        if(!gc_restore_parent()){
            break;
        }
    }
}

}
//end
