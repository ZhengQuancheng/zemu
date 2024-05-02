#ifndef _BUS_H_
#define _BUS_H_

#include "device/Device.h"
#include "types.h"
#include <cstddef>
#include <map>
#include <utility>

class Bus {
public:
    bool read(size_t addr, size_t size, uint8_t* buff);
    bool write(size_t addr, size_t size, uint8_t* buff);
    bool add_device(size_t addr, size_t size, Device* device);
private:
    std::map<std::pair<word_t, word_t>, Device*> devices;
};

#endif // _BUS_H_
