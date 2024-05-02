# include "device/Device.h"

#define DRAM_BASE 0x80000000ul
#define DRAM_SIZE 0x10000000ul

class DRAM: public Device {
public:
    DRAM(size_t dram_size = DRAM_SIZE);
    ~DRAM();
    bool read(size_t addr, size_t size, uint8_t* buff) override;
    bool write(size_t addr, size_t size, uint8_t* buff) override;
    void set_image(const char* file);
private:
    uint8_t* data;
    size_t size;
};
