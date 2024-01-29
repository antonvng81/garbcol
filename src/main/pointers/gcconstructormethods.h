///////////////////////////////////////////////////////////////////////////////
// File: gcpointerconstructormethods.h
// Version: 0.2
// Description:
// pointer functions

#ifndef _GC_CONSTRUCTORMETHODS_H_
#define _GC_CONSTRUCTORMETHODS_H_

namespace GCNamespace
{

class GCContructorMethods {
    public:
    virtual void constructor() = 0;
    virtual void destructor() = 0;
};

}
#endif