#include "bitSet.hpp"

typedef experis::BitSet<61> BitSet;

int main() {

    BitSet b1;
    BitSet b2(b1);

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
    b1.TurnAllOff();


    std::cout << "size -> " << b1.Size() << std::endl;


/*

    b1.Count(); // number of bits turned on
    b1.IsAllOn();
    b1.IsAllOff();
    

    //-------------------------------------------------
    b1[4] = true;
    std::cout << b2[6];
    //-------------------------------------------------
    b1 << 100;
    b1 >> 376;
    b1 <<= 100;
    b1 >>= 376;
*/


    return 0;
}