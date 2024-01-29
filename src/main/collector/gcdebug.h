///////////////////////////////////////////////////////////////////////////////
// File: gcdebug.h
// Version: 0.2
// Description:
// debug function

#ifndef _GC_DEBUG_H_
#define _GC_DEBUG_H_

#include <string>

namespace GCNamespace {

    class GCDebug {
    
            ::std::string mode_str[4] = {"always","notify","warning","error"};
            int counter = 0;
            int mode = 0;

        public:

            constexpr static int always = 0;
            constexpr static int notify = 1;
            constexpr static int warning = 2;
            constexpr static int error = 3;
            constexpr static int never = 4;

            static void set_mode(int debug_mode);
            static void out(::std::string str, int debug_mode=0);
    };
 
}

#endif