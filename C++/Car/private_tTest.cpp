#include <cstring>
#include <iostream>
using namespace std;

#include "car_t.h"
#include "bus_t.h"
#include "private_t.h"

const int cars = 10;

const char* GetGearTypeAsChar(Gear _gear)
{
	return (STANDARD == _gear) ? "standard" : "automatic";
}

int main()
{
	int cont = 1, busLine;
	unsigned int action, carType;
	private_t p1(1500,STANDARD), p2, p3(1800,AUTOMATIC), p4(p2);
	bus_t b1(56,80,1800,AUTOMATIC), b2, b3(2,50,1800,STANDARD), b4(b3);
	
	while (cont) {
	
		cout << endl << "Choose action: " << endl;
		cout << "1 - get car name " << endl;
		cout << "2 - get car gear type " << endl;
		cout << "3 - car operator assignment " << endl;
		cout << "4 - car operator less than " << endl;
		cout << "5 - compare two cars " << endl << endl;
		
		cout << "bus car additional options: " << endl;
		cout << "6 - bus cars get line number " << endl;
		cout << "7 - bus cars set line number " << endl;
		cout << "8 - bus cars get number of seats " << endl << endl;
	
		cout << "private car additional options: " << endl;
		cout << "9 - accelerate private car " << endl;
		cout << "10 - reduce speed private car " << endl;
		cout << "11 - get private car speed " << endl;
		
		cout << "Any another number - stop " << endl;

		cin >>  action;
		switch (action) {
		
			case 1:	
				cout << endl << "choose car type: " << endl << "1 - bus car" << endl << "2 - private car" << endl;
				cin >> carType;
				switch(carType)
				{
					case 1: cout << endl << "\033[1;31m" << b1.GetCarName() << "\033[0m" << endl; break;
						
					case 2: cout << endl << "\033[1;31m" << p1.GetCarName() << "\033[0m" << endl; break;
					
					default : cout << endl << "\033[1;31mwrong key \033[0m" << endl; break;
				}
				break;
				
			case 2:	
				cout << endl << "choose car type: " << endl << "1 - bus car" << endl << "2 - private car" << endl;
				cin >> carType;
				switch(carType)
				{
					case 1: cout << endl << "\033[1;31m" << GetGearTypeAsChar(b1.GetGearType()) << "\033[0m" << endl; break;
						
					case 2: cout << endl << "\033[1;31m" << GetGearTypeAsChar(p1.GetGearType()) << "\033[0m" << endl; break;
					
					default : cout << endl << "\033[1;31mwrong key \033[0m" << endl; break;
				}
				break;
				
			case 3:	
				cout << endl << "choose car type: " << endl << "1 - bus car" << endl << "2 - private car" << endl;
				cin >> carType;
				switch(carType)
				{
					case 1:	cout << endl << "\033[1;31m" << "gear type before -> " << GetGearTypeAsChar(b1.GetGearType()) << ", after -> " ;
						b1 = b2;
						cout << GetGearTypeAsChar(b1.GetGearType()) << "\033[0m" << endl;
						break;
						
					case 2: cout << endl << "\033[1;31m" << "gear type before -> " << GetGearTypeAsChar(p1.GetGearType()) << ", after -> " ;
						p1 = p3;
						cout << GetGearTypeAsChar(p1.GetGearType()) << "\033[0m" << endl;
						break;
					
					default : cout << endl << "\033[1;31mwrong key \033[0m" << endl; break;
				}
				break;
				
			case 4:
				cout << endl << "choose car type: " << endl << "1 - bus car" << endl << "2 - private car" << endl;
				cin >> carType;
				switch(carType)
				{
					case 1: cout << endl << "\033[1;31mbus car -> is 1500 < 1800? -> " << (b2 < b3) << endl;
						cout << "\033[1;31mbus car -> is 1800 < 1800? -> " << (b3 < b4) << "\033[0m" << endl;
						break;
						
					case 2: cout << endl << "\033[1;31mprivate car -> is 1500 < 1800? -> " << (p2 < p3) << endl;
						cout << "\033[1;31mprivate car -> is 1500 < 1500? -> " << (p2 < p4) << "\033[0m" << endl;
						break;
					
					default : cout << endl << "\033[1;31mwrong key \033[0m" << endl; break;
				}
				break;
				
			case 5:
				cout  << endl << "choose car type: " << endl << "1 - two bus" << endl << "2 - two private" << endl << "3 - private with bus" << endl;
				cin >> carType;
				switch(carType)
				{
					case 1: cout << "\033[1;31mbus vs bus -> is == ? -> " << b1.Compare(b3) << "\033[0m" << endl; break;
						
					case 2: cout << "\033[1;31mprivate vs private -> is == ? -> " << p1.Compare(p3) << "\033[0m" << endl; break;
						
					case 3: cout << "\033[1;31mprivate vs bus -> is == ? -> " << p1.Compare(b3) << "\033[0m" << endl; break;
						
					default : cout << endl << "\033[1;31mwrong key \033[0m\n" << endl; break;
				}
				break;
				
			case 6:
				cout  << endl << "\033[1;31mbus line number -> " << b1.GetLineNum() << "\033[0m" << endl;
				break;
				
			case 7:
				cout  << endl << "\033[1;31mset new bus line number: " << endl;
				cin >> busLine;
				cout << "new bus line number -> " << b1.SetLineNum(busLine).GetLineNum() << "\033[0m" << endl;
				break;
				
			case 8:
				cout  << endl << "\033[1;31mbus number of seats -> " << b1.GetNumOfSeats() << "\033[0m" << endl;
				break;
				
			case 9:
				p1.Accelerate();
				cout << endl << "\033[1;31mprivate car accelerated \033[0m" << endl;
				break;
				
			case 10:
				p1.ReduceSpeed();
				cout << endl << "\033[1;31mprivate car reduced its speed \033[0m" << endl;
				break;
				
			case 11:
				cout << endl << "\033[1;31mprivate car speed -> " << p1.GetSpeed() << "\033[0m" << endl;
				break;

			default: 
				cont = 0;
				break;
		}
	}


	return 0;
}
