///////////////////////////////////////////////////////////////////////////////
// File: gccore.h
// Version: 0.2
// Description:
// Core header

#ifndef _GC_CORE_H
#define _GC_CORE_H

#include "../collector/gcdebug.h"
#include "../collector/gcflags.h"
#include "../objects/gcinheritance.h"
#include "../pointers/gcpointertype.h"
#include "../pointers/gcpointerbase.h"
#include "../objects/gcobjectbase.h"
#include "../objects/gcchildnodebase.h"
#include "../containers/gccontainerbase.h"
#include "../pointers/gcsharedpointerbase.h"
#include "../pointers/gcweakpointerbase.h"
#include "../pointers/gcuniquepointerbase.h"

#include "../objects/gcobjectadapter.h"
#include "../scope/gcscopestack.h"
#include "../scope/gcscope.h"
#include "../objects/gcobject.h"
#include "../objects/gcconstructorfunction.h"
#include "../objects/gcdestructorfunction.h"
#include "../collector/gcmarkstate.h"
#include "../collector/gcsweepstate.h"
#include "../collector/gccollector.h"

#include "../pointers/gcsharedpointermethods.h"
#include "../pointers/gcsharedpointercore.h"
#include "../pointers/gcweakpointermethods.h"
#include "../pointers/gcweakpointercore.h"
#include "../pointers/gcuniquepointercore.h"
#include "../pointers/gcuniquepointermethods.h"

#include "../threads/gcthreadfunction.h"

#endif // _GC_CORE_H
