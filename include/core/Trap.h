#ifndef _TRAP_H_
#define _TRAP_H_

#include "types.h"
#include <exception>

struct mstatus_t {
    uint32_t WPRI_0 : 1;
    uint32_t SIE    : 1;
    uint32_t WPRI_1 : 1;
    uint32_t MIE    : 1;
    uint32_t WPRI_2 : 1;
    uint32_t SPIE   : 1;
    uint32_t UBE    : 1;
    uint32_t MPIE   : 1;
    uint32_t SPP    : 1;
    uint32_t VS     : 2;
    uint32_t MPP    : 2;
    uint32_t FS	    : 2;
    uint32_t XS     : 2;
    uint32_t MPRV   : 1;
    uint32_t SUM    : 1;
    uint32_t MXR    : 1;
    uint32_t TVM    : 1;
    uint32_t TW     : 1;
    uint32_t TSR    : 1;
#ifdef CONFIG_ISA64
    uint16_t WPRI_3 : 9;
    uint32_t UXL    : 2;
    uint32_t SXL    : 2;
    uint32_t SBE    : 1;
    uint32_t MBE    : 1;
    uint64_t WPRI_4 : 25;
    uint32_t SD     : 1;
#else
    uint32_t WPRI_3 : 8;
    uint32_t SD     : 1;
#endif
};

/* Machine Level CSRs */
#define MSTATUS     0x300
#define MEDELEG     0x302
#define MIDELEG     0x303
#define MIE         0x304
#define MTVEC       0x305
#define MEPC        0x341
#define MCAUSE      0x342
#define MTVAL       0x343
#define MIP         0x344

/* Supervisor Level CSRs */
#define SSTATUS     0x100
#define SIE         0x104
#define STVEC       0x105
#define SEPC        0x141
#define SCAUSE      0x142
#define STVAL       0x143
#define SIP         0x144
#define SATP        0x180

#define MSB_1 (1ull << (XLEN - 1))

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

class FatalException: public std::exception {
private:
    word_t cause;
    word_t epc;
    word_t tval;
public:
    FatalException(word_t cause, word_t epc, word_t tval = 0) : cause(cause), epc(epc), tval(tval) {}
    const char* what() const noexcept override { 
        return "Fatal Exception";
    }
};

#endif // _TRAP_H_
