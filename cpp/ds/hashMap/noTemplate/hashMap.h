#ifndef __HASH_MAP_H__
#define __HASH_MAP_H__

#include <iostream>
#include <vector>
#include <cstring>
#include <list>
#include <utility>
#include <algorithm>

typedef std::string KeyT;
typedef std::string ValueT;

struct HashMapTypdef{
        typedef size_t(*HashPtr)(const KeyT&);
        typedef bool(*ComparePtr)(const KeyT&, const KeyT&);
        typedef std::list<std::pair<KeyT, ValueT> > T_list;
        typedef T_list::iterator T_iterator;
};

template<class KeyT>
class Key {
public:
	~Key() {}
	Key(const KeyT& a_key, HashMapTypdef::ComparePtr a_compareFunc);
		
	bool operator()(const std::pair<KeyT, ValueT>& m_pair) const;

private:
	KeyT m_key;
	HashMapTypdef::ComparePtr m_compareFunc;
};

template<class KeyT>
Key<KeyT>::Key(const KeyT& a_key, HashMapTypdef::ComparePtr a_compareFunc)
: m_key(a_key)
, m_compareFunc(a_compareFunc) {
}

template<class KeyT>
bool Key<KeyT>::operator()(const std::pair<KeyT, ValueT>& m_pair) const { 
        return m_compareFunc(m_pair.first, m_key);
}

class HashMap : public std::vector<std::list<std::pair<KeyT, ValueT> > > {
public:
	~HashMap() {}
	
	HashMap(HashMapTypdef::HashPtr a_hashFunc, HashMapTypdef::ComparePtr a_compareFunc);
	HashMap(HashMapTypdef::HashPtr a_hashFunc, HashMapTypdef::ComparePtr a_compareFunc, unsigned int a_capacity);
	HashMap(const HashMap& a_hashMap);
	HashMap& operator=(const HashMap& a_hashMap);

	bool Put(const KeyT &a_key, const ValueT &a_value);
        void Remove(const KeyT &a_key); //throw const char* exception if not found
	
	bool Has(const KeyT &a_key) const;
	ValueT& Retrieve(const KeyT &a_key) const; //throw const char* exception if not found, else return the value

private:
	static const unsigned int DEFAULT_CAPACITY = 16; 

	HashMapTypdef::T_list& findList(const KeyT &a_key) const;
	
	HashMapTypdef::HashPtr m_hashFunc;
	HashMapTypdef::ComparePtr m_compareFunc;
	unsigned int m_capacity;
};

HashMap::HashMap(HashMapTypdef::HashPtr a_hashFunc, HashMapTypdef::ComparePtr a_compareFunc)
: m_hashFunc(a_hashFunc)
, m_compareFunc(a_compareFunc)
, m_capacity(DEFAULT_CAPACITY)
, vector(DEFAULT_CAPACITY) {
}

HashMap::HashMap(HashMapTypdef::HashPtr a_hashFunc, HashMapTypdef::ComparePtr a_compareFunc, unsigned int a_capacity)
: m_hashFunc(a_hashFunc)
, m_compareFunc(a_compareFunc)
, m_capacity(a_capacity)
, vector(a_capacity) {
}

HashMap::HashMap(const HashMap& a_hashMap)
: m_hashFunc(a_hashMap.m_hashFunc)
, m_compareFunc(a_hashMap.m_compareFunc)
, m_capacity(a_hashMap.m_capacity)
, vector(a_hashMap) {
}

HashMap& HashMap::operator=(const HashMap& a_hashMap) {

	if(this != &a_hashMap)
	{
		m_hashFunc = a_hashMap.m_hashFunc;
		m_compareFunc = a_hashMap.m_compareFunc;
		m_capacity = a_hashMap.m_capacity;
		vector::operator=(a_hashMap);
	}
	return *this;
}

bool HashMap::Put(const KeyT &a_key, const ValueT &a_value) {

	HashMapTypdef::T_list &elementList = findList(a_key);
	HashMapTypdef::T_iterator itr = std::find_if(elementList.begin(), elementList.end(), Key<KeyT>(a_key, m_compareFunc));
	
	if(itr != elementList.end()) {
		return false;
	}
	elementList.push_back(std::pair<KeyT, ValueT>(a_key, a_value));
	
	return true;
}

void HashMap::Remove(const KeyT &a_key) {
	
	HashMapTypdef::T_list &elementList = findList(a_key);
	HashMapTypdef::T_iterator itr = std::find_if(elementList.begin(), elementList.end(), Key<KeyT>(a_key, m_compareFunc));
	
	if(itr == elementList.end()) {
		throw "key not found!";
	}
	
	elementList.remove(*itr);
}

bool HashMap::Has(const KeyT &a_key) const {
	
	HashMapTypdef::T_list &elementList = findList(a_key);
	HashMapTypdef::T_iterator itr = std::find_if(elementList.begin(), elementList.end(), Key<KeyT>(a_key, m_compareFunc));
	
	return (itr != elementList.end());
}

ValueT& HashMap::Retrieve(const KeyT &a_key) const {
        
        HashMapTypdef::T_list &elementList = findList(a_key);
	HashMapTypdef::T_iterator itr = std::find_if(elementList.begin(), elementList.end(), Key<KeyT>(a_key, m_compareFunc));
	
	if(itr == elementList.end()) {
		throw "key not found!";
	}
	
	return itr->second;
}

HashMapTypdef::T_list& HashMap::findList(const KeyT &a_key)const {

	size_t position = m_hashFunc(a_key) % m_capacity;
	
	return (reference)at(position);
}


#endif
