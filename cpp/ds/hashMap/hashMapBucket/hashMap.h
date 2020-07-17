#ifndef __HASH_MAP_H__
#define __HASH_MAP_H__

#include "bucket.h"
#include <vector>

//typedef std::string KeyT;
//typedef std::string ValueT;
typedef size_t(*HashPrt)(const KeyT&);

class HashMap : public std::vector<Bucket> {
typedef typename std::vector<Bucket> T_vector;
public:
        ~HashMap() {}
        HashMap(HashPrt a_hashFunc, BucketType::ComparePtr a_compareFunc);
        //HashMap(HashPrt a_hashFunc, BucketType::ComparePtr a_compareFunc, unsigned int a_capacity); //TODO
        //HashMap(const HashMap& a_hashMap);
        //HashMap& operator=(const HashMap& a_hashMap);
        
        bool Put(const KeyT& a_key, const ValueT& a_value);
        bool Has(const KeyT& a_key) const;
        void Remove(const KeyT& a_key);
        const ValueT& Retrieve(const KeyT& a_key) const ;

private:
        static const unsigned int DEFAULT_CAPACITY = 16;
        
        unsigned int GetPosition(const KeyT& a_key) const;
        void CheckMembersValidation(HashPrt a_hashFunc, BucketType::ComparePtr a_compareFunc, unsigned int a_capacity) const;
        
        unsigned int m_capacity;
        HashPrt m_hashFunc;
};

HashMap::HashMap(HashPrt a_hashFunc, BucketType::ComparePtr a_compareFunc)
: m_capacity(DEFAULT_CAPACITY)
, m_hashFunc(a_hashFunc)
, vector(DEFAULT_CAPACITY, Bucket(a_compareFunc)) {

        CheckMembersValidation(a_hashFunc, a_compareFunc, DEFAULT_CAPACITY);
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

void HashMap::CheckMembersValidation(HashPrt a_hashFunc, BucketType::ComparePtr a_compareFunc, unsigned int a_capacity) const {

        assert(m_capacity == a_capacity);
        //for(T_vector::iterator itr = this->T_vector::begin() ; itr != this->T_vector::end() ; ++itr) {
                //assert(itr == Bucket(a_hashFunc, a_compareFunc));
        //}
}




#endif
