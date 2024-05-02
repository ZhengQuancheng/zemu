#include "device/Device.h"

class PLIC: public Device {
private:
public:
    PLIC();
    ~PLIC();
    bool read(size_t addr, size_t size, uint8_t* buff) override;
    bool write(size_t addr, size_t size, uint8_t* buff) override;
};
