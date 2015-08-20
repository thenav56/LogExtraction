#include "../include/regex_key_value.h"

void regex_key_value::add(std::string ty , std::string rx){
	regMap.insert(std::make_pair(regMap.size(),regexPair(ty,rx))) ;
}

std::string regex_key_value::getRegex(int key){
	regexPair regexP =  regMap.find(key)->second ;
	return std::get<1>(regexP) ;
}

std::string regex_key_value::gettype(int key){
	regexPair regexP =  regMap.find(key)->second ;
	return std::get<0>(regexP) ;
}

std::pair<int,std::string> regex_key_value::doRegex(std::string token){
	std::smatch string_matches;
	for(regexMap_itr itr = regMap.begin() ; itr != regMap.end() ; itr++ ){
		if(std::regex_match(token, string_matches , std::regex(std::get<1>(itr->second)  ))){
			return std::make_pair(itr->first, std::get<0>(itr->second) ) ;
		}
	}
	return std::make_pair(-1,"Unknown") ;
}

