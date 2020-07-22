#ifndef __INCH_H__
#define __INCH_H__

#include <iostream>
class Centimeter;

class Inch {
public:
    Inch();
    Inch(double a_value);
    //Inch(const Inch& a_inch) = default;
    //~Inch() = default;
    Inch& operator=(const Inch& a_inch);

    operator Centimeter();
    double GetVal();

private:
    const double convertToCentimeter = 2.54;

    double m_value;
};

#endif