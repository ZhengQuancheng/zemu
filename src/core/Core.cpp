#include "core/Core.h"
#include "core/Trap.h"
#include "types.h"

#include <cstdint>
#include <cstdio>

Core::Core() {
    // Constructor
}

Core::~Core() {
    // Destructor
}

void Core::set_bus(Bus* bus) {
    // Set bus
    this->bus = bus;
}

void Core::fetch(Package& pkg) {
    // Fetch
}

void Core::decode(Package& ip) {
    // Decode
}

void Core::execute(Package& ip) {
    // Execute
}

void Core::reset() {
    // Reset
}

void Core::step(InterruptPin& pin) {
    this->check_interrupt(pin);
}

void Core::check_interrupt(InterruptPin& pin) {
    // Check interrupt
}

void Core::take_trap(Trap trap, word_t tval) {
    // Take trap
}
