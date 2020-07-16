#include "hashMap.h"

typedef std::vector< std::list<std::pair<std::string, std::string> > > t_vector;

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

static void CTORTest(const HashMap<std::string, std::string>& a_hash) {

	static int testNumber = 0;
	std::cout << "CTOR with default capacity, test " << ++testNumber <<  ":\t" << ((16 == a_hash.size()) ? "SUCCEEDED" : "FAILED") << std::endl;
}

static void CTORCapacityTest(const HashMap<std::string, std::string>& a_hash, unsigned int a_capacity) {

	static int testNumber = 0;
	std::cout << "CTOR with capacity, test " << ++testNumber << ":\t\t" 
			<< ((a_capacity == a_hash.t_vector::size()) ? "SUCCEEDED" : "FAILED") << std::endl;
}

static void CopyCTORTest(const HashMap<std::string, std::string>& a_hash) {

	static int testNumber = 0;
	HashMap copyHash(a_hash);
	std::cout << "copy CTOR, test " << ++testNumber << ":\t\t\t" << ((copyHash.size() == a_hash.size()) ? "SUCCEEDED" : "FAILED") << std::endl;
}

static void PutTest(HashMap<std::string, std::string>& a_hash, const std::string& a_key, const std::string& a_value, bool a_validKey) {

	static int testNumber = 0;
	bool result = (a_validKey == a_hash.Put(a_key,a_value));
	result = a_hash.Has(a_key);
	std::cout << "put pair, test " << ++testNumber << ":\t\t\t" << (result ? "SUCCEEDED" : "FAILED") << std::endl;
}

static void RemoveTest(HashMap<std::string, std::string>& a_hash, const std::string& a_key, bool a_IsKeyExist) {

	static int testNumber = 0;
	bool result = (a_IsKeyExist == a_hash.Remove(a_key)) && (!a_hash.Has(a_key));
	std::cout << "remove pair, test " << ++testNumber << ":\t\t\t" << (result ? "SUCCEEDED" : "FAILED") << std::endl;
}


int main() {

	HashMap hash<std::string, std::string>(StrHash, Compare), hashCapacity<std::string, std::string>(StrHash, Compare, 32);
	
	CTORTest(hash);
	CTORCapacityTest(hashCapacity,32);
	CopyCTORTest(hash);
	
	std::string key = "maayan";
	std::string value = "1992";
	
	//PutTest(hash, key, value,true);
	//PutTest(hash, key, value,false);
	
	//RemoveTest(hash, key,true);
	//RemoveTest(hash, key,false);
	//RemoveTest(hash, "12345",false);
	
	return 0;
}


