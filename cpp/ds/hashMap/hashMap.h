#ifndef __HASH_MAP_H__
#define __HASH_MAP_H__

#include <iostream>
#include <vector>
#include <cstring>
#include <list>
#include <utility>
#include <algorithm>

template<class KeyT, class ValueT>
class Key {

typedef bool(*comparePtr)(const KeyT&, const KeyT&);

public:
	~Key() {}
	Key(const KeyT& a_key, comparePtr a_compareFunc) : m_key(a_key), m_compareFunc(a_compareFunc) {}
			
	bool operator()(const std::pair<KeyT, ValueT>& m_pair)const { return m_compareFunc(m_pair.first, m_key); }

private:
	KeyT m_key;
	comparePtr m_compareFunc;
};

template<class KeyT, class ValueT>
class HashMap : public std::vector< std::list<std::pair<KeyT, ValueT> > > {

typedef size_t(*hashPtr)(const KeyT&);
typedef bool(*comparePtr)(const KeyT&, const KeyT&);
typedef std::list<std::pair<KeyT, ValueT> > t_list;
typedef std::vector< std::list<std::pair<KeyT, ValueT> > > t_vector;
typedef typename std::list<std::pair<KeyT, ValueT> >::iterator t_listIterator;

public:
	~HashMap() {}
	
	HashMap(hashPtr a_hashFunc, comparePtr a_compareFunc);
	HashMap(hashPtr a_hashFunc, comparePtr a_compareFunc, unsigned int a_capacity);
	HashMap(const HashMap& a_hashMap);
	HashMap& operator=(const HashMap& a_hashMap);

	bool Put(const KeyT &a_key, const ValueT &a_value);
	bool Remove(const KeyT &a_key);
	
	bool Has(const KeyT &a_key) const;
	//??? Retrieve(const KeyT &a_key) const;

private:
	static const unsigned int DEFAULT_CAPACITY = 16;

	t_list& findList(const KeyT &a_key)const;
	
	hashPtr m_hashFunc;
	comparePtr m_compareFunc;
	unsigned int m_capacity;


};

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(hashPtr a_hashFunc, comparePtr a_compareFunc)
: m_hashFunc(a_hashFunc)
, m_compareFunc(a_compareFunc)
, m_capacity(DEFAULT_CAPACITY)
, t_vector::vector(DEFAULT_CAPACITY) {
}

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(hashPtr a_hashFunc, comparePtr a_compareFunc, unsigned int a_capacity)
: m_hashFunc(a_hashFunc)
, m_compareFunc(a_compareFunc)
, m_capacity(a_capacity)
, t_vector::vector(a_capacity) {
}

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>::HashMap(const HashMap<KeyT, ValueT>& a_hashMap)
: m_hashFunc(a_hashMap.m_hashFunc)
, m_compareFunc(a_hashMap.m_compareFunc)
, m_capacity(a_hashMap.m_capacity)
, t_vector::vector(a_hashMap) {
}

template<class KeyT, class ValueT>
HashMap<KeyT, ValueT>& HashMap<KeyT, ValueT>::operator=(const HashMap<KeyT, ValueT>& a_hashMap) {

	if(this != &a_hashMap)
	{
		m_hashFunc = a_hashMap.m_hashFunc;
		m_capacity = a_hashMap.m_capacity;
		t_vector::operator=(a_hashMap);
	}
	return *this;
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::Put(const KeyT &a_key, const ValueT &a_value) {

	t_list &elementList = findList(a_key);
	t_listIterator itr = std::find_if(elementList.begin(), elementList.end(), Key<KeyT, ValueT>(a_key, m_compareFunc));
	
	if(itr != elementList.end()) {
		return false;
	}
	elementList.push_back(std::pair<KeyT, ValueT>(a_key, a_value));
	
	return true;
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::Remove(const KeyT &a_key) {
	
	t_list &elementList = findList(a_key);
	t_listIterator itr = std::find_if(elementList.begin(), elementList.end(), Key<KeyT, ValueT>(a_key, m_compareFunc));
	
	if(itr == elementList.end()) {
		return false;
	}
	
	KeyT removedKey = itr->first;
	elementList.remove(*itr);
	
	return true;
}

template<class KeyT, class ValueT>
bool HashMap<KeyT, ValueT>::Has(const KeyT &a_key) const {
	
	t_list &elementList = findList(a_key);
	t_listIterator itr = std::find_if(elementList.begin(), elementList.end(), Key<KeyT, ValueT>(a_key, m_compareFunc));
	
	return (itr != elementList.end());
}

t_list& HashMap<KeyT, ValueT>::findList(const KeyT &a_key)const {

	size_t position = m_hashFunc(a_key) % m_capacity;
	
	return (reference)at(position);
}

#endif
