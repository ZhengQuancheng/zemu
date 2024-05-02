#include "types.h"
#include <cstdint>

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
    uint16_t WPRI_3 : 9;
    uint32_t UXL    : 2;
    uint32_t SXL    : 2;
    uint32_t SBE    : 1;
    uint32_t MBE    : 1;
    uint64_t WPRI_4 : 25;
    uint32_t SD     : 1;
};

class CSR {
private:
    word_t status;
    word_t ip;
public:
    enum Name: word_t {
        MSTATUS = 0x300,
        MEDELEG = 0x302,
        MIDELEG = 0x303,
        MIE     = 0x304,
        MTVEC   = 0x305,
        MEPC    = 0x341,
        MCAUSE  = 0x342,
        MTVAL   = 0x343,
        MIP     = 0x344,
    };
};
