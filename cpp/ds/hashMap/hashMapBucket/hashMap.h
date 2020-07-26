#ifndef __HASH_MAP_H__
#define __HASH_MAP_H__

#include "bucket.h"
#include <vector>

template<class KeyT, class ValueT, class HashFunc, class EqualsFunc = EqualsKey<KeyT, ValueT> >
class HashMap : public std::vector< Bucket<KeyT, ValueT, EqualsFunc> > {
        typedef typename std::vector< Bucket<KeyT, ValueT, EqualsFunc> > Vector;
        friend class HasIter<KeyT>;
public:
        //a_compareFunc - if NULL then undefined behaviour.
        //a_size - if 0 or less then undefined behaviour.
        HashMap();
        HashMap(unsigned int a_size);
        HashMap(const HashMap<KeyT, ValueT, HashFunc, EqualsFunc>& a_hashMap);
        HashMap& operator=(const HashMap<KeyT, ValueT, HashFunc, EqualsFunc>& a_hashMap);
        //~HashMap() = default;
        
        bool Put(const KeyT& a_key, const ValueT& a_value);
        bool Has(const KeyT& a_key) const; //throw Exception if not found.
        void Remove(const KeyT& a_key); //throw Exception if not found.
        const ValueT& Retrieve(const KeyT& a_key) const ;

private:
        static const unsigned int DEFAULT_CAPACITY = 16;
        
        unsigned int GetPosition(const KeyT& a_key) const;
        
        struct HasIter;
};

template<class KeyT, class ValueT, class HashFunc, class EqualsFunc>
HashMap<KeyT, ValueT, HashFunc, EqualsFunc>::HashMap()
: Vector::vector(DEFAULT_CAPACITY, Bucket<KeyT, ValueT, EqualsFunc>()) {

        assert(this->size() == DEFAULT_CAPACITY);
}

template<class KeyT, class ValueT, class HashFunc, class EqualsFunc>
HashMap<KeyT, ValueT, HashFunc, EqualsFunc>::HashMap(unsigned int a_size)
: Vector::vector(a_size, Bucket<KeyT, ValueT, EqualsFunc>()) {

        assert(a_size > 0);
        assert(this->size() == a_size);
}

template<class KeyT, class ValueT, class HashFunc, class EqualsFunc>
HashMap<KeyT, ValueT, HashFunc, EqualsFunc>::HashMap(const HashMap<KeyT, ValueT, HashFunc, EqualsFunc>& a_hashMap)
: Vector::vector(a_hashMap) {

        assert(this->size() == a_hashMap.size());
}

template<class KeyT, class ValueT, class HashFunc, class EqualsFunc>
HashMap<KeyT, ValueT, HashFunc, EqualsFunc>& HashMap<KeyT, ValueT, HashFunc, EqualsFunc>::operator=(const HashMap<KeyT, ValueT, HashFunc, EqualsFunc>& a_hashMap) {

        if(this != &a_hashMap) { (*this) = a_hashMap; }
        return *this;
}

template<class KeyT, class ValueT, class HashFunc, class EqualsFunc>
bool HashMap<KeyT, ValueT, HashFunc, EqualsFunc>::Put(const KeyT& a_key, const ValueT& a_value) {

        return (*this)[GetPosition(a_key)].Put(a_key, a_value);
}

template<class KeyT, class ValueT, class HashFunc, class EqualsFunc>
bool HashMap<KeyT, ValueT, HashFunc, EqualsFunc>::Has(const KeyT& a_key) const {

        return (*this)[GetPosition(a_key)].Has(a_key);
}

template<class KeyT, class ValueT, class HashFunc, class EqualsFunc>
void HashMap<KeyT, ValueT, HashFunc, EqualsFunc>::Remove(const KeyT& a_key) {

        (*this)[GetPosition(a_key)].Remove(a_key);
}

template<class KeyT, class ValueT, class HashFunc, class EqualsFunc>
const ValueT& HashMap<KeyT, ValueT, HashFunc, EqualsFunc>::Retrieve(const KeyT& a_key) const {

        return (*this)[GetPosition(a_key)].Retrieve(a_key);
}

template<class KeyT, class ValueT, class HashFunc, class EqualsFunc>
unsigned int HashMap<KeyT, ValueT, HashFunc, EqualsFunc>::GetPosition(const KeyT& a_key) const {

        return HashFunc()(a_key) % this->size();
}

// Iterator
template<class KeyT>
class HasIter {
public:
        HasIter(KeyT* a_itr);
        //HasIter(const HasIter& a_itr) = default;
        //~HasIter() = default;

        bool operator!=(const Iter& a_itr);
        HasIter& operator++();
        KeyT& operator*() { return *m_itr; }
        
        HasIter& Begin() { return &(*this)[0]; m_position = 1; }
        HasIter& End() { return 0; }

private:
        KeyT* m_itr;
        unsigned int m_position;
};

template<class KeyT>
HasIter<KeyT>::HasIter(KeyT* a_itr)
: m_itr(a_itr)
, m_position(0) {
}

template<class KeyT>
HasIter<KeyT>& HasIter<KeyT>::operator++() {
        
        if(m_position ) {
                return 0;
        }
        return &(*this)[m_position++];
}







#endif
