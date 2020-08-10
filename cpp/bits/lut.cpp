#include "lut.hpp"
#include <algorithm>

namespace experis {

static const size_t LUT_TABLE_SIZE = 256;
static const size_t BITS_SIZE = sizeof(char)*8;

static unsigned int countOnBits(unsigned char a_num) {
    size_t  count = 0;
    for(size_t i = 0;i < BITS_SIZE;++i) {
        count += ((a_num >> i) & 1);
    }
    return count;
}

void Lut::buildLut() {
    for (unsigned int i = 0 ; i < LUT_TABLE_SIZE ; ++i){
        m_lutTable[i] = countOnBits(i);
    }
}

unsigned int Lut::GetLutResultByPosition(size_t a_position) {
    return m_lutTable[a_position];
}

} // experis