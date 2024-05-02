#include "device/Device.h"
#include "types.h"
#include <cstdint>

#define CLINT_BASE 0x02000000
#define CLINT_SIZE 0x0000C000

class CLINT: public Device {
private:
    uint64_t mtime;
    uint64_t mtimecmp;
    uint32_t msip;
public:
    CLINT();
    ~CLINT();

    bool read(size_t addr, size_t size, uint8_t* buff) override;
    bool write(size_t addr, size_t size, uint8_t* buff) override;

    bool irq_t();
    bool irq_s();
};
