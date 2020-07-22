#include "inch.h"
#include "centimeter.h"

Inch::Inch()
: m_value() {
}
    
Inch::Inch(double a_value)
: m_value(a_value) {
}

Inch& Inch::operator=(const Inch& a_inch) {
    
    if(this != &a_inch) {
        m_value = a_inch.m_value;
    }
    return *this;
}

Inch::operator Centimeter() {
    return Centimeter(m_value / convertToCentimeter);
}
    
double Inch::GetVal() {
    return m_value;
}