#include "tContainer.h"
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;


int main()
{
	tContainer<int,vector<int*> > vec;
	tContainer<int,list<int*> > list;
	
	cout << "is empty? -> " << vec.IsEmpty() << endl;

	int a = 2, b = 3, c = 4;
	
	vec.InsertNemElement(&a);
	vec.InsertNemElement(&b);
	vec.InsertNemElement(&c);
	
	vec.NumOfElements();
	
	cout << "first -> " << *vec.GetFirstElement() << endl;

	cout << "last -> " << *vec.GetLastElement() << endl;

	cout << "find - > " << *vec.Find(3) << endl;
	
	cout << "remove - > " << *vec.RemoveByValue(3) << endl;
	
	cout << "find - > " << (!vec.Find(3) ? "not found" : "found" ) << endl;
	
	cout << "element at position 0 -> " << *vec[0] << endl;
	
	cout << "element at position 0 -> " << list[0] << endl;

	return 0;
}


