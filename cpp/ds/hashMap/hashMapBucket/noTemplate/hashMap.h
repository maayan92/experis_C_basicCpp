#ifndef __HASH_MAP_H__
#define __HASH_MAP_H__

#include "bucket.h"
#include <vector>

class HashMap : public std::vector<Bucket> {
typedef size_t(*HashPrt)(const KeyT&);
public:
        ~HashMap() {}
        HashMap(HashPrt a_hashFunc, BucketType::ComparePtr a_compareFunc);
        HashMap(HashPrt a_hashFunc, BucketType::ComparePtr a_compareFunc, unsigned int a_capacity);
        HashMap(const HashMap& a_hashMap);
        HashMap& operator=(const HashMap& a_hashMap);
        
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

HashMap::HashMap(HashPrt a_hashFunc, BucketType::ComparePtr a_compareFunc)
: m_capacity(DEFAULT_CAPACITY)
, m_hashFunc(a_hashFunc)
, vector(DEFAULT_CAPACITY, Bucket(a_compareFunc)) {

        CheckMembersValidation(a_hashFunc, DEFAULT_CAPACITY);
}

HashMap::HashMap(HashPrt a_hashFunc, BucketType::ComparePtr a_compareFunc, unsigned int a_capacity)
: m_capacity(a_capacity)
, m_hashFunc(a_hashFunc)
, vector(a_capacity, Bucket(a_compareFunc)) {

        CheckMembersValidation(a_hashFunc, a_capacity);
}

HashMap::HashMap(const HashMap& a_hashMap)
: m_capacity(a_hashMap.m_capacity)
, m_hashFunc(a_hashMap.m_hashFunc)
, vector(a_hashMap) {

        CheckMembersValidation(a_hashMap.m_hashFunc, a_hashMap.m_capacity);
}

HashMap& HashMap::operator=(const HashMap& a_hashMap) {

        if(this != &a_hashMap) {
                m_capacity = a_hashMap.m_capacity;
                m_hashFunc = a_hashMap.m_hashFunc;
                (*this) = a_hashMap;
        }
        return *this;
}

bool HashMap::Put(const KeyT& a_key, const ValueT& a_value) {

        return (*this)[GetPosition(a_key)].Put(a_key, a_value);
}

bool HashMap::Has(const KeyT& a_key) const {

        return (*this)[GetPosition(a_key)].Has(a_key);
}

void HashMap::Remove(const KeyT& a_key) {

        (*this)[GetPosition(a_key)].Remove(a_key);
}

const ValueT& HashMap::Retrieve(const KeyT& a_key) const {

        return (*this)[GetPosition(a_key)].Retrieve(a_key);
}

unsigned int HashMap::GetPosition(const KeyT& a_key) const {

        return m_hashFunc(a_key) %  m_capacity;
}

void HashMap::CheckMembersValidation(HashPrt a_hashFunc, unsigned int a_capacity) const {

        assert(m_capacity == a_capacity);
        assert(m_hashFunc == a_hashFunc);
        assert(this->size() == a_capacity);
}

#endif
