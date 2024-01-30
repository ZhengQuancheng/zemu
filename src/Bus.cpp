#include "Bus.h"
#include <cstdio>

bool Bus::read(word_t addr, size_t size, uint8_t* buff) {
    return false;
}

bool Bus::write(word_t addr, size_t size, uint8_t* buff) {
    return false;
}

bool Bus::add_device(word_t addr, size_t size, Device* device) {
    return false;
}
