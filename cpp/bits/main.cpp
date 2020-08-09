#include "bitSet.hpp"

typedef experis::BitSet<61> BitSet;

int main() {

    BitSet b1;
    BitSet b2(b1);

    //experis::Lut lut;

    //b1 = b2;

    std::cout << (b1 == b2) << std::endl;
    std::cout << (b1 != b2) << std::endl;

    BitSet resultAnd = b1 & b2;
    BitSet resultOr = b1 | b2;
    BitSet resultXor = b1 ^ b2;
 
    ~b1;
    b1 &= b2;
    b1 |= b2;
    b1 ^= b2;
    b1.Set(12); // 12 is the bit number
    b1.Clear(45);
    b1.Flip(12);
    b1.TurnAllOn();
    std::cout << "is all on? -> " << b1.IsAllOn() << std::endl;
    b1.TurnAllOff();
    std::cout << "is all off? -> " << b1.IsAllOff() << std::endl;

    //std::cout << "count" << b1.Count() << std::endl; // number of bits turned on

    std::cout << "size -> " << b1.Size() << std::endl;
    b2.Flip(6);

    b2 >> 5;
    std::cout << b2[1] << std::endl;

/*

    //-------------------------------------------------
    b1[4] = true;
    //-------------------------------------------------
    b1 >> 376;
    b1 <<= 100;
    b1 >>= 376;
*/


    return 0;
}