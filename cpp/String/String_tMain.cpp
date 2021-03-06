#include <cstdio>
#include <cstring>
#include <iostream>
#include "String_t.h"
using namespace std;

typedef enum
{
	SUCCEDD,
	FAILED
}Result;

// CONSTRUCTOR

Result TestString_t_Valid()
{
	String_t s;
	if('\0' != s.GetString()[0])
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

// CONSTRUCTOR WITH VAL

Result TestString_t_ValValid()
{
	const char *buffer = "hello";
	
	String_t s(buffer);
	if(0 != s.Compare(buffer))
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

Result TestString_t_NULLVal()
{
	String_t s(NULL);
	if('\0' == s.GetString()[0])
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

// COPY CONSTRUCTOR

Result TestString_t_CopyValid()
{
	const char *buffer = "hello";
	
	String_t s1(buffer);
	if(0 != s1.Compare(buffer))
	{
		return FAILED;
	}
	
	String_t s2 = s1;
	if(0 != s2.Compare(buffer))
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

Result TestString_t_CopyNULLVal()
{
	String_t s1(NULL);
	if('\0' != s1.GetString()[0])
	{
		return FAILED;
	}
	
	String_t s2 = s1;
	if('\0' != s2.GetString()[0])
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

// OPERATOR=

Result TestoperatorEqual_Valid()
{
	const char *buffer = "hello", *buffer2 = "world";
	
	String_t s1(buffer);
	String_t s2(buffer2);
	if(0 != s1.Compare(buffer) || 0 != s2.Compare(buffer2))
	{
		return FAILED;
	}
	
	s2 = s1;
	if(0 != s2.Compare(buffer))
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

Result TestoperatorEqual_SetNULL()
{
	const char *buffer = "hello";
	
	String_t s1(NULL);
	String_t s2(buffer);
	
	if('\0' != s1.GetString()[0] || 0 != s2.Compare(buffer))
	{
		return FAILED;
	}
	
	s2 = s1;
	if('\0' != s2.GetString()[0])
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

Result TestoperatorEqual_WasNULL()
{
	const char *buffer = "hello";
	
	String_t s1(buffer);
	String_t s2(NULL);
	
	if(0 != s1.Compare(buffer) || '\0' != s2.GetString()[0])
	{
		return FAILED;
	}
	
	s2 = s1;
	if(0 != s2.Compare(buffer))
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

// LENGTH

Result TestLength_ValidN()
{
	const char *buffer = "hello";
	
	String_t s(buffer);
	if(!s.GetString() || 5 != s.Length())
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

Result TestLength_Valid0()
{
	String_t s(NULL);
	
	if('\0' != s.GetString()[0] || 0 != s.Length())
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

// SET

Result TestSetString_Valid()
{
	const char *buffer1 = "hello", *buffer2 = "world";
	
	String_t s(buffer1);
	if(0 != s.Compare(buffer1))
	{
		return FAILED;
	}
	
	s.SetString(buffer2);
	if(0 != s.Compare(buffer2))
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

Result TestSetString_WasNULL()
{
	const char *buffer = "hello";
	
	String_t s;
	if('\0' != s.GetString()[0])
	{
		return FAILED;
	}
	
	s.SetString(buffer);
	if(0 != s.Compare(buffer))
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

Result TestSetString_SetNULL()
{
	const char *buffer = "hello";
	
	String_t s(buffer);
	if(0 != s.Compare(buffer))
	{
		return FAILED;
	}
	
	s.SetString(NULL);
	if('\0' != s.GetString()[0])
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

// GET

Result TestGetString_Valid()
{
	const char *buffer = "hello";
	
	String_t s(buffer);
	if(0 != s.Compare(buffer) || 0 != s.Compare(s.GetString()))
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

Result TestGetString_NULL()
{
	String_t s(NULL);
	if('\0' == s.GetString()[0])
	{
		return SUCCEDD;
	}
	
	return FAILED;
}

// COMPARE

Result TestCompare_Valid0()
{
	const char *buffer = "hello";
	
	String_t s(buffer);
	if(0 != s.Compare(buffer))
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

Result TestCompare_Valid1()
{
	const char *buffer = "hello", *buffer2 = "world";
	
	String_t s(buffer2);
	if(2 != s.Compare(buffer))
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

Result TestCompare_Valid2()
{
	const char *buffer = "hello", *buffer2 = "world";
	
	String_t s(buffer);
	if(1 != s.Compare(buffer2))
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

// LOWER

Result TestLower_Valid()
{
	const char *buffer = "HELLO";
	
	String_t s(buffer);
	if(0 != s.Lower().Compare("hello"))
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

// LOWER

Result TestUpper_Valid()
{
	const char *buffer = "hello";
	
	String_t s(buffer);
	if(0 != s.Upper().Compare("HELLO"))
	{
		return FAILED;
	}
	
	return SUCCEDD;
}

static void PrintRes(const char *_str, Result _res)
{
	static int count = 0;
	++count;
	
	printf("\n%d. %-40s \t %s \n", count, _str, (SUCCEDD == _res) ? "succedded" : "failed");
}

int main()
{	
	/*Default constructor*/
	printf("\n--- Default constructor: ---\n");
	PrintRes("TestString_t_Valid:",TestString_t_Valid());

	/*Constructor with val*/
	printf("\n--- Constructor with val: ---\n");
	PrintRes("TestString_t_ValValid:",TestString_t_ValValid());
	PrintRes("TestString_t_NULLVal:",TestString_t_NULLVal());

	/*Copy constructor*/
	printf("\n--- Copy constructor: ---\n");
	PrintRes("TestString_t_CopyValid:",TestString_t_CopyValid());
	PrintRes("TestString_t_CopyNULLVal:",TestString_t_CopyNULLVal());

	/*Operator=*/
	printf("\n--- Operator=: ---\n");
	PrintRes("TestoperatorEqual_Valid:",TestoperatorEqual_Valid());
	PrintRes("TestoperatorEqual_SetNULL:",TestoperatorEqual_SetNULL());
	PrintRes("TestoperatorEqual_WasNULL:",TestoperatorEqual_WasNULL());

	/*Length*/
	printf("\n--- Length: ---\n");
	PrintRes("TestLength_ValidN:",TestLength_ValidN());
	PrintRes("TestLength_Valid0:",TestLength_Valid0());

	/*Set string=*/
	printf("\n--- Set string: ---\n");
	PrintRes("TestSetString_Valid:",TestSetString_Valid());
	PrintRes("TestSetString_WasNULL:",TestSetString_WasNULL());
	PrintRes("TestSetString_SetNULL:",TestSetString_SetNULL());

	/*Get string*/
	printf("\n--- Get string: ---\n");
	PrintRes("TestGetString_Valid:",TestGetString_Valid());
	PrintRes("TestGetString_NULL:",TestGetString_NULL());

	/*Compare*/
	printf("\n--- Compare: ---\n");
	PrintRes("TestCompare_Valid0:",TestCompare_Valid0());
	PrintRes("TestCompare_Valid1:",TestCompare_Valid1());
	PrintRes("TestCompare_Valid2:",TestCompare_Valid2());

	/*Lower*/
	printf("\n--- Lower: ---\n");
	PrintRes("TestLower_Valid:",TestLower_Valid());

	/*Upper*/
	printf("\n--- Upper: ---\n");
	PrintRes("TestUpper_Valid:",TestUpper_Valid());


	const char *buffer1 = "hello", *buffer2 = "HeLLo";
	
	printf("\n--- Print: ---\n");
	
	/*CTOR with value*/
	String_t s1(buffer1);
	cout << "\nbuffer -> 'hello' s1 -> \n" << endl;
	s1.Print();

	String_t s2(buffer2);
	
	cout << "\nHeLLo to lower " << s2.Lower().GetString() << endl;
	
	cout << "\nhello to upper " << s1.Upper().GetString() << endl;
	
	cout << "\nprepend char HELLO with hello " << s1.Prepend(buffer2).GetString() << endl;
	
	cout << "\nprepend char HeLLoHELLO with hello " << s1.Prepend(s2).GetString() << endl;
	
	cout << "\nhello Contains el -> " << ((1 == s2.Contains("el")) ? "true" : "false") << endl;
	
	cout << "\nhello Contains ab -> " << ((1 == s2.Contains("ab")) ? "true" : "false") << endl;
	
	s1.SetString(buffer1);
	cout << "\nchar operator hello += HeLLo " << (s1 += buffer2).GetString() << endl;
	
	cout << "\nobject operator helloHeLLo += hello " << (s1 += s2).GetString() << endl;
	
	cout << "\nfind first occur of l in hello " << s2.FirstOccur('l') << endl;
	
	cout << "\nfind last occur of l in hello " << s2.LastOccur('l') << endl;

	s1.SetString(buffer2);
	cout << "\n" << s2.GetString() << " < " << s1.GetString() << "-> " << (s2 < s1) << endl;
	
	cout << "\n" << s1.GetString() << " < " << s2.GetString() << "-> " << (s1 < s2) << endl;
	
	cout << "\n" << s2.GetString() << " > " << s1.GetString() << "-> " << (s2 > s1) << endl;

	cout << "\n" << s1.GetString() << " > " << s2.GetString() << "-> " << (s1 > s2) << endl;
	
	cout << "\n" << s2.GetString() << " <= " << s1.GetString() << "-> " << (s2 <= s1) << endl;
	s1.SetString(buffer1);
	cout << "\n" << s1.GetString() << " <= " << s2.GetString() << "-> " << (s1 <= s2) << endl;
	
	cout << "\n" << s2.GetString() << " >= " << s1.GetString() << "-> " << (s2 >= s1) << endl;
	s1.SetString(NULL);
	cout << "\n" << s2.GetString() << " >= " << s1.GetString() << "-> " << (s2 >= s1) << endl;
	s1.SetString(buffer2);
	cout << "\n" << s1.GetString() << " >= " << s2.GetString() << "-> " << (s1 >= s2) << endl;
	
	String_t::SetCaseSens(false);
	cout << "\n" << s2.GetString() << " == " << s1.GetString() << "-> " << (s2 == s1) << endl;
	s1.SetString(buffer1);
	cout << "\n" << s1.GetString() << " == " << s2.GetString() << "-> " << (s1 == s2) << endl;
	
	cout << "\n" << s2.GetString() << " != " << s1.GetString() << "-> " << (s2 != s1) << endl;
	s1.SetString(buffer2);
	cout << "\n" << s1.GetString() << " != " << s2.GetString() << "-> " << (s1 != s2) << endl;

	const String_t s3;
	cout << "\nindex 3 in const empty -> " << s3[3] << endl;
	const String_t s4(buffer1);
	cout << "\nindex 1 in const " << s4.GetString() << " -> " << s4[1] << endl;
	
	cout << "\nset index 3 in not const to 'c' -> befor -> " << s2.GetString();
	
	s2[3] = 'c';
	cout << " after -> " << s2.GetString() << endl;

	cout << "\nset index 7 in not const to 'c' -> befor -> " << s2.GetString();
	
	s2[7] = 'c';
	cout << " after -> " << s2.GetString() << endl;
	
	s2.SetString("prepend char HeLLoHELLO with hello");
	cout << s2 << endl;
	
	cout << "sub string from position 7 with len 7 -> " << s1 << " -> " << s1(7,7) << endl;
	
	cout << "sub string from position 3 with len 2 -> " << s1 << " -> " << s1(3,2) << endl;
	
	cout << "sub string from position 3 with len 6 -> " << s1 << " -> " << s1(3,6) << endl;
	
	cout << "num of strings -> " << String_t::GetNumOfStrings() << endl;
	
	cin >> s1;
	

	return 0;
}







