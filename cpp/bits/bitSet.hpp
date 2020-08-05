#ifndef __BIT_SET_H__
#define __BIT_SET_H__

#include <iostream>
#include <algorithm>

namespace experis {

template<size_t N>
class BitSet {
public:
    BitSet();
    //BitSet(const BitSet& a_bitSet) = default;
    //~BitSet() = default;
    //BitSet& operator=(const BitSet& a_bitSet) = default;

    //operations:
    bool operator==(const BitSet& a_bitSet);
    bool operator!=(const BitSet& a_bitSet);
    BitSet operator&(const BitSet& a_bitSet);
    BitSet operator|(const BitSet& a_bitSet);
    BitSet operator^(const BitSet& a_bitSet);
    BitSet& operator~();
    BitSet& operator&=(const BitSet& a_bitSet);
    BitSet& operator|=(const BitSet& a_bitSet);
    BitSet& operator^=(const BitSet& a_bitSet);

    //other mem functions:
    BitSet& Set(size_t a_bitNum);
    BitSet& Clear(size_t a_bitNum);
    BitSet& Flip(size_t a_bitNum);
    BitSet& TurnAllOn();
    BitSet& TurnAllOff();
    size_t Size() { return N; }

    //MysteryClass operator[](size_t a_bitidx);
    //bool operator[](size_t a_bitidx) const;

private:
    static const size_t BITS_SIZE = sizeof(unsigned long)*8;
    static const size_t NUM_BLOCKS = (N / BITS_SIZE) + (((N % BITS_SIZE) != 0) ? 1 : 0);
    unsigned long m_bits[NUM_BLOCKS];
};

} // experis

namespace experis {

static unsigned long andOperator(unsigned long a_left, unsigned long a_right) {
    return a_left & a_right;
}

static unsigned long orOperator(unsigned long a_left, unsigned long a_right) {
    return a_left | a_right;
}

static unsigned long xorOperator(unsigned long a_left, unsigned long a_right) {
    return a_left ^ a_right;
}

static unsigned long tildaOperator(unsigned long a_element) {
    return ~a_element;
}

static unsigned long TurnOff(unsigned long a_element) {
    return a_element & 0;
}

// CTOR:

template<size_t N>
BitSet<N>::BitSet()
: m_bits() {
}

// operations:

template<size_t N>
bool BitSet<N>::operator==(const BitSet& a_bitSet) {
    return std::equal(m_bits, m_bits + NUM_BLOCKS, a_bitSet.m_bits);
}

template<size_t N>
bool BitSet<N>::operator!=(const BitSet& a_bitSet) {
    return !std::equal(m_bits, m_bits + NUM_BLOCKS, a_bitSet.m_bits);
}

template<size_t N>
BitSet<N> BitSet<N>::operator&(const BitSet& a_bitSet) {
    BitSet<N> result;
    std::transform (m_bits, m_bits + NUM_BLOCKS, a_bitSet.m_bits, result.m_bits, andOperator);
    return result;
}

template<size_t N>
BitSet<N> BitSet<N>::operator|(const BitSet& a_bitSet) {
    BitSet<N> result;
    std::transform (m_bits, m_bits + NUM_BLOCKS, a_bitSet.m_bits, result.m_bits, orOperator);
    return result;
}

template<size_t N>
BitSet<N> BitSet<N>::operator^(const BitSet& a_bitSet) {
    BitSet<N> result;
    std::transform (m_bits, m_bits + NUM_BLOCKS, a_bitSet.m_bits, result.m_bits, xorOperator);
    return result;
}

template<size_t N>
BitSet<N>& BitSet<N>::operator~() {
    std::transform (m_bits, m_bits + NUM_BLOCKS, m_bits, tildaOperator);
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

static unsigned long TurnOn(unsigned long a_element) {
    return a_element | ~(0);
}

template<size_t N>
BitSet<N>& BitSet<N>::TurnAllOn() {
    std::transform(m_bits, m_bits + (NUM_BLOCKS - 1), m_bits, TurnOn);
    m_bits[NUM_BLOCKS - 1] |= (~(0) >> (BITS_SIZE - (N % BITS_SIZE)));
    return *this;
}

template<size_t N>
BitSet<N>& BitSet<N>::TurnAllOff() {
    std::transform(m_bits, m_bits + NUM_BLOCKS, m_bits, TurnOff);
    return *this;
}

} // experis

#endif