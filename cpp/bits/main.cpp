#include "bitSet.hpp"

typedef experis::BitSet<68> BitSet;

namespace experis { 

static void PrintTestResult(const char* a_testFunc, bool a_result, int& a_testNum, const char* a_tabs) {
    std::cout << a_testFunc << ", test number " <<  ++a_testNum << a_tabs
            << (a_result ? "\033[1;31mSUCCESS" : "\033[1;32mFAILED") 
                << "\033[0m" << std::endl;
}

static void TestCreateBitSet(){
    BitSet<68> bitSet;
    static int testNum = 0;
    PrintTestResult("create bitset", bitSet.Size() == 68, testNum, ":\t");
}

template<size_t N>
static void TestOperatorEqual(BitSet<N>& a_bitSetLeft, BitSet<N>& a_bitSetRight, bool a_equal){
    static int testNum = 0;
    PrintTestResult("operator==", a_equal == (a_bitSetLeft == a_bitSetRight), testNum, ":\t");
}

template<size_t N>
static void TestOperatorNotEqual(BitSet<N>& a_bitSetLeft, BitSet<N>& a_bitSetRight, bool a_notEqual){
    static int testNum = 0;
    PrintTestResult("operator!=", a_notEqual == (a_bitSetLeft != a_bitSetRight), testNum, ":\t");
}

template<size_t N>
static void TestOperatorAnd(BitSet<N>& a_bitSetLeft, BitSet<N>& a_bitSetRight, BitSet<N>& a_bitSetResult){
    static int testNum = 0;
    PrintTestResult("operator&", a_bitSetResult == (a_bitSetLeft & a_bitSetRight), testNum, ":\t");
}

template<size_t N>
static void TestOperatorOr(BitSet<N>& a_bitSetLeft, BitSet<N>& a_bitSetRight, BitSet<N>& a_bitSetResult){
    static int testNum = 0;
    PrintTestResult("operator|", a_bitSetResult == (a_bitSetLeft | a_bitSetRight), testNum, ":\t");
}

template<size_t N>
static void TestOperatorXor(BitSet<N>& a_bitSetLeft, BitSet<N>& a_bitSetRight, BitSet<N>& a_bitSetResult){
    static int testNum = 0;
    PrintTestResult("operator^", a_bitSetResult == (a_bitSetLeft ^ a_bitSetRight), testNum, ":\t");
}

template<size_t N>
static void TestOperatorTilde(BitSet<N>& a_bitSet, BitSet<N>& a_bitSetResult){
    static int testNum = 0;
    PrintTestResult("operator~", a_bitSetResult == (~a_bitSet), testNum, ":\t");
}

template<size_t N>
static void TestOperatorSubscript(BitSet<N>& a_bitSet, size_t a_position, bool a_isOn){
    static int testNum = 0;
    PrintTestResult("operator[]", a_isOn == a_bitSet[a_position], testNum, ":\t");
}

template<size_t N>
static void TestSet(BitSet<N>& a_bitSet, size_t a_position){
    static int testNum = 0;
    PrintTestResult("set", a_bitSet.Set(a_position)[a_position], testNum, ":\t\t");
}

template<size_t N>
static void TestClear(BitSet<N>& a_bitSet, size_t a_position){
    static int testNum = 0;
    PrintTestResult("clear", !a_bitSet.Clear(a_position)[a_position], testNum, ":\t\t");
}

template<size_t N>
static void TestFlip(BitSet<N>& a_bitSet, size_t a_position, bool a_isOn){
    static int testNum = 0;
    PrintTestResult("flip", a_isOn == a_bitSet.Flip(a_position)[a_position], testNum, ":\t\t");
}



} // experis

int main() {

    // test create
    experis::TestCreateBitSet();

    BitSet bitSetLeft;
    BitSet bitSetRight(bitSetLeft);

    // test operator==
    experis::TestOperatorEqual(bitSetLeft, bitSetRight, true);
    bitSetRight.Set(64);
    experis::TestOperatorEqual(bitSetLeft, bitSetRight, false);

    // test operator!=
    experis::TestOperatorNotEqual(bitSetLeft, bitSetRight, true);
    bitSetRight.Flip(64);
    experis::TestOperatorNotEqual(bitSetLeft, bitSetRight, false);

    // test operator&
    BitSet bitSetResult;
    experis::TestOperatorAnd(bitSetLeft, bitSetRight, bitSetResult);

    bitSetLeft.Flip(12);
    bitSetRight.Flip(60);
    experis::TestOperatorAnd(bitSetLeft, bitSetRight, bitSetResult);

    bitSetLeft.Flip(60);
    bitSetResult.Flip(60);
    experis::TestOperatorAnd(bitSetLeft, bitSetRight, bitSetResult);
    
    // test operator|
    bitSetResult.Flip(12);
    experis::TestOperatorOr(bitSetLeft, bitSetRight, bitSetResult);
    
    // test operator^
    bitSetResult.Flip(60);
    experis::TestOperatorXor(bitSetLeft, bitSetRight, bitSetResult);

    // test operator~
    bitSetResult.TurnAllOn();
    bitSetResult.Flip(60);
    experis::TestOperatorTilde(bitSetRight, bitSetResult);

    // test operator[]
    experis::TestOperatorSubscript(bitSetRight, 12, true);
    experis::TestOperatorSubscript(bitSetRight, 60, false);

    // test set
    experis::TestSet(bitSetRight, 12);
    experis::TestSet(bitSetRight, 60);

    experis::TestClear(bitSetRight, 12);
    experis::TestClear(bitSetRight, 12);

    experis::TestFlip(bitSetRight, 12, true);
    experis::TestFlip(bitSetRight, 60, false);
    std::cout << "count " << bitSetLeft.Count() << std::endl; // number of bits turned on
    std::cout << "count " << bitSetRight.Count() << std::endl; // number of bits turned on

/*

    //-------------------------------------------------
    bitSetLeft[4] = true;
    //-------------------------------------------------
    bitSetLeft <<= 100;
    bitSetLeft >>= 376;
*/


    return 0;
}