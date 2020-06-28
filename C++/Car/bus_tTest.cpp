#include <iostream>
#include "bus_t.h"

int main()
{
	int cont = 1;
	unsigned int action;
	
	while (cont) {
		cout << "Choose action: " << endl;
		cout << "1 - create a new bus " << endl;
		cout << "2 -  " << endl;
		cout << "3 -  " << endl;
		cout << "Any another number - stop " << endl;

		cin >>  action;
		switch (action) {
		
			case 1:
				
				
				break;
				
			case 2:
			
				s1.GetString();
				break;
				
			case 3:
			
				s2.Compare(s1);
				break;

			default: 
			
				cont = 0;
				break;
		}
	}


	return 0;
}
