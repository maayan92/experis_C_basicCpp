#ifndef __KEY_H__
#define __KEY_H__

#include "keyValue.h"

//template<class KeyT, class ValueT>
class Key {
typedef bool(*ComparePtr)(const KeyT&, const KeyT&);

public:
        ~Key() {}
        Key(const KeyT& a_key, ComparePtr a_compareFunc);

        bool operator()(const KeyValue& a_keyValue) const;

private:
        KeyT m_key;
        ComparePtr m_compareFunc;
};

//template<class KeyT, class ValueT>
Key::Key(const KeyT& a_key, ComparePtr a_compareFunc)
: m_key(a_key)
, m_compareFunc(a_compareFunc) {

        assert(m_key == a_key);
        assert(m_compareFunc == a_compareFunc);
}

//template<class KeyT, class ValueT>
bool Key::operator()(const KeyValue& a_keyValue) const {
        return m_compareFunc(a_keyValue.GetKey(), m_key);
}


#endif
