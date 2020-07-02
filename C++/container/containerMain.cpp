#include "container.h"
#include "array.h"

#include <iostream>
using namespace std;

int main()
{
	array<int> arr(1,5);

	int a = 8, b = 10, c = 2, d = 1;
	
	try{
		arr.Insert(&a);
	}
	catch(const char* exc){
		cout << exc << endl;
	}
	
	try{
		arr.Append(&b,3);
	}
	catch(const char* exc){
		cout << "append index 3 -> " << exc << endl;
	}
	
	try{
		arr.Append(&c,0);
	}
	catch(const char* exc){
		cout << "append index 0 -> " << exc << endl;
	}
	
	try{
		arr.Prepend(&d,2);
	}
	catch(const char* exc){
		cout << "prepend index 3 -> " << exc << endl;
	}
	
	
	cout << arr.Contains(&a) << endl;
	cout << arr.Contains(&b) << endl;
	
	cout << "index of 8 -> " << arr.Index(&a) << endl;
	cout << "index of 1 -> " << arr.Index(&d) << endl;
	cout << "index of 2 -> " << arr.Index(&c) << endl;
	
	const int* val = arr.Find(2);
	
	(NULL != val) ? cout << *val : cout;
	cout << endl;
	
	
	
	
	return 0;
}
