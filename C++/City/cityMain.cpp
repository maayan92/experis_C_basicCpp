#include "building.h"
#include "street.h"
#include "city.h"

#include <iostream>
using namespace std;

int main()
{
	building<int> b(3);
	street<char,int> s('s');
	city<const char*,char,int> c("city");
	
	s.AddBuilding2Street(b);
	c.AddStreet(s);
	
	street<char,int> s2(c.GetStreet('s'));
	building<int> b2(s2.GetBuilding(3));
	
	cout << "city id -> " << c.GetCityID() << endl;
	cout << "street id -> " << s2.GetStreetID() << endl;
	cout << "buildeng id -> " << b2.getBuildingID() << endl;
	
	street<char,int> s3(c.GetStreet('f'));
	
	cout << "street with id 'f' " << ((s3.GetStreetID() != 'f') ? "not found" : "found") << " in the city" << endl;
	
	
	return 0;
}
