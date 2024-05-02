#ifndef _MONITOR_H_
#define _MONITOR_H_

#include "Bus.h"
#include "core/Core.h"
#include "device/CLINT.h"
#include "device/PLIC.h"

class Monitor {
private:
    Bus bus;
    Core core;
    CLINT clint;
    PLIC plic;
public:
    Monitor();
    ~Monitor();
    void step(uint64_t n);
};

#endif // _MONITOR_H_
