///////////////////////////////////////////////////////////////////////////////
// File: gcuniquepointercore.h
// Version: 0.2
// Description:
// unique pointer

#ifndef _GC_UNIQUEPOINTERCORE_H
#define _GC_UNIQUEPOINTERCORE_H

#include "gcuniquepointermethods.h"
#include "gcpointertype.h"

namespace GCNamespace {

class GCObject_B_;
class GCContainer_B_;

template<GCPointerType _PointerTypeContainer=GCPointerType::not_from_container, 
GCPointerType _PointerTypeStatic=GCPointerType::is_non_static> 
class GCUniquePointerCore;

///////////////////////////////////////////////////////////////////////////////
// unique pointer core

template<GCPointerType _PointerTypeContainer, GCPointerType _PointerTypeStatic>
class GCUniquePointerCore : public GCUniquePointerMethods, public GCContructorMethods{

    friend class GCCollector;

    virtual void constructor() override;
    virtual void destructor() override;

public:

    GCUniquePointerCore();
    ~GCUniquePointerCore() override;
};

}

#endif // _GC_UNIQUEPOINTERCORE_H

