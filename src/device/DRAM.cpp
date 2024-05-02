#include "device/DRAM.h"
#include "types.h"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <ios>
#include <fstream>

DRAM::DRAM(size_t dram_size) {
    this->size = dram_size;
    this->data = new uint8_t[dram_size];
}

DRAM::~DRAM() {
    delete[] this->data;
}

bool DRAM::read(size_t addr, size_t size, uint8_t* buff) {
    uint64_t offset = addr - DRAM_BASE;
    if (offset + size > this->size) {
        return false;
    }
    std::memcpy(buff, this->data + offset, size);
    return true;
}

bool DRAM::write(size_t addr, size_t size, uint8_t* buff) {
    uint64_t offset = addr - DRAM_BASE;
    if (offset + size > this->size) {
        return false;
    }
    std::memcpy(this->data + offset, buff, size);
    return true;
}

void DRAM::set_image(const char* file) {
    size_t file_size = std::filesystem::file_size(file);
    assert(file_size <= this->size);
    std::ifstream ifs(file, std::ios::binary);
    ifs.read(reinterpret_cast<char*>(this->data), file_size);
}
