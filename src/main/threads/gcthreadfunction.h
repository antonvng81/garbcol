///////////////////////////////////////////////////////////////////////////////
// File: gcthreadfunction.h
// Version: 0.2
// Description:
// scope container interfaces

#ifndef _GC_THREADFUNCTION_H
#define _GC_THREADFUNCTION_H

#include <thread>
#include <mutex>
#include <functional>
#include <vector>

#include "../collector/gctypes.h"

namespace GCNamespace{

class GCScopeStack;
class GCConstructorStack;

///////////////////////////////////////////////////////////////////////////////
// configure a thread

class GCThreadFunction {
    
    friend class                                        GCCollector;
    template<GCPointerType,GCPointerType> friend class  GCSharedPointerCore;
    template<GCPointerType,GCPointerType> friend class  GCUniquePointerCore;

    GCScopeStack*                                       scope_stack;   
    gc_thread_heap_t::iterator                          position;
    
    static thread_local GCThreadFunction*               thread_function;
    
public:

    GCThreadFunction(std::function<void(void)> fnc=nullptr);
    ~GCThreadFunction();
};

}

#endif //_GC_THREADFUNCTION_H