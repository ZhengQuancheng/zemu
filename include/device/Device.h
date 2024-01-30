#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "types.h"

class Device {
    virtual bool read(word_t addr, size_t size, uint8_t* buff)  = 0;
    virtual bool write(word_t addr, size_t size, uint8_t* buff) = 0;
};

#endif // _DEVICE_H_
