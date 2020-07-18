#ifndef __BUCKET_H__
#define __BUCKET_H__

#include <iostream>
#include <list>
#include <algorithm>
#include <assert.h>
#include "keyValue.h"
#include "key.h"

struct BucketType {
        typedef bool(*ComparePtr)(const KeyT&, const KeyT&);
        typedef typename std::list<KeyValue>::iterator KeyValue_iterator;
        typedef typename std::list<KeyValue>::const_iterator KeyValue_cIterator;
};

struct Exception {
        Exception(const std::string& a_error) { m_error = a_error; }
        
        const std::string& GetError() { return m_error; }
        std::string m_error;
};

class Bucket {
public:
        ~Bucket() {}
        Bucket(BucketType::ComparePtr a_compareFunc);
        Bucket(const Bucket& a_bucket);
        Bucket& operator=(const Bucket& a_bucket);
        
        bool Put(const KeyT& a_key, const ValueT& a_value);
        bool Has(const KeyT& a_key) const;
        void Remove(const KeyT& a_key);
        const ValueT& Retrieve(const KeyT& a_key) const;

private:
        std::list<KeyValue> m_list;
        BucketType::ComparePtr m_compareFunc;
};

Bucket::Bucket(BucketType::ComparePtr a_compareFunc)
: m_list()
, m_compareFunc(a_compareFunc) {

        assert(m_compareFunc == a_compareFunc);
        assert(m_list.size() == 0);
}

Bucket::Bucket(const Bucket& a_bucket)
: m_list(a_bucket.m_list)
, m_compareFunc(a_bucket.m_compareFunc) {
        
        assert(m_compareFunc == a_bucket.m_compareFunc);
        assert(m_list.size() == a_bucket.m_list.size());
}

Bucket& Bucket::operator=(const Bucket& a_bucket) {
        
        m_list = a_bucket.m_list;
        m_compareFunc = a_bucket.m_compareFunc;
}

//mem functions

bool Bucket::Put(const KeyT& a_key, const ValueT& a_value) {

        if(Has(a_key)) {
                return false;
        }
        
        m_list.push_back(KeyValue(a_key, a_value));
        return true;
}

bool Bucket::Has(const KeyT& a_key) const {

        return (find_if(m_list.begin(), m_list.end(), Key(a_key, m_compareFunc)) != m_list.end());
}

void Bucket::Remove(const KeyT& a_key) {

        BucketType::KeyValue_iterator itr = find_if(m_list.begin(), m_list.end(), Key(a_key, m_compareFunc));
        if(itr == m_list.end()) {
                throw Exception("key not exist!");
        }
        m_list.remove(*itr);
}

const ValueT& Bucket::Retrieve(const KeyT& a_key) const {

        BucketType::KeyValue_cIterator itr = find_if(m_list.begin(), m_list.end(), Key(a_key, m_compareFunc));
        if(itr  == m_list.end()) {
                throw Exception("key not exist!");
        }
        return itr->GetValue();
}





#endif
