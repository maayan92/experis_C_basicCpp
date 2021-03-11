#include <iosfwd>

namespace experis {

typedef size_t BitsSetType;
static const int BYTE_IN_BITS = 8;
static const size_t BITS_SIZE = sizeof(BitsSetType)*BYTE_IN_BITS;

static BitsSetType andOperator(BitsSetType a_left, BitsSetType a_right) {
    return a_left & a_right;
}

static BitsSetType orOperator(BitsSetType a_left, BitsSetType a_right) {
    return a_left | a_right;
}

static BitsSetType xorOperator(BitsSetType a_left, BitsSetType a_right) {
    return a_left ^ a_right;
}

static BitsSetType tildeOperator(BitsSetType a_element) {
    return ~a_element;
}

static BitsSetType turnOff(BitsSetType a_element) {
    return a_element & 0;
}

static BitsSetType turnOn(BitsSetType a_element) {
    return a_element | ~(0);
}

class ShiftRight {
public:
    ShiftRight(size_t a_numOfBits) : m_numOfBits(a_numOfBits) {}
    BitsSetType operator()(BitsSetType a_left, BitsSetType a_right) {
        return (a_left >> (m_numOfBits % BITS_SIZE))
                 | (a_right << (BITS_SIZE - (m_numOfBits % BITS_SIZE)));
    }
private:
    size_t m_numOfBits;
};

class ShiftLeft {
public:
    ShiftLeft(size_t a_numOfBits) : m_numOfBits(a_numOfBits) {}
    BitsSetType operator()(BitsSetType a_left, BitsSetType a_right) {
        return (a_left >> (BITS_SIZE - (m_numOfBits % BITS_SIZE)))
                 | (a_right << (m_numOfBits % BITS_SIZE));
    }
private:
    size_t m_numOfBits;
};

} // experis