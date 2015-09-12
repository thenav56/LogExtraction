#ifndef REGEX_KEY_VALUE_H
#define REGEX_KEY_VALUE_H
#include<fstream>
#include<map>
#include<regex>

namespace std_boost = std ;
typedef std::pair<std::string, std::string> regexPair  ;
typedef std::map<int,regexPair>::iterator regexMap_itr ;
typedef std::map<int,regexPair> regexMap ;

class regex_key_value
{
	public:
		void add(std::string ty , std::string rx) ;
		std::string getRegex(int key) ;
		std::string gettype(int key) ;
		std::pair<int,std::string> doRegex(std::string token) ;
		void readFromFile(std::string filename); 
		int get_regex_count() ; 
		bool remove_regex(int key) ; 
		std::string remove_extra_space(std::string word)  ;
		std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)  ; 
		std::vector<std::string> split(const std::string &s, char delim) ; 
	private:
		regexMap regMap ;
		int regex_count =  0 ;

};

#endif // REGEX_KEY_VALUE_H
