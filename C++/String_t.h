#ifndef __STRING_T_H__
#define __STRING_T_H__

class String_t
{
	public:
		
		/*
			Description: destructor.
		*/
		~String_t();
		/*
			Description: default constructor.
		*/
		String_t();
		/*
			Description: constructor, create the object with initialization.
			Input: _str - the initial value of buffer.
		*/
		String_t(const char* _str);
		/*
			Description: copy constructor.
			Input: _s - the object to copy.
		*/
		String_t(const String_t& _s);
		/*
			Description: copy all _s members to this mambers.
			Input: _s - the object to copy.
		*/
		String_t& operator=(String_t& _s);
		/*
			Description: get the length of buffer.
		*/
		size_t Length()const;
		/*
			Description: set the buffer to _str.
			Input: _str - the new value to buffer.
		*/
		void SetString(const char* _str);
		/*
			Description: get the buffer.
		*/
		const char* GetString()const;
		/*
			Description: compare the string _str to the object buffer. 
		*/
		int Compare(const char* _str)const;
		/*
			Description: print the buffer.
		*/
		void Print()const;
		
	private:
	
		char *buffer;
		
		char* CreateFrom(const char *_str);
};




#endif
