#ifndef __HASH_MAP_H__
#define __HASH_MAP_H__

#include "bucket.h"
#include <vector>

template<class KeyT, class ValueT>
class HashMap : public std::vector< Bucket<KeyT, ValueT> > {
typedef size_t(*HashPrt)(const KeyT&);
typedef bool(*ComparePtr)(const KeyT&, const KeyT&);
typedef typename std::vector< Bucket<KeyT, ValueT> > T_vector;
public:
        ~HashMap() {}
        HashMap(HashPrt a_hashFunc, ComparePtr a_compareFunc);
        HashMap(HashPrt a_hashFunc, ComparePtr a_compareFunc, unsigned int a_capacity);
        HashMap(const HashMap<KeyT, ValueT>& a_hashMap);
        HashMap& operator=(const HashMap<KeyT, ValueT>& a_hashMap);
        
        bool Put(const KeyT& a_key, const ValueT& a_value);
        bool Has(const KeyT& a_key) const;
        void Remove(const KeyT& a_key);
        const ValueT& Retrieve(const KeyT& a_key) const ;

private:
        static const unsigned int DEFAULT_CAPACITY = 16;
        
        unsigned int GetPosition(const KeyT& a_key) const;
        void CheckMembersValidation(HashPrt a_hashFunc, unsigned int a_capacity) const;
        
        unsigned int m_capacity;
        HashPrt m_hashFunc;
};

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(HashPrt a_hashFunc, ComparePtr a_compareFunc)
: m_capacity(DEFAULT_CAPACITY)
, m_hashFunc(a_hashFunc)
, T_vector::vector(DEFAULT_CAPACITY, Bucket<KeyT, ValueT>(a_compareFunc)) {

        CheckMembersValidation(a_hashFunc, DEFAULT_CAPACITY);
}

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(HashPrt a_hashFunc, ComparePtr a_compareFunc, unsigned int a_capacity)
: m_capacity(a_capacity)
, m_hashFunc(a_hashFunc)
, T_vector::vector(a_capacity, Bucket<KeyT, ValueT>(a_compareFunc)) {

        CheckMembersValidation(a_hashFunc, a_capacity);
}

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(const HashMap<KeyT, ValueT>& a_hashMap)
: m_capacity(a_hashMap.m_capacity)
, m_hashFunc(a_hashMap.m_hashFunc)
, T_vector::vector(a_hashMap) {

        CheckMembersValidation(a_hashMap.m_hashFunc, a_hashMap.m_capacity);
}

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>& HashMap<KeyT, ValueT>::operator=(const HashMap<KeyT, ValueT>& a_hashMap) {

        if(this != &a_hashMap) {
                m_capacity = a_hashMap.m_capacity;
                m_hashFunc = a_hashMap.m_hashFunc;
                (*this) = a_hashMap;
        }
        return *this;
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::Put(const KeyT& a_key, const ValueT& a_value) {

        return (*this)[GetPosition(a_key)].Put(a_key, a_value);
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::Has(const KeyT& a_key) const {

        return (*this)[GetPosition(a_key)].Has(a_key);
}

template<class KeyT, class ValueT>
void HashMap<KeyT, ValueT>::Remove(const KeyT& a_key) {

        (*this)[GetPosition(a_key)].Remove(a_key);
}

template<class KeyT, class ValueT>
const ValueT& HashMap<KeyT, ValueT>::Retrieve(const KeyT& a_key) const {

        return (*this)[GetPosition(a_key)].Retrieve(a_key);
}

template<class KeyT, class ValueT>
unsigned int HashMap<KeyT, ValueT>::GetPosition(const KeyT& a_key) const {

        return m_hashFunc(a_key) %  m_capacity;
}

template<class KeyT, class ValueT>
void HashMap<KeyT, ValueT>::CheckMembersValidation(HashPrt a_hashFunc, unsigned int a_capacity) const {

        assert(m_capacity == a_capacity);
        assert(m_hashFunc == a_hashFunc);
        assert(this->size() == a_capacity);
}

#endif
