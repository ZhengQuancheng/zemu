#ifndef _TRAP_H_
#define _TRAP_H_

#include "types.h"
#include <exception>

#define MSB_1 (1ull << (64 - 1))

enum class Trap: word_t{
    // Exception
    InstructionAddressMisaligned   = 0,
    InstructionAccessFault         = 1,
    IllegalInstruction             = 2,
    Breakpoint                     = 3,
    LoadAddressMisaligned          = 4,
    LoadAccessFault                = 5,
    StoreAddressMisaligned         = 6,
    StoreAccessFault               = 7,
    UserEnvironmentCall            = 8,
    SupervisorEnvironmentCall      = 9,
    MachineEnvironmentCall         = 11,
    InstructionPageFault           = 12,
    LoadPageFault                  = 13,
    StorePageFault                 = 15,
    // Interrupt
    UserSoftwareInterrupt          = MSB_1 | 0,
    SupervisorSoftwareInterrupt    = MSB_1 | 1,
    MachineSoftwareInterrupt       = MSB_1 | 3,
    UserTimerInterrupt             = MSB_1 | 4,
    SupervisorTimerInterrupt       = MSB_1 | 5,
    MachineTimerInterrupt          = MSB_1 | 7,
    UserExternalInterrupt          = MSB_1 | 8,
    SupervisorExternalInterrupt    = MSB_1 | 9
};

inline bool fatal_exception(Trap& trap) {
    return (trap == Trap::InstructionAddressMisaligned) 
        || (trap == Trap::InstructionAccessFault) 
        || (trap == Trap::IllegalInstruction) 
        || (trap == Trap::Breakpoint) 
        || (trap == Trap::LoadAddressMisaligned) 
        || (trap == Trap::LoadAccessFault) 
        || (trap == Trap::StoreAddressMisaligned) 
        || (trap == Trap::StoreAccessFault) 
        || (trap == Trap::InstructionPageFault) 
        || (trap == Trap::LoadPageFault) 
        || (trap == Trap::StorePageFault);
}

class RISCVException: public std::exception {
private:
    word_t cause;
    word_t epc;
    word_t tval;
public:
    RISCVException(word_t cause, word_t epc, word_t tval = 0) : cause(cause), epc(epc), tval(tval) {}
    const char* what() const noexcept override { 
        return "Fatal Exception";
    }
};

#endif // _TRAP_H_
