#ifndef __MEETING__
#define __MEETING__

#include <iostream>
#include <string>
using namespace std;

const float smallerHour = 0;
const float biggerHour = 24;

class meeting
{
	public:
				
		~meeting() {}
		inline meeting(float _beginH, float _endH, const string& _subject);
				
		inline bool IsValidMeeting()const;
			
		float GetBeginHour()const { return m_beginH; }
		
		float GetEndHour()const { return m_endH; }
		
		string GetSubject()const { return m_subject; }
		
	private:
			
		float m_beginH;
		float m_endH;
		string m_subject;
};

meeting::meeting(float _beginH, float _endH, const string& _subject)
{
	m_beginH = _beginH;
	m_endH = _endH;
	m_subject = _subject;
}

bool meeting::IsValidMeeting()const
{
	return !(m_beginH > m_endH || m_beginH < smallerHour || m_beginH > biggerHour || m_endH < smallerHour || m_endH > biggerHour);
}

ostream& operator<<(ostream& _os, const meeting& _meet)
{
	_os << "begin -> " <<  _meet.GetBeginHour() 
		<< ", end -> " << _meet.GetEndHour() 
			<< ", subject -> " << _meet.GetSubject() << endl;
			
	return _os;
}



#endif
