///////////////////////////////////////////////////////////////////////////////
// File: gcsharedpointercore.h
// Versin 0.2
// Description:
// shared pointer class for GCPointer implementation

#ifndef _GC_SHAREDPOINTERCORE_H
#define _GC_SHAREDPOINTERCORE_H

#include "gcsharedpointermethods.h"
#include "gcpointertype.h"
#include "gcconstructormethods.h"

namespace GCNamespace {

template<GCPointerType _PointerTypeContainer=GCPointerType::not_from_container, 
GCPointerType _PointerTypeStatic=GCPointerType::is_non_static> 
class GCSharedPointerCore;

///////////////////////////////////////////////////////////////////////////////
// shared pointer core 

template<GCPointerType _PointerTypeContainer, GCPointerType _PointerTypeStatic>
class GCSharedPointerCore : public GCSharedPointerMethods, public GCContructorMethods{
    
    friend class GCCollector;

    virtual void constructor() override;
    virtual void destructor() override;
    
public:

    GCSharedPointerCore();
    ~GCSharedPointerCore() override;
};

}
#endif // _GC_SHAREDPOINTERCORE_H
