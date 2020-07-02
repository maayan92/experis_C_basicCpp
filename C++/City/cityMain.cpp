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
	try
	{
		cout << "street id -> " << s2.GetStreetID() << endl;
	}
	catch(const char* exc)
	{
		cout << exc << endl;;
	}
	try
	{
		cout << "buildeng id -> " << b2.GetBuildingID() << endl;
	}
	catch(const char* exc)
	{
		cout << exc << endl;;
	}
	try
	{
		street<char,int> s3(c.GetStreet('f'));
	}
	catch(const char* exc)
	{
		cout << exc << endl;;
	}
	
	
	return 0;
}
