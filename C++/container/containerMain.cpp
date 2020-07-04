#include "container.h"
#include "array.h"
#include "dList.h"

#include <iostream>
using namespace std;

const int size = 200;

void Run(container<int> *_contain)
{
	int cont = 1, data[size], i = 0, dataRF, *val;
	unsigned int action, position;
	bool res;
	
	while (cont) {
	
		cout << endl << "Choose action: " << endl;
		cout << "1 - Insert new element " << endl;
		cout << "2 - Append new element " << endl;
		cout << "3 - Prepend new element " << endl;
		cout << "4 - Find data " << endl;
		cout << "5 - Remove data " << endl;
		cout << "6 - Get number of elements " << endl;
		cout << "7 - Is container empty " << endl;
		
		cout << "Any other number - stop " << endl;
		
		cin >>  action;
		switch (action) {
		
			case 1:	
				cout << "\033[1;31mif the insert fails an exception will occur\033[0m" << endl;
				
				cout << "Insert data: " << endl;
				cin >> data[i];
				
				try{
					res = _contain->Insert(&data[i]);
				}
				catch(const char* exc){
					cout << "\033[0;32m" << exc << "\033[0m" << endl;
				}
				
				++i;
				
				break;
				
			case 2:	
				cout << "\033[1;31mif the append fails an exception will occur\033[0m" << endl;
				
				cout << "Insert data: " << endl;
				cin >> data[i];
				cout << "Insert position: " << endl;
				cin >> position;
				
				try{
					res = _contain->Append(&data[i],position);
				}
				catch(const char* exc){
					cout << "\033[0;32m" << exc << "\033[0m" << endl;
				}
				
				++i;
			
				break;
				
			case 3:
				cout << "\033[1;31mif the prepend fails an exception will occur\033[0m" << endl;

				cout << "Insert data: " << endl;
				cin >> data[i];
				cout << "Insert position: " << endl;
				cin >> position;
				
				try{
					res = _contain->Prepend(&data[i],position);
				}
				catch(const char* exc){
					cout << "\033[0;32m" << exc << "\033[0m" << endl;
				}
				
				++i;
			
				break;
			
			case 4:
				cout << "Insert data to find: " << endl;
				cin >> dataRF;
			
				val = (int*)_contain->Find(dataRF);
				
				cout << "\033[1;31m" << ((NULL != val) ? "data found!" : "data not found!") << "\033[0m" << endl;
				
				break;
					
			case 5:	
				cout << "Insert data to remove: " << endl;
				cin >> dataRF;
			
				cout << "\033[1;31m" << ((_contain->Remove(dataRF)) ? "data removed!" : "data not found!") << "\033[0m" << endl;
				
				break;
				
			case 6:
				cout << "\033[1;31mnumber of elements -> " << _contain->Count() << "\033[0m" << endl; break;
				
			case 7:
				cout << "\033[1;31mis empty? -> " << (_contain->IsEmpty() ? "true" : "false") << "\033[0m" << endl; break;
				
			default: 
				cont = 0;
				break;
		}
	}
}

int main()
{
	int cont = 1;
	unsigned int action;
	container<int> *contain = NULL;
	
	while (cont) {
	
		cout << endl << "Choose action: " << endl;
		cout << "1 - for creating array container " << endl;
		cout << "2 - for creating double list container " << endl;
		
		cout << "Any other number - stop " << endl;

		cin >>  action;
		switch (action) {
		
			case 1:	
				contain = new array<int>; break;
				
			case 2:	
				contain = new dList<int>; break;
				
			default: 
				cont = 0; break;
		}
		
		if(0 != cont)
		{
			Run(contain); 
			delete contain;
		}
		
	}
	
	return 0;
}
