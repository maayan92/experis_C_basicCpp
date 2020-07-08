#include "ADiary.h"

// diary mem functions

bool ADiary::InsertNewMeeting(float _beginH, const meeting* _newMeeting)
{
	if(!_newMeeting->IsValidMeeting()) { throw "invalid meeting hours!"; }
	
	if(!m_ADiary.empty())
	{
		if(!CheckOverLap(_beginH,_newMeeting->GetEndHour())) throw "overLap!";
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








