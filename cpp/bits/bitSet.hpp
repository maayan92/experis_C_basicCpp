#ifndef __BIT_SET_H__
#define __BIT_SET_H__

#include <iostream>
#include <algorithm>

namespace experis {
typedef unsigned long BitsSetType;

template<size_t N>
class BitSet {
public:
    static const size_t BITS_SIZE = sizeof(BitsSetType)*8;

    BitSet();
    //BitSet(const BitSet& a_bitSet) = default;
    //~BitSet() = default;
    //BitSet& operator=(const BitSet& a_bitSet) = default;

    //operations:
    bool operator==(const BitSet& a_bitSet) const;
    bool operator!=(const BitSet& a_bitSet) const;
    BitSet operator&(const BitSet& a_bitSet) const;
    BitSet operator|(const BitSet& a_bitSet) const;
    BitSet operator^(const BitSet& a_bitSet) const;
    BitSet& operator~();
    BitSet& operator&=(const BitSet& a_bitSet);
    BitSet& operator|=(const BitSet& a_bitSet);
    BitSet& operator^=(const BitSet& a_bitSet);

    //MysteryClass operator[](size_t a_bitidx);
    bool operator[](size_t a_bitidx) const;

    BitSet& operator>>(size_t a_numOfBits);
    BitSet& operator<<(size_t a_numOfBits);

    //other mem functions:
    BitSet& Set(size_t a_bitNum);
    BitSet& Clear(size_t a_bitNum);
    BitSet& Flip(size_t a_bitNum);
    BitSet& TurnAllOn();
    BitSet& TurnAllOff();
    //size_t Count() const;
    bool IsAllOn() const;
    bool IsAllOff() const;
    size_t Size() const { return N; }

private:
    static const size_t NUM_BLOCKS = (N / BITS_SIZE) + (((N % BITS_SIZE) != 0) ? 1 : 0);
    //static const Lut lut;
    
    BitsSetType m_bits[NUM_BLOCKS];
};

} // experis

namespace experis {

static BitsSetType andOperator(BitsSetType a_left, BitsSetType a_right) {
    return a_left & a_right;
}

static BitsSetType orOperator(BitsSetType a_left, BitsSetType a_right) {
    return a_left | a_right;
}

static BitsSetType xorOperator(BitsSetType a_left, BitsSetType a_right) {
    return a_left ^ a_right;
}

static BitsSetType tildaOperator(BitsSetType a_element) {
    return ~a_element;
}

static BitsSetType turnOff(BitsSetType a_element) {
    return a_element & 0;
}

static BitsSetType turnOn(BitsSetType a_element) {
    return a_element | ~(0);
}

// CTOR:

template<size_t N>
BitSet<N>::BitSet()
: m_bits() {
}

// operations:

template<size_t N>
bool BitSet<N>::operator==(const BitSet& a_bitSet) const {
    return std::equal(m_bits, m_bits + NUM_BLOCKS, a_bitSet.m_bits);
}

template<size_t N>
bool BitSet<N>::operator!=(const BitSet& a_bitSet) const {
    return !std::equal(m_bits, m_bits + NUM_BLOCKS, a_bitSet.m_bits);
}

template<size_t N>
BitSet<N> BitSet<N>::operator&(const BitSet& a_bitSet) const {
    BitSet<N> result;
    std::transform (m_bits, m_bits + NUM_BLOCKS, a_bitSet.m_bits, result.m_bits, andOperator);
    return result;
}

template<size_t N>
BitSet<N> BitSet<N>::operator|(const BitSet& a_bitSet) const {
    BitSet<N> result;
    std::transform (m_bits, m_bits + NUM_BLOCKS, a_bitSet.m_bits, result.m_bits, orOperator);
    return result;
}

template<size_t N>
BitSet<N> BitSet<N>::operator^(const BitSet& a_bitSet) const {
    BitSet<N> result;
    std::transform (m_bits, m_bits + NUM_BLOCKS, a_bitSet.m_bits, result.m_bits, xorOperator);
    return result;
}

template<size_t N>
BitSet<N>& BitSet<N>::operator~() {
    std::transform (m_bits, m_bits + NUM_BLOCKS, m_bits, tildaOperator);
    m_bits[NUM_BLOCKS - 1] >>= (BITS_SIZE - (N % BITS_SIZE));
    return *this;
}

template<size_t N>
BitSet<N>& BitSet<N>::operator&=(const BitSet& a_bitSet) {
    std::transform (m_bits, m_bits + NUM_BLOCKS, a_bitSet.m_bits, m_bits, andOperator);
    return *this;
}

template<size_t N>
BitSet<N>& BitSet<N>::operator|=(const BitSet& a_bitSet) {
    std::transform (m_bits, m_bits + NUM_BLOCKS, a_bitSet.m_bits, m_bits, orOperator);
    return *this;
}

template<size_t N>
BitSet<N>& BitSet<N>::operator^=(const BitSet& a_bitSet) {
    std::transform (m_bits, m_bits + NUM_BLOCKS, a_bitSet.m_bits, m_bits, xorOperator);
    return *this;
}

template<size_t N>
bool BitSet<N>::operator[](size_t a_bitidx) const {
    return (m_bits[a_bitidx / BITS_SIZE] & (1 << (a_bitidx % BITS_SIZE)));
}

template<size_t N>
class ShiftLeft {
public:
    ShiftLeft(size_t a_numOfBits) : m_numOfBits(a_numOfBits) {}
    BitsSetType operator()(BitsSetType a_left, BitsSetType a_right) {
        BitsSetType result = (~(0) & (a_left >> (m_numOfBits % BitSet<N>::BITS_SIZE)));
        return result | (a_right << (BitSet<N>::BITS_SIZE - (m_numOfBits % BitSet<N>::BITS_SIZE)));
    }
private:
    size_t m_numOfBits;
};

template<size_t N>
BitSet<N>& BitSet<N>::operator>>(size_t a_numOfBits) {
    size_t setFromPos = (a_numOfBits / BITS_SIZE);
    std::transform (m_bits + setFromPos, m_bits + (NUM_BLOCKS - 1)
                    , m_bits + (setFromPos + 1), m_bits, ShiftLeft<N>(a_numOfBits));

    ++setFromPos;
    m_bits[NUM_BLOCKS - setFromPos] = (~(0) & (m_bits[NUM_BLOCKS - setFromPos] >> (a_numOfBits % BITS_SIZE)));
    std::transform(m_bits + (NUM_BLOCKS - setFromPos + 1), m_bits + NUM_BLOCKS, m_bits, turnOff);

    return *this;
}

template<size_t N>
BitSet<N>& BitSet<N>::operator<<(size_t a_numOfBits) {
    
    return *this;
}

// other mem functions

template<size_t N>
BitSet<N>& BitSet<N>::Set(size_t a_bitNum) {
    m_bits[a_bitNum / BITS_SIZE] |= (1 << a_bitNum % BITS_SIZE);
    return *this;
}

template<size_t N>
BitSet<N>& BitSet<N>::Clear(size_t a_bitNum) {
    m_bits[a_bitNum / BITS_SIZE] &= ~(1 << a_bitNum % BITS_SIZE);
    return *this;
}

template<size_t N>
BitSet<N>& BitSet<N>::Flip(size_t a_bitNum) {
    m_bits[a_bitNum / BITS_SIZE] ^= (1 << a_bitNum % BITS_SIZE);
    return *this;
}

template<size_t N>
BitSet<N>& BitSet<N>::TurnAllOn() {
    std::transform(m_bits, m_bits + NUM_BLOCKS, m_bits, turnOn);
    m_bits[NUM_BLOCKS - 1] >>= (BITS_SIZE - (N % BITS_SIZE));
    return *this;
}

template<size_t N>
BitSet<N>& BitSet<N>::TurnAllOff() {
    std::transform(m_bits, m_bits + NUM_BLOCKS, m_bits, turnOff);
    return *this;
}
/*
template<size_t N>
size_t BitSet<N>::Count() const {
    BitsSetType mask = turnOn(m_bits[0]);
    size_t count = 0;
    return (count + (m_bits[0] & mask));
}
*/

template<size_t N>
bool BitSet<N>::IsAllOn() const {
    BitSet<N> bitSetAllOn;
    bitSetAllOn.TurnAllOn();
    return (bitSetAllOn == *this);
}

template<size_t N>
bool BitSet<N>::IsAllOff() const {
    BitSet<N> bitSetAllOn;
    bitSetAllOn.TurnAllOff();
    return (bitSetAllOn == *this);
}

} // experis

#endif