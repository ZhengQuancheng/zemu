#ifndef _TYPES_H_
#define _TYPES_H_

#include <cstdint>
#include <cstddef>

#ifdef CONFIG_RV32
    
#else
    typedef uint64_t word_t;
    #define XLEN 64
#endif

#endif // _TYPES_H_
