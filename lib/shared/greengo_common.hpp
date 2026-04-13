#ifndef greengo_common_hpp
#define greengo_common_hpp

#ifdef ARDUINO
    #include "Arduino.h"
#else
    #include "arduino_emulator.hpp"
#endif /* ARDUINO */

typedef unsigned long   ulong;
typedef unsigned int    uint;

#endif /* greengo_common_hpp */
