#include "container.h"
#include "array.h"
#include "dList.h"

#include <iostream>
using namespace std;

int main()
{
	array<int> arr(1,5);
	array<int> arr2(arr);
	array<int> arr3;
	
	int a = 8, b = 10, c = 2, d = 1;
	
	try{
		arr.Insert(&a);
	}
	catch(const char* exc){
		cout << exc << endl;
	}
	try{
		arr2.Insert(&c);
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
	
	arr3 = arr;
	
	arr.Remove(8);
	
	cout << "index of 8 -> " << arr.Index(&a) << endl;
	cout << "index of 1 -> " << arr.Index(&d) << endl;
	cout << "index of 2 -> " << arr.Index(&c) << endl;
	
	cout << "number of elements -> " << arr.Count() << endl;
	cout << "is empty? -> " << arr.IsEmpty() << endl;
	
	arr.RemoveAll();
	
	cout << "index of 1 -> " << arr.Index(&d) << endl;
	cout << "index of 2 -> " << arr.Index(&c) << endl;
	
	cout << "number of elements -> " << arr.Count() << endl;
	cout << "is empty? -> " << arr.IsEmpty() << endl;
	
	cout << endl << "copy CTOR: " << endl;
	
	cout << "index of 8 -> " << arr2.Index(&a) << endl;
	cout << "index of 1 -> " << arr2.Index(&d) << endl;
	cout << "index of 2 -> " << arr2.Index(&c) << endl;
	
	cout << "number of elements -> " << arr2.Count() << endl;
	cout << "is empty? -> " << arr2.IsEmpty() << endl;
	
	cout << endl << "operator=: " << endl;
	
	cout << "index of 8 -> " << arr3.Index(&a) << endl;
	cout << "index of 1 -> " << arr3.Index(&d) << endl;
	cout << "index of 2 -> " << arr3.Index(&c) << endl;
	
	cout << "number of elements -> " << arr3.Count() << endl;
	cout << "is empty? -> " << arr3.IsEmpty() << endl;
	
	
	cout << endl << "list:" << endl;
	dList<int> list;
	
	try{
		list.Insert(&a);
	}
	catch(const char* exc){
		cout << exc << endl;
	}
	
	try{
		list.Insert(&b);
	}
	catch(const char* exc){
		cout << exc << endl;
	}
	
	try{
		list.Append(&c,0);
	}
	catch(const char* exc){
		cout << exc << endl;
	}
	
	try{
		list.Prepend(&d,1);
	}
	catch(const char* exc){
		cout << exc << endl;
	}
	
	cout << list.Contains(&c) << endl;
	
	cout << "number of elements -> " << list.Count() << endl;
	cout << "is empty? -> " << list.IsEmpty() << endl;
	
	const int* valL = list.Find(8);
	
	(NULL != valL) ? cout << *valL : cout;
	cout << endl;
	
	cout << "index of 1 -> " << list.Index(&d) << endl;
	cout << "index of 8 -> " << list.Index(&a) << endl;
	cout << "index of 2 -> " << list.Index(&c) << endl;
	cout << "index of 10 -> " << list.Index(&b) << endl;

	list.Remove(2);
	
	cout << "index of 1 -> " << list.Index(&d) << endl;
	cout << "index of 8 -> " << list.Index(&a) << endl;
	cout << "index of 2 -> " << list.Index(&c) << endl;
	cout << "index of 10 -> " << list.Index(&b) << endl;
	
	list.RemoveAll();
	
	cout << "index of 1 -> " << list.Index(&d) << endl;
	cout << "index of 8 -> " << list.Index(&a) << endl;
	cout << "index of 2 -> " << list.Index(&c) << endl;
	cout << "index of 10 -> " << list.Index(&b) << endl;
	
	
	
	return 0;
}
