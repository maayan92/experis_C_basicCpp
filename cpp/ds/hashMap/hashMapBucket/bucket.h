#ifndef __BUCKET_H__
#define __BUCKET_H__

#include <iostream>
#include <list>
#include <algorithm>
#include <assert.h>
#include "keyValue.h"
#include "key.h"

struct Exception {
        Exception(const std::string& a_error) { m_error = a_error; }
        
        const std::string& GetError() { return m_error; }
        std::string m_error;
};

template<class KeyT, class ValueT>
class Bucket {
typedef bool(*ComparePtr)(const KeyT&, const KeyT&);
typedef typename std::list< KeyValue<KeyT, ValueT> >::iterator KeyValue_iterator;
typedef typename std::list< KeyValue<KeyT, ValueT> >::const_iterator KeyValue_cIterator;
public:
        ~Bucket() {}
        Bucket(ComparePtr a_compareFunc);
        Bucket(const Bucket<KeyT, ValueT>& a_bucket);
        Bucket& operator=(const Bucket<KeyT, ValueT>& a_bucket);
        
        bool Put(const KeyT& a_key, const ValueT& a_value);
        bool Has(const KeyT& a_key) const;
        void Remove(const KeyT& a_key);
        const ValueT& Retrieve(const KeyT& a_key) const;

private:
        std::list< KeyValue<KeyT, ValueT> > m_list;
        ComparePtr m_compareFunc;
};

template<class KeyT, class ValueT>
Bucket<KeyT, ValueT>::Bucket(ComparePtr a_compareFunc)
: m_list()
, m_compareFunc(a_compareFunc) {

        assert(m_compareFunc == a_compareFunc);
        assert(m_list.size() == 0);
}

template<class KeyT, class ValueT>
Bucket<KeyT, ValueT>::Bucket(const Bucket<KeyT, ValueT>& a_bucket)
: m_list(a_bucket.m_list)
, m_compareFunc(a_bucket.m_compareFunc) {
        
        assert(m_compareFunc == a_bucket.m_compareFunc);
        assert(m_list.size() == a_bucket.m_list.size());
}

template<class KeyT, class ValueT>
Bucket<KeyT, ValueT>& Bucket<KeyT, ValueT>::operator=(const Bucket<KeyT, ValueT>& a_bucket) {
        
        m_list = a_bucket.m_list;
        m_compareFunc = a_bucket.m_compareFunc;
}

//mem functions

template<class KeyT, class ValueT>
bool Bucket<KeyT, ValueT>::Put(const KeyT& a_key, const ValueT& a_value) {

        if(Has(a_key)) {
                return false;
        }
        
        m_list.push_back(KeyValue<KeyT, ValueT>(a_key, a_value));
        return true;
}

template<class KeyT, class ValueT>
bool Bucket<KeyT, ValueT>::Has(const KeyT& a_key) const {

        return (find_if(m_list.begin(), m_list.end(), Key<KeyT, ValueT>(a_key, m_compareFunc)) != m_list.end());
}

template<class KeyT, class ValueT>
void Bucket<KeyT, ValueT>::Remove(const KeyT& a_key) {

        KeyValue_iterator itr = find_if(m_list.begin(), m_list.end(), Key<KeyT, ValueT>(a_key, m_compareFunc));
        if(itr == m_list.end()) {
                throw Exception("key not exist!");
        }
        m_list.remove(*itr);
}

template<class KeyT, class ValueT>
const ValueT& Bucket<KeyT, ValueT>::Retrieve(const KeyT& a_key) const {

        KeyValue_cIterator itr = find_if(m_list.begin(), m_list.end(), Key<KeyT, ValueT>(a_key, m_compareFunc));
        if(itr  == m_list.end()) {
                throw Exception("key not exist!");
        }
        return itr->GetValue();
}





#endif
