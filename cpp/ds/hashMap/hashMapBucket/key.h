#ifndef __KEY_H__
#define __KEY_H__

#include "keyValue.h"

template<class KeyT, class ValueT>
class Key {
typedef bool(*ComparePtr)(const KeyT&, const KeyT&);
public:
        //~Key() = default;
        Key(const KeyT& a_key) : m_key(a_key) {}

        bool operator()(const KeyValue<KeyT, ValueT>& a_keyValue) const { return a_keyValue.GetKey() == m_key; }

private:
        KeyT m_key;
};

#endif
