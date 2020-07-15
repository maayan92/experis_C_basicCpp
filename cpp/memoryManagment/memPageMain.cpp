#include <cstring>
#include <iostream>
using namespace std;

#include "memManager_t.h"
#include "memPage_t.h"
#include "memPool_t.h"

void Run(memManager_t *_memory)
{
	int cont = 1, type, writeI, zeroWVal;
	unsigned int action, position, numOfBytes;;
	char writeC, read;
	
	while (cont) {
	
		cout << endl << "Choose action: " << endl;
		cout << "1 - is memory empty " << endl;
		cout << "2 - get actual size " << endl;
		cout << "3 - get current position " << endl;
		cout << "4 - set current position " << endl;
		cout << "5 - write data " << endl;
		cout << "6 - write data by position " << endl;
		cout << "7 - read data " << endl;
		cout << "8 - read data by position " << endl;
		
		cout << "Any other number - stop " << endl;
		
		numOfBytes = 0;
		read = '\0';
		writeC = '\0';

		cin >>  action;
		switch (action) {
		
			case 1:	
				cout << "\033[1;31mis empty? -> " << _memory->IsMemoryEmpty() << "\033[0m" << endl; break;
				
			case 2:	
				cout << "\033[1;31mcurrent actual size -> " << _memory->GetActualSize() << "\033[0m" << endl; break;
				
			case 3:
				cout << "\033[1;31mcurrent position -> " << _memory->GetCurrentPosition() << "\033[0m" << endl; break;
			
			case 4:
				cout << "\033[1;31mcurrent position -> " << _memory->GetCurrentPosition() << "\033[0m" << endl; break;
					
			case 5:	
				cout << "select type to insert 1-for char, any other-for int: " << endl;
				cin >> type;
				
				if(1 == type)
				{
					cout << "insert char data to write: " << endl;
					cin >> writeC;
					cout  << "\033[1;31mnumber of bytes written -> " << _memory->WriteData(&writeC,sizeof(writeC)) << endl;
					cout  << "data written -> " << writeC << "\033[0m" << endl;
				}
				else
				{
					cout << "insert int data to write: " << endl;
					cin >> writeI;
					cout  << "\033[1;31mnumber of bytes written -> " << _memory->WriteData(&writeI,sizeof(writeI)) << endl;
					cout  << "data written -> " << writeI << "\033[0m" << endl;
				}
				
				break;
				
			case 6:
				cout << "select type to insert 1-for char, any other-for int: " << endl;
				cin >> type;
				cout << "insert position: " << endl;
				cin >> position;
				
				if(1 == type)
				{
					cout << "insert char data to write: " << endl;
					cin >> writeC;
					cout  << "\033[1;31mnumber of bytes written -> " << _memory->WriteData(&writeC,sizeof(writeC),position) << endl;
					cout  << "data written -> " << writeC << "\033[0m" << endl;
				}
				else
				{
					cout << "insert int data to write: " << endl;
					cin >> writeI;
					cout  << "\033[1;31mnumber of bytes written -> " << _memory->WriteData(&writeI,sizeof(writeI),position) << endl;
					cout  << "data written -> " << writeI << "\033[0m" << endl;
				}
				
				break;
				
			case 7:
				cout << "select type to read 1-for char, any other-for int: " << endl;
				cin >> type;
				
				if(1 == type)
				{
					numOfBytes = _memory->ReadData(&read,sizeof(read));
					
					cout  << "\033[1;31mnumber of bytes read -> " << numOfBytes << endl;
					cout  << "data read -> " << read << "\033[0m" << endl;
				}
				else
				{
					numOfBytes = _memory->ReadData(&writeI,sizeof(writeI));
					cout  << "\033[1;31mnumber of bytes read -> " << numOfBytes << endl;
					cout  << "data read -> " << ((numOfBytes > 0) ? writeI : 0) << "\033[0m" << endl;
				}
				
				break;
				
			case 8:
				cout << "select type to read 1-for char, any other-for int: " << endl;
				cin >> type;
				cout << "insert position: " << endl;
				cin >> position;

				if(1 == type)
				{
					numOfBytes = _memory->ReadData(&read,sizeof(read),position);
					
					cout  << "\033[1;31mnumber of bytes read -> " << numOfBytes << endl;
					cout  << "data read -> " << read << "\033[0m" << endl;
				}
				else
				{
					numOfBytes = _memory->ReadData(&writeI,sizeof(writeI),position);
					cout  << "\033[1;31mnumber of bytes read -> " << numOfBytes << endl;
					cout  << "data read -> " << ((numOfBytes > 0) ? writeI : 0) << "\033[0m" << endl;
				}
				
				break;
			
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
	memManager_t *manager = NULL;
	
	while (cont) {
	
		cout << endl << "Choose action: " << endl;
		cout << "1 - for creating page memory " << endl;
		cout << "2 - for creating pool memory " << endl;
		
		cout << "Any other number - stop " << endl;

		cin >>  action;
		switch (action) {
		
			case 1:	
				manager = new memPage_t; break;
				
			case 2:	
				manager = new memPool_t; break;
				
			default: 
				cont = 0; break;
		}
		
		if(0 != cont)
		{
			Run(manager);
			delete manager;
		}
	}
	
	return 0;
}



