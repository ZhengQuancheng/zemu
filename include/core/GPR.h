#include "types.h"
#include <cassert>

class GPR {
private:
    word_t data[32] = { 0 };
public:
    word_t& operator[](uint8_t index) {
        data[0] = 0;
        assert(index >= 0 && index < 32);
        return data[index];
    }
};
