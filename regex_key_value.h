#include <iostream>
#include <map>
#include <regex>


typedef std::pair<std::string, std::string> regexPair  ;
typedef std::map<int,regexPair>::iterator regexMap_itr ;
typedef std::map<int,regexPair> regexMap ;

class regex_key_value
{
	private:
		regexMap regMap ;

	public:
		void add(std::string ty , std::string rx){
			regMap.insert(std::make_pair(regMap.size(),regexPair(ty,rx))) ;
		}
		std::string getRegex(int key){
			regexPair regexP =  regMap.find(key)->second ;
			return std::get<1>(regexP) ;
		}
		std::string gettype(int key){
			regexPair regexP =  regMap.find(key)->second ;
			return std::get<0>(regexP) ;
		}
		std::pair<int,std::string> doRegex(std::string token){
			for(regexMap_itr itr = regMap.begin() ; itr != regMap.end(); itr++ ){
				auto reg = std::regex(std::get<1>(itr->second));
				if(std::regex_match(token, reg)) {
					return std::make_pair(itr->first, std::get<0>(itr->second) ) ;
				}
			}
			return std::make_pair(-1,"Unknown") ;
		}
};


