#ifndef __LOG_MACRO
#define __LOG_MACRO

#define DEBUG true

#ifdef DEBUG

#include <iostream>

#if DEBUG == true
#define LOG(x,y,z) std::cout << x << y << z
#elif
#define LOG(x,y,z)
#endif

#endif

#endif 