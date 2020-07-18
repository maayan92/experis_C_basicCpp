#ifndef __KEY_VALUE_H__
#define __KEY_VALUE_H__

#include <iosfwd>

typedef std::string KeyT;
typedef std::string ValueT;

class KeyValue {
public:
        ~KeyValue() {}
        KeyValue(const KeyT& a_key, const ValueT& a_value);
        KeyValue(const KeyValue& a_keyValue);
        KeyValue& operator=(const KeyValue& a_keyValue);
        
        bool operator==(const KeyValue& a_keyValue);

        const KeyT& GetKey() const { return m_key; }
        const ValueT& GetValue() const { return m_value; }
        void SetValue(const ValueT& a_value) { m_value = a_value; }

private:
        KeyT m_key;
        ValueT m_value;
};

KeyValue::KeyValue(const KeyT& a_key, const ValueT& a_value)
: m_key(a_key)
, m_value(a_value) {

        assert(m_key == a_key);
        assert(m_value == a_value);
}

KeyValue::KeyValue(const KeyValue& a_keyValue)
: m_key(a_keyValue.m_key)
, m_value(a_keyValue.m_value) {

        assert(m_key == a_keyValue.m_key);
        assert(m_value == a_keyValue.m_value);
}

KeyValue& KeyValue::operator=(const KeyValue& a_keyValue) {

        if(this != &a_keyValue) {
                m_key = a_keyValue.m_key;
                m_value = a_keyValue.m_value;
        }
        return *this;
}

bool KeyValue::operator==(const KeyValue& a_keyValue) {

        return (m_key == a_keyValue.m_key && m_value == a_keyValue.m_value);
}

#endif
