#ifndef __KEY_VALUE_H__
#define __KEY_VALUE_H__

#include <iosfwd>

template<class KeyT, class ValueT>
class KeyValue {
public:
        KeyValue(const KeyT& a_key, const ValueT& a_value);
        KeyValue(const KeyValue<KeyT, ValueT>& a_keyValue);
        KeyValue& operator=(const KeyValue<KeyT, ValueT>& a_keyValue);
        //~KeyValue() = default;
        
        bool operator==(const KeyValue& a_keyValue);

        const KeyT& GetKey() const { return m_key; }
        const ValueT& GetValue() const { return m_value; }
        void SetValue(const ValueT& a_value) { m_value = a_value; }

private:
        KeyT m_key;
        ValueT m_value;
};

template<class KeyT, class ValueT>
KeyValue<KeyT, ValueT>::KeyValue(const KeyT& a_key, const ValueT& a_value)
: m_key(a_key)
, m_value(a_value) {

        assert(m_key == a_key);
        assert(m_value == a_value);
}

template<class KeyT, class ValueT>
KeyValue<KeyT, ValueT>::KeyValue(const KeyValue& a_keyValue)
: m_key(a_keyValue.m_key)
, m_value(a_keyValue.m_value) {

        assert(m_key == a_keyValue.m_key);
        assert(m_value == a_keyValue.m_value);
}

template<class KeyT, class ValueT>
KeyValue<KeyT, ValueT>& KeyValue<KeyT, ValueT>::operator=(const KeyValue& a_keyValue) {

        if(this != &a_keyValue) {
                m_key = a_keyValue.m_key;
                m_value = a_keyValue.m_value;
        }
        return *this;
}

template<class KeyT, class ValueT>
bool KeyValue<KeyT, ValueT>::operator==(const KeyValue& a_keyValue) {

        return (m_key == a_keyValue.m_key && m_value == a_keyValue.m_value);
}

#endif
