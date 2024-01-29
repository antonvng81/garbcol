///////////////////////////////////////////////////////////////////////////////
// File: gcweakpointercore.h
// Version: 0.2
// Description:
// weak pointer methods

#ifndef _GC_WEAKPOINTERCORE_H
#define _GC_WEAKPOINTERCORE_H

#include "gcweakpointermethods.h"
#include "gcpointertype.h"

namespace GCNamespace {

class GCObject_B_;
class GCContainer_B_;


template<GCPointerType _FromContainer=GCPointerType::not_from_container,GCPointerType _IsStatic=GCPointerType::is_non_static> 
class GCWeakPointerCore;

///////////////////////////////////////////////////////////////////////////////
// weak pointer core

template<GCPointerType _FromContainer, GCPointerType _IsStatic>
class GCWeakPointerCore : public GCWeakPointerMethods, public GCContructorMethods{
public:

    friend class GCCollector;

    virtual void constructor() override;
    virtual void destructor() override;
    
public:
    GCWeakPointerCore();
    ~GCWeakPointerCore() override;
};

}

#endif // _GC_WEAKPOINTERCORE_H