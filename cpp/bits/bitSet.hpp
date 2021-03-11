#ifndef __BIT_SET_H__
#define __BIT_SET_H__

#include <iostream>
#include <algorithm>
#include "bitwiseOperations.hpp"
#include "lut.hpp"

namespace experis {

template<size_t N>
class BitSet {
public:
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

    BitSet operator>>(size_t a_numOfBits);
    BitSet operator<<(size_t a_numOfBits);
    //BitSet& operator>>=(size_t a_numOfBits);
    //BitSet& operator<<=(size_t a_numOfBits);

    //other mem functions:
    BitSet& Set(size_t a_bitNum);
    BitSet& Clear(size_t a_bitNum);
    BitSet& Flip(size_t a_bitNum);
    BitSet& TurnAllOn();
    BitSet& TurnAllOff();
    size_t Count() const;
    bool IsAllOn() const;
    bool IsAllOff() const;
    size_t Size() const { return N; }

private:
    size_t countBits(BitsSetType a_bits) const;

    class CountOnBits;
    static const size_t NUM_BLOCKS = (N / BITS_SIZE) + (((N % BITS_SIZE) != 0) ? 1 : 0);
    
    Lut m_lut;
    BitsSetType m_bits[NUM_BLOCKS];
};

} // experis

namespace experis {

// CTOR:

template<size_t N>
BitSet<N>::BitSet()
: m_bits()
, m_lut() {
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
    std::transform (m_bits, m_bits + NUM_BLOCKS, m_bits, tildeOperator);
    m_bits[NUM_BLOCKS - 1] &= ((BitsSetType)~(0) >> (BITS_SIZE - (N % BITS_SIZE)));
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
BitSet<N> BitSet<N>::operator>>(size_t a_numOfBits) {
    BitSet<N> bitSetResult;
    size_t setFromPos = a_numOfBits / BITS_SIZE;
    std::transform (m_bits + setFromPos, m_bits + (NUM_BLOCKS - 1)
                    , m_bits + (setFromPos + 1), bitSetResult.m_bits, ShiftRight(a_numOfBits));

    ++setFromPos;
    bitSetResult.m_bits[NUM_BLOCKS - setFromPos] = (~(0) & (m_bits[NUM_BLOCKS - setFromPos] >> (a_numOfBits % BITS_SIZE)));
    return bitSetResult;
}

template<size_t N>
BitSet<N> BitSet<N>::operator<<(size_t a_numOfBits) {
    BitSet<N> bitSetResult;
    size_t setFromPos = a_numOfBits / BITS_SIZE;
    std::transform (m_bits, m_bits + (NUM_BLOCKS - 1 - setFromPos), m_bits + setFromPos
                        , bitSetResult.m_bits + setFromPos + 1, ShiftLeft(a_numOfBits));

    bitSetResult.m_bits[setFromPos] = m_bits[0] << (a_numOfBits % BITS_SIZE);
    bitSetResult.m_bits[NUM_BLOCKS-1] &= ((BitsSetType)~(0) >> (BITS_SIZE - (N % BITS_SIZE)));
    return bitSetResult;
}

// other mem functions

template<size_t N>
BitSet<N>& BitSet<N>::Set(size_t a_bitNum) {
    if(a_bitNum <= N) { 
        m_bits[a_bitNum / BITS_SIZE] |= (1 << a_bitNum % BITS_SIZE);
    }

    return *this;
}

template<size_t N>
BitSet<N>& BitSet<N>::Clear(size_t a_bitNum) {
    if(a_bitNum <= N) { 
        m_bits[a_bitNum / BITS_SIZE] &= ~(1 << a_bitNum % BITS_SIZE);
    }

    return *this;
}

template<size_t N>
BitSet<N>& BitSet<N>::Flip(size_t a_bitNum) {
    if(a_bitNum <= N) { 
        m_bits[a_bitNum / BITS_SIZE] ^= (1 << a_bitNum % BITS_SIZE);
    }

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

template<size_t N>
size_t BitSet<N>::Count() const {
    size_t sum = 0;
    for (size_t i = 0; i < NUM_BLOCKS; i++) {
        sum += countBits(m_bits[i]);
    }
    return sum;
}


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

// private funcrion:

template<size_t N>
size_t BitSet<N>::countBits(BitsSetType a_bits) const {
    size_t sum = 0;
    for (size_t i = 0; i < sizeof(BitsSetType); i++) {
        sum += m_lut.GetLutResultByPosition((a_bits & 0xff));
        a_bits >>= BYTE_IN_BITS;
    }
    return sum;
}

} // experis

#endif