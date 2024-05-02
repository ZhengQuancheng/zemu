#include "Monitor.h"
#include "core/Core.h"
#include "core/Trap.h"
#include <cstdint>

Monitor::Monitor() {
    core.set_bus(&bus);
}

Monitor::~Monitor() {
    // Destructor
}

void Monitor::step(uint64_t n) {
    // Step
    InterruptPin pin;
    try {
        while (n--) {
            pin.msip = clint.irq_s();
            pin.mtip = clint.irq_t();
            /* PLIC */
            core.step(pin);
        }
    } catch (RISCVException& e) {
        // Exception
    }
}
