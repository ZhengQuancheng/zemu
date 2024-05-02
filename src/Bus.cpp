#include "Bus.h"
#include <cstdio>

bool Bus::read(size_t addr, size_t size, uint8_t* buff) {
    return false;
}

bool Bus::write(size_t addr, size_t size, uint8_t* buff) {
    return false;
}

bool Bus::add_device(size_t addr, size_t size, Device* device) {
    return false;
}
