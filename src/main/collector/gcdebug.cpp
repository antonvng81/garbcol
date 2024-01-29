#include <iostream>
#include "gcdebug.h"

namespace GCNamespace{

GCDebug _GC_debug;


void GCDebug::set_mode(int debug_mode){
    _GC_debug.mode = debug_mode;
}

void GCDebug::out(::std::string str, int debug_mode) {
    if( _GC_debug.mode <= debug_mode ){
        ::std::cout   << "["<< _GC_debug.counter << "]" 
                    << _GC_debug.mode_str[debug_mode] <<": \t" << str <<"\n";   
        _GC_debug.counter += 1; 
    }
}

}