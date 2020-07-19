#ifndef __BUCKET_H__
#define __BUCKET_H__

#include <iostream>
#include <list>
#include <algorithm>
#include <assert.h>
//#include <exception>
#include "keyValue.h"

struct Exception{
        Exception(const std::string& a_error) { m_error = a_error; }
        
        const std::string& GetError() { return m_error; }
        std::string m_error;
};
/*
template<class KeyT>
class EqualsKey {
public:
        //~EqualsKey() = default;
        EqualsKey(const KeyT& a_key) : m_key(a_key) {}

        bool operator()(const KeyValue<KeyT, ValueT>& a_keyValue) const { return a_keyValue.GetKey() == m_key; }
private:
        KeyT m_key;
};
*/

template<class KeyT, class ValueT>
struct EqualsKey {
        EqualsKey(const KeyT& a_key) : m_key(a_key) {}
        bool operator()(const KeyValue<KeyT, ValueT>& a_keyValue) const {
                return m_key == a_keyValue.GetKey();
        }
        KeyT m_key;
};

/*
template<class KeyT>
struct Equals {
        bool operator()(const KeyT& a_left, const KeyT& a_right) const {
                return a_left == a_right;
        }
};
*/
template<class KeyT, class ValueT, class EqualsFunc = EqualsKey<KeyT, ValueT> >
class Bucket {  
typedef typename std::list< KeyValue<KeyT, ValueT> >::iterator KeyValue_iterator;
typedef typename std::list< KeyValue<KeyT, ValueT> >::const_iterator KeyValue_cIterator;
public:
        Bucket();
        Bucket(const Bucket<KeyT, ValueT, EqualsFunc>& a_bucket);
        Bucket& operator=(const Bucket<KeyT, ValueT, EqualsFunc>& a_bucket);
        //~Bucket() = default;
        
        bool Put(const KeyT& a_key, const ValueT& a_value);
        bool Has(const KeyT& a_key) const; //throw Exception if not found.
        void Remove(const KeyT& a_key); //throw Exception if not found.
        const ValueT& Retrieve(const KeyT& a_key) const;

private:
        std::list< KeyValue<KeyT, ValueT> > m_list;
};

template<class KeyT, class ValueT, class EqualsFunc>
Bucket<KeyT, ValueT, EqualsFunc>::Bucket()
: m_list() {

        assert(m_list.size() == 0);
}

template<class KeyT, class ValueT, class EqualsFunc>
Bucket<KeyT, ValueT, EqualsFunc>::Bucket(const Bucket<KeyT, ValueT, EqualsFunc>& a_bucket)
: m_list(a_bucket.m_list) {
        
        assert(m_list.size() == a_bucket.m_list.size());
}

template<class KeyT, class ValueT, class EqualsFunc>
Bucket<KeyT, ValueT, EqualsFunc>& Bucket<KeyT, ValueT, EqualsFunc>::operator=(const Bucket<KeyT, ValueT, EqualsFunc>& a_bucket) {
        
        if(this != &a_bucket) { m_list = a_bucket.m_list; }
        
        return *this;
}

//mem functions

template<class KeyT, class ValueT, class EqualsFunc>
bool Bucket<KeyT, ValueT, EqualsFunc>::Put(const KeyT& a_key, const ValueT& a_value) {

        if(Has(a_key)) {
                return false;
        }
        
        m_list.push_back(KeyValue<KeyT, ValueT>(a_key, a_value));
        return true;
}

template<class KeyT, class ValueT, class EqualsFunc>
bool Bucket<KeyT, ValueT, EqualsFunc>::Has(const KeyT& a_key) const {

        return (find_if(m_list.begin(), m_list.end(), EqualsKey<KeyT, ValueT>(a_key)) != m_list.end());
}

template<class KeyT, class ValueT, class EqualsFunc>
void Bucket<KeyT, ValueT, EqualsFunc>::Remove(const KeyT& a_key) {

        KeyValue_iterator itr = find_if(m_list.begin(), m_list.end(), EqualsKey<KeyT, ValueT>(a_key));
        if(itr == m_list.end()) {
                throw Exception("key not exist!");
        }
        m_list.remove(*itr);
}

template<class KeyT, class ValueT, class EqualsFunc>
const ValueT& Bucket<KeyT, ValueT, EqualsFunc>::Retrieve(const KeyT& a_key) const {

        KeyValue_cIterator itr = find_if(m_list.begin(), m_list.end(), EqualsKey<KeyT, ValueT>(a_key));
        if(itr  == m_list.end()) {
                throw Exception("key not exist!");
        }
        return itr->GetValue();
}

#endif
