#include "TException.h"

void foo(int _num)
{
	
	throw TException<int>(_num,__FILE__,__LINE__,"int exception!");
	
}

int main()
{
	int num = 5;
	 
	try
	{
		foo(num);
	}
	catch(TException<int>& exc)	
	{
		cout << "exception -> " << exc.GetException() << endl;
		cout << "message -> " << exc.GetExcMessage() << endl;
		cout << "file name -> " << exc.GetFileName() << endl;
		cout << "line number -> " << exc.GetLineNumber() << endl;
	}


	return 0;
}

