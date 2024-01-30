#ifndef _BUS_H_
#define _BUS_H_

#include "device/Device.h"
#include "types.h"
#include <cstddef>
#include <map>
#include <utility>

class Bus {
public:
    bool read(word_t addr, size_t size, uint8_t* buff);
    bool write(word_t addr, size_t size, uint8_t* buff);
    bool add_device(word_t addr, size_t size, Device* device);
private:
    std::map<std::pair<word_t, word_t>, Device*> devices;
};

#endif // _BUS_H_
