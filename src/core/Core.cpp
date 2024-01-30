#include "core/Core.h"
#include "core/Trap.h"
#include "types.h"

#include <cstdint>
#include <cstdio>

Core::Core(Bus& bus, uint8_t hart_id) : bus(bus), hart_id(hart_id) {
    // Constructor
    printf("Core %d created\n", hart_id);
}

Core::~Core() {
    // Destructor
}

void Core::fetch(InstPack& ip) {
    ip.pc = pc;
    if (pc & 0x1) { take_trap(Trap::InstructionAddressMisaligned); }
    bool flag = bus.read(pc, 4, (uint8_t*)&ip.inst);
    if (!flag) { take_trap(Trap::InstructionAccessFault); }
}

void Core::decode(InstPack& ip) {
    // Decode
}

void Core::execute(InstPack& ip) {
    // Execute
}

void Core::reset() {
    // Reset
}

void Core::run() {
    // Run
}

void Core::take_trap(Trap trap) {
    // Take trap
    word_t epc = this->pc;
    auto prev_mode = this->mode;
    word_t cause = static_cast<word_t>(trap);
    if (fatal_exception(trap)) { throw FatalException(cause, epc); }
    static mstatus_t* mstatus = (mstatus_t*)&csr[MSTATUS];
    word_t excode = cause & 0x7FFFFFFF;
    bool intr = cause & 0x80000000;
    word_t bits = 1 << excode;
    // bool flag = cause & 0x80000000;
    auto next_mode = PrivilegeMode::Machine;
    if (prev_mode <= PrivilegeMode::Supervisor &&
        (!intr && csr[MEDELEG] && bits || intr && csr[MIDELEG] && bits)) {
        next_mode = PrivilegeMode::Supervisor;
        mstatus->SPP = static_cast<uint32_t>(prev_mode);
        mstatus->SPIE = mstatus->SIE;
    }
}