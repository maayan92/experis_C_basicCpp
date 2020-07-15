#include "compiler.h"

int main(int _argc, char* _argv[])
{
	int i = 1;
	compiler c;
	string fileName;
	
	while(i < _argc)
	{
		fileName = _argv[i];
		cout << "\033[4m\033[3m\033[1;38min file: '" << fileName << "':\033[0m" << endl << endl;
		c.Compilation(fileName);
		++i;
	}

	return 0;
}
