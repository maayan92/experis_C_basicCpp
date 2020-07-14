#include "string_t.h"
#include <iostream>

void LengthTest(const String& a_str, unsigned int a_size){
	
	static int testNum = 0;
	std::cout << "length test number " << ++testNum << ":\t\t\t"
			<< ((a_size == a_str.Length()) ? "SUCCEED" : "FAILED!") << std::endl;
}

void CopyCTORTest(const String& a_str){
	
	static int testNum = 0;
	
	try{
		String copyStr(a_str);
		std::cout << "copy CTOR test number " << ++testNum << ":\t\t"
			<< ((copyStr.Length() == a_str.Length()) ? "SUCCEED" : "FAILED!") << std::endl;
			
	}catch(const char* exception){
		std::cout << exception << std::endl;
	}
}

void OperatorAssignTest(const String& a_str, String& a_assignStr){
	
	static int testNum = 0;
	
	a_assignStr = a_str;
	
	std::cout << "assign operator test number " << ++testNum << ":\t\t" 
			<< ((a_assignStr.Length() == a_str.Length()) ? "SUCCEED" : "FAILED!") << std::endl;
}

void OperatorIsEqualTestTrue(const String& a_strFirst, const String& a_strSecond){
	
	static int testNum = 0;
	
	std::cout << "operator == equal, test number " << ++testNum << ":\t"
			<< ((a_strFirst == a_strSecond) ? "SUCCEED" : "FAILED!") << std::endl;
}

void OperatorIsEqualTestFalse(const String& a_strFirst, const String& a_strSecond){
	
	static int testNum = 0;
	
	std::cout << "operator == not equal, test number " << ++testNum << ":\t"
			<< (!(a_strFirst == a_strSecond) ? "SUCCEED" : "FAILED!") << std::endl;
}

void OperatorIsNotEqualTestTrue(const String& a_strFirst, const String& a_strSecond){
	
	static int testNum = 0;
	
	std::cout << "operator != equal, test number " << ++testNum << ":\t"
			<< ((a_strFirst != a_strSecond) ? "SUCCEED" : "FAILED!") << std::endl;
}

void OperatorIsNotEqualTestFalse(const String& a_strFirst, const String& a_strSecond){
	
	static int testNum = 0;
	
	std::cout << "operator != not equal, test number " << ++testNum << ":\t"
			<< (!(a_strFirst != a_strSecond) ? "SUCCEED" : "FAILED!") << std::endl;
}

void OperatorSubscribeTest(String& a_str){
	
	static int testNum = 0;
	a_str[0] = 'w';
	
	std::cout << "operator [], test number " << ++testNum << ":\t\t"
			<< ((a_str == "wello") ? "SUCCEED" : "FAILED!") << std::endl;
}

void OperatorConvertTest(String& a_str){
	
	static int testNum = 0;
	int result = a_str;
	
	std::cout << "operator int(), test number " << ++testNum << ":\t\t"
			<< ((result == 532) ? "SUCCEED" : "FAILED!") << std::endl;
}


int main(){
	
	try{
		String strEmpty;
		
		LengthTest(strEmpty,0);
		
		try{
			String str("hello");
			
			LengthTest(str,5);

			CopyCTORTest(str);
			
			OperatorAssignTest(str,strEmpty);
			
			OperatorIsEqualTestTrue(str,str);
			OperatorIsEqualTestFalse(str,"world");
			OperatorIsEqualTestFalse("world",str);
			OperatorIsEqualTestFalse(str,0);
			
			OperatorIsNotEqualTestFalse(str,str);
			OperatorIsNotEqualTestTrue(str,"world");
			OperatorIsNotEqualTestTrue("world",str);
			OperatorIsNotEqualTestTrue(str,0);
			
			OperatorConvertTest(str);

			OperatorSubscribeTest(str);
			
			std::cout << str;
			
		}catch(const char* exception){
			std::cout << exception << std::endl;
		}
	}catch(const char* exception){
		std::cout << exception << std::endl;
	}
	
	return 0;
}











