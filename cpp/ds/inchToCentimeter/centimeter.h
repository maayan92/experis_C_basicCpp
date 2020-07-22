#ifndef __CENTIMETER_H__
#define __CENTIMETER_H__

#include <iostream>
class Inch;

class Centimeter {
public:
    Centimeter();
    Centimeter(double a_value);
    //Centimeter(const Centimeter& a_centimeter) = default;
    //~Centimeter() = default;
    Centimeter& operator=(const Centimeter& a_centimeter);

    operator Inch();
    double GetVal();

private:
    const double convertToInch = 2.54;

    double m_value;
};

#endif