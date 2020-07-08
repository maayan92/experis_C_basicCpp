#include "tContainer.h"
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

const int size = 200;

int ChooseAction()
{
	int action;
	
	cout << endl << "Choose action: " << endl;
	cout << "1 - Insert new element " << endl;
	cout << "2 - Get first element " << endl;
	cout << "3 - Get last element " << endl;
	cout << "4 - Get element by position " << endl;
	cout << "5 - Find element " << endl;
	cout << "6 - Get number of elements " << endl;
	cout << "7 - Is container empty " << endl;
	cout << "8 - Remove data " << endl;
	cout << "9 - Remove all " << endl;
		
	cout << "Any other number - stop " << endl;
	
	cin >>  action;
	return action;
}

void RunVec(tContainer<int,vector<int*> >& _vec)
{
	int cont = 1, data[size], i = 0, dataRF;
	const int *val;
	unsigned int action, position;
	bool res;
	
	while (cont) {
	
		action = ChooseAction();
		switch (action) {
		
			case 1:	
				cout << "\033[1;31mif the insert fails an exception will occur\033[0m" << endl;
				
				cout << "Insert data: " << endl;
				cin >> data[i];
				
				try{
					_vec.InsertNemElement(&data[i]);
				}
				catch(...){
					cout << "\033[1;32minsert failed!\033[0m" << endl;
				}
				
				++i;
				
				break;
				
			case 2:	
				val = _vec.GetFirstElement();
				if(!val)
				{
					cout << "\033[1;32mno elements!\033[0m" << endl; break;
				}
				
				cout << "\033[1;31mfirst element -> " << *val << "\033[0m" << endl; break;
				
			case 3:
				val = _vec.GetLastElement();
				if(!val)
				{
					cout << "\033[1;32mno elements!\033[0m" << endl; break;
				}
				
				cout << "\033[1;31mlast element -> " << *val << "\033[0m" << endl; break;
			
			case 4:
				cout << "Insert position: " << endl;
				cin >> position;
				
				val = _vec[position];
				if(!val)
				{
					cout << "\033[1;32mwrong position!\033[0m" << endl; break;
				}
				
				cout << "\033[1;31melement at position " << position << " -> " << *val << "\033[0m" << endl; break;
			
			case 5:
				cout << "Insert data to find: " << endl;
				cin >> dataRF;
			
				cout << "\033[1;31m" << ((_vec.Find(dataRF)) ? "data found!" : "data not found!") << "\033[0m" << endl;
				
				break;
			
			case 6:
				cout << "\033[1;31mnumber of elements -> " << _vec.NumOfElements() << "\033[0m" << endl; break;
					
			case 7:	
				cout << "\033[1;31mis empty? -> " << (_vec.IsEmpty() ? "true" : "false") << "\033[0m" << endl; break;
				
			case 8:
				cout << "Insert data to remove: " << endl;
				cin >> dataRF;
			
				cout << "\033[1;31m" << ((_vec.RemoveByValue(dataRF)) ? "data removed!" : "data not found!") << "\033[0m" << endl;
				
				break;
				
			case 9:
				_vec.RemoveAll();
				cout << "\033[1;31mall elements removed!\033[0m" << endl; break;
				
			default: 
				cont = 0;
				break;
		}
	}
}

void RunList(tContainer<int,list<int*> >& _list)
{
	int cont = 1, data[size], i = 0, dataRF;
	const int *val;
	unsigned int action, position;
	bool res;
	
	while (cont) {
	
		action = ChooseAction();
		switch (action) {
		
			case 1:	
				cout << "\033[1;31mif the insert fails an exception will occur\033[0m" << endl;
				
				cout << "Insert data: " << endl;
				cin >> data[i];
				
				try{
					_list.InsertNemElement(&data[i]);
				}
				catch(...){
					cout << "\033[1;32minsert failed!\033[0m" << endl;
				}
				
				++i;
				
				break;
				
			case 2:	
				val = _list.GetFirstElement();
				if(!val)
				{
					cout << "\033[1;32mno elements!\033[0m" << endl; break;
				}
				
				cout << "\033[1;31mfirst element -> " << *val << "\033[0m" << endl; break;
				
			case 3:
				val = _list.GetLastElement();
				if(!val)
				{
					cout << "\033[1;32mno elements!\033[0m" << endl; break;
				}
				
				cout << "\033[1;31mlast element -> " << *val << "\033[0m" << endl; break;
			
			case 4:
				cout << "Insert position: " << endl;
				cin >> position;
				
				val = _list[position];
				if(!val)
				{
					cout << "\033[1;32mwrong position!\033[0m" << endl; break;
				}
				
				cout << "\033[1;31melement at position " << position << " -> " << *val << "\033[0m" << endl; break;
			
			case 5:
				cout << "Insert data to find: " << endl;
				cin >> dataRF;
			
				cout << "\033[1;31m" << ((_list.Find(dataRF)) ? "data found!" : "data not found!") << "\033[0m" << endl;
				
				break;
			
			case 6:
				cout << "\033[1;31mnumber of elements -> " << _list.NumOfElements() << "\033[0m" << endl; break;
					
			case 7:	
				cout << "\033[1;31mis empty? -> " << (_list.IsEmpty() ? "true" : "false") << "\033[0m" << endl; break;
				
			case 8:
				cout << "Insert data to remove: " << endl;
				cin >> dataRF;
			
				cout << "\033[1;31m" << ((_list.RemoveByValue(dataRF)) ? "data removed!" : "data not found!") << "\033[0m" << endl;
				
				break;
				
			case 9:
				_list.RemoveAll();
				cout << "\033[1;31mall elements removed!\033[0m" << endl; break;
				
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
	
	while (cont) {
	
		cout << endl << "Choose action: " << endl;
		cout << "1 - for creating vector container " << endl;
		cout << "2 - for creating double list container " << endl;
		
		cout << "Any other number - stop " << endl;

		cin >>  action;
		switch (action) {
		
			case 1:	
			{
				tContainer<int,vector<int*> > vec;
				RunVec(vec); break;
			}
				
			case 2: 
			{
				tContainer<int,list<int*> > list;
				RunList(list); break;
			}
				
			default: 
				cont = 0; break;
		}
		
	}

	return 0;
}


