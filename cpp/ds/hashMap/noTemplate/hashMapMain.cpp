#include "hashMap.h"

static size_t StrHash(const std::string &a_str) {

	int i, sum = 0;
	for(i = 0 ; i < a_str.length() ; ++i) {
		sum += a_str[i]; 
	}
	
	return sum;
}

static bool Compare(const std::string &a_left, const std::string &a_right) {

	return a_left == a_right;
}

static void CTORTest(const HashMap& a_hash) {

	static int testNumber = 0;
	std::cout << "CTOR with default capacity, test " << ++testNumber <<  ":\t\033[1;31m" 
	                << ((16 == a_hash.size()) ? "SUCCEEDED" : "FAILED") << "\033[0m" << std::endl;
}

static void CTORCapacityTest(const HashMap& a_hash, unsigned int a_capacity) {

	static int testNumber = 0;
	std::cout << "CTOR with capacity, test " << ++testNumber << ":\t\t\033[1;31m" 
	                << ((a_capacity == a_hash.size()) ? "SUCCEEDED" : "FAILED") << "\033[0m" << std::endl;
}

static void CopyCTORTest(const HashMap& a_hash) {

	static int testNumber = 0;
	HashMap copyHash(a_hash);
	std::cout << "copy CTOR, test " << ++testNumber << ":\t\t\t\033[1;31m" 
	                << ((copyHash.size() == a_hash.size()) ? "SUCCEEDED" : "FAILED") << "\033[0m" << std::endl;
}

static void PutTest(HashMap& a_hash, const std::string& a_key, const std::string& a_value, bool a_validKey) {

	static int testNumber = 0;
	bool result = (a_validKey == a_hash.Put(a_key,a_value));
	result = a_hash.Has(a_key);
	std::cout << "put pair, test " << ++testNumber << ":\t\t\t\033[1;31m" << (result ? "SUCCEEDED" : "FAILED") << "\033[0m" << std::endl;
}

static void RemoveTest(HashMap& a_hash, const std::string& a_key, bool a_IsKeyExist) {

	static int testNumber = 0;
	std::cout << "remove pair, test " << ++testNumber << ":\t\t\t\033[1;31m";
	
	try {
	        a_hash.Remove(a_key);
	} catch(const char* exception) {
	        if(!a_IsKeyExist) { std::cout << "SUCCEEDED" << "\033[0m" << std::endl; }
	        else { std::cout << exception << std::endl; }
	        return;
	}
	
	std::cout << (!a_hash.Has(a_key) ? "SUCCEEDED" : "FAILED") << "\033[0m" << std::endl;
}

static void RetrieveTest(HashMap& a_hash, const std::string& a_key, bool a_IsKeyExist) {

	static int testNumber = 0;
	std::cout << "retrieve value, test " << ++testNumber << ":\t\t\t\033[1;31m";
	
	try {
	        a_hash.Retrieve(a_key);
	} catch(const char* exception) {
	        if(!a_IsKeyExist) { std::cout << "SUCCEEDED" << "\033[0m" << std::endl; }
	        else { std::cout << exception << std::endl; }
	        return;
	}
	
	std::cout << (a_hash.Has(a_key) ? "SUCCEEDED" : "FAILED") << "\033[0m" << std::endl;
}

int main() {

	HashMap hash(StrHash, Compare), hashCapacity(StrHash, Compare, 32);
	
	CTORTest(hash);
	CTORCapacityTest(hashCapacity,32);
	CopyCTORTest(hash);
	
	std::string key = "maayan";
	std::string value = "1992";
	
	PutTest(hash, key, value,true);
	PutTest(hash, "hhhh", "111",true);
	PutTest(hash, key, value,false);
	
	RemoveTest(hash, key,true);
	RemoveTest(hash, key,false);
	RemoveTest(hash, "12345",false);
	
	RetrieveTest(hash, "hhhh", true);
	RetrieveTest(hash, key, false);
	
	
	return 0;
}


