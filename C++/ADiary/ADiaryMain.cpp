#include "ADiary.h"
#include "meeting.h"


const int size = 200;

int main()
{
	int cont = 1,i = 0, action;
	meeting* meetings[size];
	float begin, end;
	string subject, fileName = "ADiary.txt";
	ADiary ad;
	
	ad.LoadFromFile(fileName);
	system("clear");
	
	cout << endl << "\033[1;34m-------- Appointment Diary --------\033[0m" << endl;

	while (cont) {
	
		cout << endl << "Choose action: " << endl;
		cout << "1 - Insert new meeting " << endl;
		cout << "2 - Remove meeting " << endl;
		cout << "3 - Find meeting " << endl;
		cout << "4 - Get number of meetings " << endl;
		cout << "5 - Clean appointment diary " << endl;
		
		cout << "Any other number - stop " << endl;
		
		cin >>  action;
		
		system("clear");
		cout << endl << "\033[1;34m-------- Appointment Diary --------\033[0m" << endl;
		
		switch (action) {
		
			case 1:	
				cout << endl << "\033[1;33mif the insert fails an exception will occur\033[0m" << endl;
				
				cout << "Insert begin hour: " << endl;
				cin >> begin;
				cout << "Insert end hour: " << endl;
				cin >> end;
				cout << "Insert meeting subject: " << endl;
				cin >> subject;
				
				meetings[i] = new meeting(begin,end,subject);
				
				try{
					ad.InsertNewMeeting(begin,meetings[i]);
				}
				catch(TException<int>& exc){
					cout << "\033[1;32m" << exc.GetExcMessage() << endl;
					cout << "at file -> " << exc.GetFileName() << endl;
					cout << "at line -> " << exc.GetLineNumber() << "\033[0m" << endl;
				}
				
				++i;
				
				break;
				
			case 2:	
				cout << endl << "Insert begin hour: " << endl;
				cin >> begin;
				
				if(ad.RemoveMeeting(begin))
				{
					cout << "\033[1;31mmeeting removed!\033[0m" << endl;
					break;
				}
				
				cout << "\033[1;32mmeeting not found!\033[0m" << endl;
		
				break;
				
			case 3:
				cout << endl << "Insert begin hour: " << endl;
				cin >> begin;
				
				if(ad.FindMeeting(begin))
				{
					cout << "\033[1;31mmeeting found!\033[0m" << endl;
					break;
				}
				
				cout << "\033[1;32mmeeting not found!\033[0m" << endl;
		
				break;
			
			case 4:
				cout << endl << "\033[1;31mnumber of meetings -> " << ad.GetNumOfMeetings() << "\033[0m" << endl; break;
					
			case 5:
				ad.CleanAD();
				
				cout << endl << "\033[1;31m" << (!ad.GetNumOfMeetings() ? "diary cleaning succeeded" : "diary cleaning failed") << "\033[0m" << endl;
				
				break;
				
			default: 
				cont = 0;
				break;
		}
	}
	
	try
	{
		ad.SaveToFile(fileName);
	}
	catch(TException<int> exc)
	{
		cout << "\033[1;32m" << exc.GetExcMessage() << endl;
		cout << "at file -> " << exc.GetFileName() << endl;
		cout << "at line -> " << exc.GetLineNumber() << "\033[0m" << endl;
	}
	
	return 0;
}
