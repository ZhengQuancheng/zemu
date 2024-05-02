#include "device/CLINT.h"
#include "cstdlib"
#include "cstring"

#define     MTIMECMP_OFFSET   0x4000
#define     MTIME_OFFSET      0xBFF8

CLINT::CLINT() {
    this->mtime = 0;
    this->mtimecmp = 0;
    this->msip = 0;
}

CLINT::~CLINT() {
    // Destructor
}

bool CLINT::read(size_t addr, size_t size, uint8_t* buff) {
    size_t offset = addr - CLINT_BASE;
    // msip
    if (offset >= 0 && offset < 4) {
        memcpy(buff, (uint8_t*)&msip + offset, size);
        return true;
    }
    // mtimecmp
    if (offset >= MTIMECMP_OFFSET && offset < MTIMECMP_OFFSET + 8) {
        memcpy(buff, (uint8_t*)&mtimecmp + (offset - MTIMECMP_OFFSET), size);
        return true;
    }
    // mtime
    if (offset >= MTIME_OFFSET && offset < MTIME_OFFSET + 8) {
        memcpy(buff, (uint8_t*)&mtime + (offset - MTIME_OFFSET), size);
        return true;
    }
    return false;
}

bool CLINT::write(size_t addr, size_t size, uint8_t* buff) {
    size_t offset = addr - CLINT_BASE;
    // msip
    if (offset >= 0 && offset < 4) {
        memcpy((uint8_t*)&msip + offset, buff, size);
        return true;
    }
    // mtimecmp
    if (offset >= MTIMECMP_OFFSET && offset < MTIMECMP_OFFSET + 8) {
        memcpy((uint8_t*)&mtimecmp + (offset - MTIMECMP_OFFSET), buff, size);
        return true;
    }
    // mtime
    if (offset >= MTIME_OFFSET && offset < MTIME_OFFSET + 8) {
        memcpy((uint8_t*)&mtime + (offset - MTIME_OFFSET), buff, size);
        return true;
    }
    return false;
}

bool CLINT::irq_t() {
    return mtime >= mtimecmp;
}

bool CLINT::irq_s() {
    return msip & 1;
}
