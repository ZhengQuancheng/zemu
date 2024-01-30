#ifndef _CORE_H_
#define _CORE_H_

#include "Bus.h"
#include "types.h"
#include "Trap.h"

#include <array>
#include <cstdint>
#include <memory>


/* *********** Immediate Extraction *********** */
inline word_t imm_U(uint32_t inst) {
    struct U_type {
        uint32_t opcode     : 7;
        uint32_t rd         : 5;
        int32_t imm_31_12   : 20;
    };
    U_type* inst_U = (U_type*)&inst;
    return inst_U->imm_31_12 << 12;
}
inline word_t imm_J(uint32_t inst) {
    struct J_type {
        uint32_t opcode     : 7;
        uint32_t rd         : 5;
        uint32_t imm_19_12  : 8;
        uint32_t imm_11     : 1;
        uint32_t imm_10_1   : 10;
        int32_t imm_20      : 1;
    };
    J_type* inst_J = (J_type*)&inst;
    return  (inst_J->imm_20 << 20) | (inst_J->imm_19_12 << 12) | 
            (inst_J->imm_11 << 11) | (inst_J->imm_10_1  << 1 ) ;
}
inline word_t imm_I(uint32_t inst) {
    struct I_type {
        uint32_t opcode     : 7;
        uint32_t rd         : 5;
        uint32_t funct3     : 3;
        uint32_t rs1        : 5;
        int32_t imm_11_0    : 12;
    };
    I_type* inst_I = (I_type*)&inst;
    return inst_I->imm_11_0;
}
inline word_t imm_B(uint32_t inst) {
    struct B_type {
        uint32_t opcode     : 7;
        uint32_t imm_11     : 1;
        uint32_t imm_4_1    : 4;
        uint32_t funct3     : 3;
        uint32_t rs1        : 5;
        uint32_t rs2        : 5;
        uint32_t imm_10_5   : 6;
        int32_t imm_12      : 1;
    };
    B_type* inst_B = (B_type*)&inst;
    return  (inst_B->imm_12  << 12) | (inst_B->imm_11 << 11) | 
            (inst_B->imm_10_5 << 5) | (inst_B->imm_4_1 << 1) ;
}
inline word_t imm_S(uint32_t inst) {
    struct S_type {
        uint32_t opcode : 7;
        uint32_t imm_4_0 : 5;
        uint32_t funct3 : 3;
        uint32_t rs1 : 5;
        uint32_t rs2 : 5;
        int32_t imm_11_5 : 7;
    };
    S_type* inst_S = (S_type*)&inst;
    return  (inst_S->imm_11_5 << 5) | (inst_S->imm_4_0);
}
/* *********** Immediate Extraction *********** */

enum class Instruction {
    LUI, AUIPC,
    JAL, JALR,
    BEQ, BNE, BLT, BGE, BLTU, BGEU,
    LB, LH, LW, LD, LBU, LHU, LWU,
    SB, SH, SW, SD,
    ADDI, SLTI, SLTIU, XORI, ORI, ANDI, SLLI, SRLI, SRAI,
    ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND,
    MUL, MULH, MULHSU, MULHU, DIV, DIVU, REM, REMU,
    ECALL, EBREAK, MRET, CSRRW, CSRRS, CSRRC, CSRRWI, CSRRSI, CSRRCI,
    ADDIW, SLLIW, SRLIW, SRAIW, ADDW, SUBW, SLLW, SRLW, SRAW,
    MULW, DIVW, DIVUW, REMW, REMUW
};

enum class PrivilegeMode: uint8_t {
    User, Supervisor, Machine
};

class Core {
private:
    struct InstPack {
        Instruction type;
        uint32_t inst;
        word_t pc;
        word_t imm;
        uint8_t rd;
        uint8_t rs1;
        uint8_t rs2;
        uint8_t funct3;
        uint8_t funct7;
    };

    const uint8_t hart_id;
    PrivilegeMode mode;
    word_t pc;
    std::array<word_t, 32> gpr;
    std::array<word_t, 4096> csr;
    Bus& bus;
    void fetch(InstPack& ip);
    void decode(InstPack& ip);
    void execute(InstPack& ip);
    void take_trap(Trap trap);
public:
    Core(Bus& bus, uint8_t hart_id);
    ~Core();
    void reset();
    void run();
};

#endif // _CORE_H_
