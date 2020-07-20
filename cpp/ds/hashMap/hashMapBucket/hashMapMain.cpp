#include "hashMap.h"

struct Hash {
        unsigned int operator()(const std::string &a_str) const {
                int i, sum = 0;
	        for(i = 0 ; i < a_str.length() ; ++i) {
		        sum += a_str[i]; 
	        }
	        
	        return sum;
        }
};

static void CTORTest(const HashMap<std::string, std::string, Hash>& a_hash) {

	static int testNumber = 0;
	std::cout << "CTOR with default capacity, test " << ++testNumber <<  ":\t\033[1;31m" 
	                << ((16 == a_hash.size()) ? "SUCCEEDED" : "FAILED") << "\033[0m" << std::endl;
}

static void CTORCapacityTest(const HashMap<std::string, std::string, Hash>& a_hash, unsigned int a_capacity) {

	static int testNumber = 0;
	std::cout << "CTOR with capacity, test " << ++testNumber << ":\t\t\033[1;31m" 
	                << ((a_capacity == a_hash.size()) ? "SUCCEEDED" : "FAILED") << "\033[0m" << std::endl;
}

static void CopyCTORTest(const HashMap<std::string, std::string, Hash>& a_hash) {

	static int testNumber = 0;
	HashMap<std::string, std::string, Hash> copyHash(a_hash);
	std::cout << "copy CTOR, test " << ++testNumber << ":\t\t\t\033[1;31m" 
	                << ((copyHash.size() == a_hash.size()) ? "SUCCEEDED" : "FAILED") << "\033[0m" << std::endl;
}

static void PutTest(HashMap<std::string, std::string, Hash>& a_hash, const std::string& a_key, const std::string& a_value, bool a_validKey) {

	static int testNumber = 0;
	bool result = (a_validKey == a_hash.Put(a_key,a_value));
	result = a_hash.Has(a_key);
	std::cout << "put pair, test " << ++testNumber << ":\t\t\t\033[1;31m" << (result ? "SUCCEEDED" : "FAILED") << "\033[0m" << std::endl;
}

static void RemoveTest(HashMap<std::string, std::string, Hash>& a_hash, const std::string& a_key, bool a_IsKeyExist) {

	static int testNumber = 0;
	std::cout << "remove pair, test " << ++testNumber << ":\t\t\t\033[1;31m";
	
	try {
	        a_hash.Remove(a_key);
	} catch(Exception& exception) {
	        if(!a_IsKeyExist) { std::cout << "SUCCEEDED" << "\033[0m" << std::endl; }
	        else { std::cout << exception.GetError() << "\033[0m"<< std::endl; }
	        return;
	}
	
	std::cout << (!a_hash.Has(a_key) ? "SUCCEEDED" : "FAILED") << "\033[0m" << std::endl;
}

static void RetrieveTest(HashMap<std::string, std::string, Hash>& a_hash, const std::string& a_key, bool a_IsKeyExist) {

	static int testNumber = 0;
	std::cout << "retrieve value, test " << ++testNumber << ":\t\t\t\033[1;31m";
	
	try {
	        a_hash.Retrieve(a_key);
	} catch(Exception& exception) {
	        if(!a_IsKeyExist) { std::cout << "SUCCEEDED" << "\033[0m" << std::endl; }
	        else { std::cout << exception.GetError() << "\033[0m"<< std::endl; }
	        return;
	}
	
	std::cout << (a_hash.Has(a_key) ? "SUCCEEDED" : "FAILED") << "\033[0m" << std::endl;
}

int main() {

	HashMap<std::string, std::string, Hash> hash, hashCapacity(32);
	
	CTORTest(hash);
	CTORCapacityTest(hashCapacity,32);
	CopyCTORTest(hash);
	
	std::string key = "maayan";
	std::string value = "1992";
	
	PutTest(hash, key, value,true); //1
	PutTest(hash, "hhhh", "111",true); //2
	PutTest(hash, key, value,false); //3
	
	RemoveTest(hash, key,true); //1
	RemoveTest(hash, key,false); //2
	RemoveTest(hash, "12345",false); //3
	
	RetrieveTest(hash, "hhhh", true); //1
	RetrieveTest(hash, key, false); //2
	
	
	return 0;
}


