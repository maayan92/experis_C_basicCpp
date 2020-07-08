#include "ADiary.h"
#include "meeting.h"


int main()
{
	meeting* newMeeting = new meeting(8.0,9.0,"meet1");
	meeting* newMeeting2 = new meeting(10.0,11.0,"meet2");
	meeting* newMeeting3 = new meeting(8.5,9.5,"meet3");
	meeting* newMeeting4 = new meeting(9.0,10.0,"meet4");
	
	ADiary ad;

	try
	{
		ad.InsertNewMeeting(8.0,newMeeting);
	}
	catch(TException<int> exc)
	{
		cout << "message -> " << exc.GetExcMessage() << endl;
		cout << "file name -> " << exc.GetFileName() << endl;
		cout << "line number -> " << exc.GetLineNumber() << endl;
	}
	
	try
	{
		ad.InsertNewMeeting(10.0,newMeeting2);
	}
	catch(TException<int> exc)
	{
		cout << "message -> " << exc.GetExcMessage() << endl;
		cout << "file name -> " << exc.GetFileName() << endl;
		cout << "line number -> " << exc.GetLineNumber() << endl;
	}
	
	try
	{
		ad.InsertNewMeeting(8.5,newMeeting3);
	}
	catch(TException<int> exc)
	{
		cout << "message -> " << exc.GetExcMessage() << endl;
		cout << "file name -> " << exc.GetFileName() << endl;
		cout << "line number -> " << exc.GetLineNumber() << endl;
	}

	try
	{
		ad.InsertNewMeeting(9.5,newMeeting4);
	}
	catch(TException<int> exc)
	{
		cout << "message -> " << exc.GetExcMessage() << endl;
		cout << "file name -> " << exc.GetFileName() << endl;
		cout << "line number -> " << exc.GetLineNumber() << endl;
	}

	cout << "find -> " << ((meeting)(*ad.FindMeeting(8.0))) << endl;
	
	try
	{
		ad.LoadToFile("adiary.txt");
	}
	catch(TException<int> exc)
	{
		cout << "message -> " << exc.GetExcMessage() << endl;
		cout << "file name -> " << exc.GetFileName() << endl;
		cout << "line number -> " << exc.GetLineNumber() << endl;
	}
	
	ad.CleanAD();
	
	meeting *m = (meeting*)(ad.FindMeeting(8.0));
	meeting *m2 = (meeting*)(ad.FindMeeting(10.0));
	meeting *m3 = (meeting*)(ad.FindMeeting(9.0));
	
	cout << "find 8 -> " << (!m ? "not found!" : "found!") << endl;
	cout << "find 10 -> " << (!m2 ? "not found!" : "found!") << endl;
	cout << "find 9 -> " << (!m3 ? "not found!" : "found!") << endl;
	
	try
	{
		ad.LoadFromFile("adiary.txt");
	}
	catch(TException<int> exc)
	{
		cout << "message -> " << exc.GetExcMessage() << endl;
		cout << "file name -> " << exc.GetFileName() << endl;
		cout << "line number -> " << exc.GetLineNumber() << endl;
	}
	
	m = (meeting*)(ad.FindMeeting(8.0));
	m2 = (meeting*)(ad.FindMeeting(10.0));
	m3 = (meeting*)(ad.FindMeeting(9.0));
	
	cout << "find 8 -> " << (!m ? "not found!" : "found!") << endl;
	cout << "find 10 -> " << (!m2 ? "not found!" : "found!") << endl;
	cout << "find 9 -> " << (!m3 ? "not found!" : "found!") << endl;
	
	cout << "number of meetinngs -> " << ad.GetNumOfMeetings() << endl;
	
	delete newMeeting3;
	

	return 0;
}
