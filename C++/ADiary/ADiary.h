#ifndef __A_DIARY__
#define __A_DIARY__

#include "meeting.h"
#include "TException.h"
#include <iostream>
#include <algorithm> 
#include <map>
#include <fstream>
using namespace std;

class ADiary
{
	public:
	
	// DTOR
	
		~ADiary() { CleanAD(); }
	
	// CTOR

		ADiary() {}
		
	// mem function

		inline bool InsertNewMeeting(float _beginH, const meeting* _newMeeting);
		
		inline meeting* RemoveMeeting(float _beginH);
		
		inline const meeting* FindMeeting(float _beginH)const;
		
		inline void CleanAD();
		
		void LoadToFile(const string& _fileName);
		
		void LoadFromFile(const string& _fileName);
		
		size_t GetNumOfMeetings()const { return m_ADiary.size(); }
	
	private:
		
		map<float,meeting*> m_ADiary;
		
		typedef map<float,meeting*>::iterator mapItr;
		typedef map<float,meeting*>::const_iterator mapCItr;
		
		inline bool CheckOverLap(float _beginH, float _endH);

};

// mem functions

bool ADiary::InsertNewMeeting(float _beginH, const meeting* _newMeeting)
{
	if(!_newMeeting->IsValidMeeting())
	{
		throw TException<int>(0,__FILE__,__LINE__,"invalid meeting hours!");
	}
	
	if(!m_ADiary.empty())
	{
		if(!CheckOverLap(_beginH,_newMeeting->GetEndHour()))
		{
			throw TException<int>(0,__FILE__,__LINE__,"overLap!");
		}
	}

	return m_ADiary.insert(pair<float,meeting*>(_beginH,(meeting*)_newMeeting)).second;
}

meeting* ADiary::RemoveMeeting(float _beginH)
{
	mapItr itr = m_ADiary.find(_beginH);
	
	if(itr == m_ADiary.end()) { return 0; }
	
	meeting* remove = itr->second;
	m_ADiary.erase(itr);
	
	return remove;
}

const meeting* ADiary::FindMeeting(float _beginH)const
{
	mapCItr itr = m_ADiary.find(_beginH);
	
	return (itr == m_ADiary.end()) ? 0 : itr->second;
}

void ADiary::CleanAD()
{
	mapItr itr = m_ADiary.begin();
	meeting* remove = itr->second;
	
	while(itr != m_ADiary.end())
	{
		m_ADiary.erase(itr);
		delete remove;
		
		itr = m_ADiary.begin();
		remove = itr->second;
	}
	
}

void ADiary::LoadToFile(const string& _fileName)
{
	ofstream diaryFile;
	diaryFile.open(_fileName.c_str());
	
	if(diaryFile.fail())
	{
		throw TException<int>(0,__FILE__,__LINE__,"failed to open file!");
	}
	
	mapItr itr = m_ADiary.begin();
	
	while(itr != m_ADiary.end())
	{
		diaryFile << itr->second->GetBeginHour() << '\t' << itr->second->GetEndHour() << '\t' << itr->second->GetSubject() << endl;
		
		++itr;
	}
}

void ADiary::LoadFromFile(const string& _fileName)
{
	ifstream diaryFile;
	diaryFile.open(_fileName.c_str());
	
	if(diaryFile.fail())
	{
		throw TException<int>(0,__FILE__,__LINE__,"failed to open file!");
	}
	
	float begin, end;
	string subject;
	meeting *newMeet;
	
	while(diaryFile.peek() != EOF)
	{
		diaryFile >> begin >> end >> subject;
		newMeet = new meeting(begin,end,subject);
		
		m_ADiary.insert(pair<float,meeting*>(begin,newMeet));
	}
}

// private functions

bool ADiary::CheckOverLap(float _beginH, float _endH)
{
	mapItr upperItr = m_ADiary.upper_bound(_beginH);
		
	if(upperItr == m_ADiary.end())
	{
		return (m_ADiary.rbegin()->second->GetEndHour() > _beginH) ? false : true;
	}
		
	if(upperItr->first < _endH)
	{
		return false;
	}
	
	--upperItr;
	
	if(upperItr != m_ADiary.end() && _beginH < upperItr->second->GetEndHour())
	{
		return false;
	}
	
	return true;
}








#endif
