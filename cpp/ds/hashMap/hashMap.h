#ifndef __HASH_MAP_H__
#define __HASH_MAP_H__

#include <iostream>
#include <vector>
#include <cstring>
#include <list>
#include <utility>
#include <algorithm>
#include <assert.h>

template<class KeyT, class ValueT>
class Key {

typedef bool(*ComparePtr)(const KeyT&, const KeyT&);

public:
	~Key() {}
	Key(const KeyT& a_key, ComparePtr a_compareFunc);
			
	bool operator()(const std::pair<KeyT, ValueT>& m_pair) const;

private:
	KeyT m_key;
	ComparePtr m_compareFunc;
};

template<class KeyT, class ValueT>
Key<KeyT, ValueT>::Key(const KeyT& a_key, ComparePtr a_compareFunc)
: m_key(a_key)
, m_compareFunc(a_compareFunc) {
}

template<class KeyT, class ValueT>
bool Key<KeyT, ValueT>::operator()(const std::pair<KeyT, ValueT>& m_pair) const { 
        return m_compareFunc(m_pair.first, m_key);
}

template<class KeyT, class ValueT>
class HashMap : public std::vector<std::list<std::pair<KeyT, ValueT> > > {

typedef size_t(*HashPtr)(const KeyT&);
typedef bool(*ComparePtr)(const KeyT&, const KeyT&);
typedef typename std::list<std::pair<KeyT, ValueT> > T_list;
typedef typename std::vector< T_list > T_vector;
typedef typename T_list::const_iterator KeyValueC_iterator;
typedef typename T_list::iterator KeyValue_iterator;

public:
	~HashMap() {}
	
	HashMap(HashPtr a_hashFunc, ComparePtr a_compareFunc);
	HashMap(HashPtr a_hashFunc, ComparePtr a_compareFunc, unsigned int a_capacity);
	HashMap(const HashMap& a_hashMap);
	HashMap& operator=(const HashMap& a_hashMap);

	bool Put(const KeyT &a_key, const ValueT &a_value);
	void Remove(const KeyT &a_key); //throw const char* exception if not found
	
	bool Has(const KeyT &a_key) const;
	const ValueT& Retrieve(const KeyT &a_key) const; //throw const char* exception if not found, else return the value

private:
	static const unsigned int DEFAULT_CAPACITY = 16;
	
	void CheckMembersValidation(HashPtr a_hashFunc, ComparePtr a_compareFunc, unsigned int a_capacity);

	HashPtr m_hashFunc;
	ComparePtr m_compareFunc;
	unsigned int m_capacity;
};

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(HashPtr a_hashFunc, ComparePtr a_compareFunc)
: m_hashFunc(a_hashFunc)
, m_compareFunc(a_compareFunc)
, m_capacity(DEFAULT_CAPACITY)
, T_vector::vector(DEFAULT_CAPACITY) {

        CheckMembersValidation(a_hashFunc, a_compareFunc, DEFAULT_CAPACITY);
}

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(HashPtr a_hashFunc, ComparePtr a_compareFunc, unsigned int a_capacity)
: m_hashFunc(a_hashFunc)
, m_compareFunc(a_compareFunc)
, m_capacity(a_capacity)
, T_vector::vector(a_capacity) {

         CheckMembersValidation(a_hashFunc,a_compareFunc,a_capacity);
}

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(const HashMap<KeyT, ValueT>& a_hashMap)
: m_hashFunc(a_hashMap.m_hashFunc)
, m_compareFunc(a_hashMap.m_compareFunc)
, m_capacity(a_hashMap.m_capacity)
, T_vector::vector(a_hashMap) {

         CheckMembersValidation(a_hashMap.m_hashFunc, a_hashMap.m_compareFunc, a_hashMap.m_capacity);
}

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>& HashMap<KeyT, ValueT>::operator=(const HashMap<KeyT, ValueT>& a_hashMap) {

	if(this != &a_hashMap)
	{
		m_hashFunc = a_hashMap.m_hashFunc;
		m_compareFunc = a_hashMap.m_compareFunc;
		m_capacity = a_hashMap.m_capacity;
		this->operator=(a_hashMap);
	}
	return *this;
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::Put(const KeyT &a_key, const ValueT &a_value) {

	T_list &elementList = this->at(m_hashFunc(a_key) % m_capacity);
	KeyValue_iterator itr = std::find_if(elementList.begin(), elementList.end(), Key<KeyT, ValueT>(a_key, m_compareFunc));
	
	if(itr != elementList.end()) {
		return false;
	}
	elementList.push_back(std::pair<KeyT, ValueT>(a_key, a_value));
	
	return true;
}

struct NotFound {};

template<class KeyT, class ValueT>
void HashMap<KeyT, ValueT>::Remove(const KeyT &a_key) {
	
	T_list &elementList = this->at(m_hashFunc(a_key) % m_capacity);
	KeyValue_iterator itr = std::find_if(elementList.begin(), elementList.end(), Key<KeyT, ValueT>(a_key, m_compareFunc));
	
	if(itr == elementList.end()) {
		throw NotFound();
	}
	
	elementList.remove(*itr);
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::Has(const KeyT &a_key) const {
	
	const T_list &elementList = this->at(m_hashFunc(a_key) % m_capacity);
	KeyValueC_iterator itr = std::find_if(elementList.begin(), elementList.end(), Key<KeyT, ValueT>(a_key, m_compareFunc));
	
	return (itr != elementList.end());
}

template<class KeyT, class ValueT>
const ValueT& HashMap<KeyT, ValueT>::Retrieve(const KeyT &a_key) const {
        
        const T_list &elementList = this->at(m_hashFunc(a_key) % m_capacity);
	KeyValueC_iterator itr = std::find_if(elementList.begin(), elementList.end(), Key<KeyT, ValueT>(a_key, m_compareFunc));
	
	if(itr == elementList.end()) {
		throw NotFound();
	}
	
	return (*itr).second;
}

template<class KeyT, class ValueT>
void HashMap<KeyT, ValueT>::CheckMembersValidation(HashPtr a_hashFunc, ComparePtr a_compareFunc, unsigned int a_capacity) {

        assert(a_hashFunc == m_hashFunc);
        assert(a_compareFunc == m_compareFunc);
        assert(this->size() == m_capacity);
        
        for(typename T_vector::iterator first = this->begin() ; first != this->end() ; ++first) {
                assert(*first == T_list());
        }
}

#endif
