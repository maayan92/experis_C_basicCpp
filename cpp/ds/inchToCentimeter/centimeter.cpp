#include "centimeter.h"
#include "inch.h"

Centimeter::Centimeter()
: m_value() {
}

Centimeter::Centimeter(double a_value)
: m_value(a_value) {
}

Centimeter& Centimeter::operator=(const Centimeter& a_centimeter) {

    if(this != &a_centimeter) {
        m_value = a_centimeter.m_value;
    }
    return *this;
}

Centimeter::operator Inch() {
    return Inch(m_value * convertToInch);
}

double Centimeter::GetVal() {
    return m_value;
}