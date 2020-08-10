#ifndef __LUT_H__
#define __LUT_H__

#include <iosfwd>

namespace experis {

class Lut {
public:
    Lut() : m_lutTable() {
        buildLut();
    }
    //Lut(const Lut& a_lut) = default;
    //~Lut() = default;
    //Lut& operator=(const Lut& a_lut) = default;

    unsigned int GetLutResultByPosition(size_t a_position);

private:
    void buildLut();
    
    static const int LUT_TABLE_SIZE = 256;
    unsigned int m_lutTable[LUT_TABLE_SIZE];
};

} // experis

#endif