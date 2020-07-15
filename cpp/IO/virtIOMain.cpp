#include "virtIO.h"
#include "asciiIO.h"
#include "binIO.h"
#include "TException.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

void ChooseMode(String_t& _mode)
{
	int m;
	
	cout << endl << "Choose mode: " << endl;
	cout << "1 - (r) Read only, the file must exist" << endl;
	cout << "2 - (w) Write only, overrides the file if it doesn't exist" << endl;
	cout << "3 - (a) Append to the end of the file only, the file if created if it doesn't exist " << endl;
	cout << "4 - (r+) Read and write, the file must exist " << endl;
	cout << "5 - (w+) Read and write, overrides the file if it doesn't exist " << endl;
	cout << "6 - (a+) Read and write, the file if created if it doesn't exist " << endl;
	cin >> m;
	
	switch(m)
	{
		case 1: _mode.SetString("r"); break;
		case 2: _mode.SetString("w"); break;
		case 3: _mode.SetString("a"); break;
		case 4: _mode.SetString("r+"); break;
		case 5: _mode.SetString("w+"); break;
		default: _mode.SetString("a+"); break;
	}
}

void ChooseFileName(String_t& _fileName)
{
	cout << "Insert file name: " << endl;
	cin >> _fileName;
}

template<class T>
void ReadTryCatch(virtIO &_io)
{
	T data;
	int succeed = 1;
	
	try
	{
		_io >> data;
	}
	catch(TException<virtIO::status> exc)
	{
		cout << "\033[1;32mexception -> " << exc.GetException() << endl;
		cout << "message -> " << exc.GetExcMessage() << endl;
		cout << "file name -> " << exc.GetFileName() << endl;
		cout << "line number -> " << exc.GetLineNumber() << "\033[0m" << endl;
		succeed = 0;
	}
	
	if(succeed) cout << "\033[1;31m" << data << "\033[0m" << endl;
}

template<class T>
void WriteTryCatch(virtIO &_io)
{
	T data;
	
	cout << "Insert data to write: " << endl;
	cin >> data;
	if(!cin.good()) { cout << "\033[1;31mwrong input type!\033[0m" << endl; return; }
	
	try
	{
		_io << data << ' ';
	}
	catch(TException<virtIO::status> exc)
	{
		cout << "\033[1;32mexception -> " << exc.GetException() << endl;
		cout << "message -> " << exc.GetExcMessage() << endl;
		cout << "file name -> " << exc.GetFileName() << endl;
		cout << "line number -> " << exc.GetLineNumber() << "\033[0m" << endl;
	}
	
	cout << "\033[1;31m" << data << "\033[0m" << endl;
}

void Write(virtIO *_io)
{
	int type;
	
	cout << endl << "Choose data type: " << endl;
	cout << "1 - int" << endl;
	cout << "2 - float " << endl;
	cout << "3 - char " << endl;
	cout << "4 - short " << endl;
	cout << "5 - long " << endl;
	cout << "6 - double " << endl;
	cout << "7 - unsigned int " << endl;
	cout << "8 - unsigned char " << endl;
	cout << "9 - unsigned short " << endl;
	cout << "10 - unsigned long " << endl;
	cin >> type;
		
	switch(type)
	{
		case 1: WriteTryCatch<int>(*_io); break;
		case 2: WriteTryCatch<float>(*_io); break;
		case 3: WriteTryCatch<char>(*_io); break;
		case 4: WriteTryCatch<short>(*_io); break;
		case 5: WriteTryCatch<long>(*_io); break;
		case 6: WriteTryCatch<double>(*_io); break;
		case 7: WriteTryCatch<unsigned int>(*_io); break;
		case 8: WriteTryCatch<unsigned char>(*_io); break;
		case 9: WriteTryCatch<unsigned short>(*_io); break;
		case 10: WriteTryCatch<unsigned long>(*_io); break;
	}
}

void Read(virtIO *_io)
{
	int type;
	
	cout << endl << "Choose data type: " << endl;
	cout << "1 - int" << endl;
	cout << "2 - float " << endl;
	cout << "3 - char " << endl;
	cout << "4 - short " << endl;
	cout << "5 - long " << endl;
	cout << "6 - double " << endl;
	cout << "7 - unsigned int " << endl;
	cout << "8 - unsigned char " << endl;
	cout << "9 - unsigned short " << endl;
	cout << "10 - unsigned long " << endl;
	cin >> type;
		
	switch(type)
	{
		case 1: ReadTryCatch<int>(*_io); break;
		case 2: ReadTryCatch<float>(*_io); break;
		case 3: ReadTryCatch<char>(*_io); break;
		case 4: ReadTryCatch<short>(*_io); break;
		case 5: ReadTryCatch<long>(*_io); break;
		case 6: ReadTryCatch<double>(*_io); break;
		case 7: ReadTryCatch<unsigned int>(*_io); break;
		case 8: ReadTryCatch<unsigned char>(*_io); break;
		case 9: ReadTryCatch<unsigned short>(*_io); break;
		case 10: ReadTryCatch<unsigned long>(*_io); break;
	}
}

void WriteReadVoid(virtIO *_io)
{
	int cont;
	int buf;
	
	binIO* bin = dynamic_cast<binIO*>(_io);
	if(0 != bin)
	{
		cout << endl << "Choose data type: " << endl;
		cout << "1 - Write" << endl;
		cout << "2 - Read " << endl;
		cin >> cont;
		
		if(1 == cont)
		{
			try
			{
				cout << "Insert int data to write: " << endl;
				cin >> buf;
				
				*bin << &buf,sizeof(int);
			}
			catch(TException<virtIO::status> exc)
			{
				cout << "\033[1;32mexception -> " << exc.GetException() << endl;
				cout << "message -> " << exc.GetExcMessage() << endl;
				cout << "file name -> " << exc.GetFileName() << endl;
				cout << "line number -> " << exc.GetLineNumber() << "\033[0m" << endl;
			}
		}
		else if(2 == cont)
		{
			try
			{
				*bin >> &buf,sizeof(int);
			}
			catch(TException<virtIO::status> exc)
			{
				cout << "\033[1;32mexception -> " << exc.GetException() << endl;
				cout << "message -> " << exc.GetExcMessage() << endl;
				cout << "file name -> " << exc.GetFileName() << endl;
				cout << "line number -> " << exc.GetLineNumber() << "\033[0m" << endl;
			}
			
			cout << "\033[1;31m" << buf << "\033[0m" << endl;
		}
	}
}

void Run(virtIO *_io)
{
	int cont = 1;
	long int position;
	unsigned int action;
	String_t mode, fileName;
	
	while (cont) {
	
		cout << endl << "Choose action: " << endl;
		cout << "1 - Write" << endl;
		cout << "2 - Read " << endl;
		cout << "3 - Get position " << endl;
		cout << "4 - Set position " << endl;
		cout << "5 - Get file length " << endl;
		cout << "6 - Get file name " << endl;
		cout << "7 - Get file mode " << endl;
		cout << "8 - Get status " << endl;
		cout << "9 - Open file " << endl;
		cout << "10 - Close file " << endl;
		cout << "11 - Read/Write void pointer " << endl;
		
		cout << "Any other number - stop " << endl;

		cin >>  action;
		
		system("clear");
		cout << endl << endl;
		
		switch (action) {
		
			case 1:	system("clear"); Write(_io); break;
				
			case 2:	system("clear"); Read(_io); break;
				
			case 3: cout << "\033[1;31mposition -> " << _io->GetPosition() << "\033[0m" << endl; break;
			
			case 4: cout << "Insert position: " << endl;
				cin >> position;
				
				cout << "\033[1;31mposition set " << (_io->SetPosition(position) ? "successfully!" : "failed!") << "\033[0m" << endl;
				break;
					
			case 5:	cout << "\033[1;31mlength -> " << _io->GetFileLength() << "\033[0m" << endl; break;
				
			case 6: cout << "\033[1;31mfile name -> " << _io->GetFileName() << "\033[0m" << endl; break;
				
			case 7: cout << "\033[1;31mfile mode -> " << _io->GetFileMode() << "\033[0m" << endl; break;
			
			case 8: cout << "\033[1;31mstatus -> " << _io->GetStatus() << "\033[0m" << endl; break;
			
			case 9: ChooseMode(mode); ChooseFileName(fileName);
			
				cout << "open file " << (_io->Open(fileName,mode) ? "succeeded!" : "failed!") << endl;
			
			case 10: _io->CloseFile();
			
				cout << "close file " << (_io->GetFileLength() ? "succeeded!" : "failed!") << endl;
				
			case 11: WriteReadVoid(_io); break;
			
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
	virtIO *io = NULL;
	String_t mode, fileName;
	
	while (cont) {
	
		cout << endl << "Choose action: " << endl;
		cout << "1 - for creating ascii file " << endl;
		cout << "2 - for creating bin file " << endl;
		cout << "Any other number - stop " << endl;
		cin >>  action;
		
		system("clear");
		
		switch (action) {
		
			case 1: ChooseMode(mode);
				ChooseFileName(fileName);
				io = new asciiIO(fileName,mode); 
				system("clear");
				cout << endl << "\033[1;31m------------ Ascii file ------------\033[0m" << endl;
				break;
				
			case 2:	ChooseMode(mode);
				ChooseFileName(fileName);
				io = new binIO(fileName,mode); 
				system("clear");
				cout << endl << "\033[1;31m------------ Binary file ------------\033[0m" << endl;
				break;
				
			default: 
				cont = 0; break;
		}
		
		if(0 != cont) { Run(io); delete io; }
	}
	
	return 0;
}




