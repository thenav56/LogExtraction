#ifndef REGEX_KEY_VALUE_H
#define REGEX_KEY_VALUE_H
#include <iostream>
#include <map>
#include <regex>
#include <boost/regex.hpp>

namespace std_boost = std ;

typedef std::pair<std::string, std::string> regexPair  ;
typedef std::map<int,regexPair>::iterator regexMap_itr ;
typedef std::map<int,regexPair> regexMap ;

class regex_key_value
{
	private:
		regexMap regMap ;
		int regex_count =  0 ;

	public:

		void readFromFile(std::string filename){
			    std::ifstream infile ;
			    std::string data ;
			    std::vector<std::string> dataVec ;
			    infile.open(filename) ;
			    while(1){
			    if(std::getline(infile,data)){
				    data = remove_extra_space(data) ;
				    if(data[0] == ';')
								continue ;
				    dataVec = split(data,' ') ;
				    add(dataVec[0],dataVec[1]) ;
				    dataVec.clear() ;
				}else{
				    break ;
				}
			    }

			}

		void add(std::string ty , std::string rx){
			regMap.insert(std::make_pair(regMap.size(),regexPair(ty,rx))) ;
			regex_count++ ;
		}

		int get_regex_count(){
			return regex_count ;
		}

		std::string getRegex(int key){
			if(key<regex_count){
				regexPair regexP =  regMap.find(key)->second ;
				return regexP.second ;
			}
				return "Not Found" ;
		}

		std::string gettype(int key){
			if(key<regex_count){
				regexPair regexP =  regMap.find(key)->second ;
				return regexP.first ;
			}
				return "Not Found" ;
		}
		std::pair<int,std::string> doRegex(std::string token){
			for(regexMap_itr itr = regMap.begin() ; itr != regMap.end(); itr++ ){
				auto reg = std_boost::regex(std::get<1>(itr->second));
				if(std_boost::regex_match(token, reg)) {
					return std::make_pair(itr->first, std::get<0>(itr->second) ) ;
				}
			}
			return std::make_pair(-1,"Unknown") ;
		}

	std::string remove_extra_space(std::string word){
		    int space_start = -1  ;
		    int space_count = 0  ;
		    for(int unsigned i=0 ; i < word.size() ; i++){
		        if(word[i] == '\t'){
		            word[i] = ' ' ;
		        }
		    }
		    for(int unsigned i=0 ; i < word.size() ; i++){
		        if(space_start != -1 ){
		            if(word[i] == ' '){
		                space_count++ ;
		            }else{
		                word.erase(space_start,space_count) ;
		                i -= space_count ;
		                space_start = -1 ;
		                space_count = 0 ;
		            }
		        }else{
		            if(word[i] == ' '){
		                if(i == 0){
		                    space_count++ ;
		                }
		                space_start = i ;
		            }
		        }
		    }
		        return word ;
		}

		 std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
		    std::stringstream ss(s);
		    std::string item;
		    while (std::getline(ss, item, delim)) {
		        elems.push_back(item);
		    }
		    return elems;
		}

		std::vector<std::string> split(const std::string &s, char delim) {
		    std::vector<std::string> elems;
		    split(s, delim, elems);
		    return elems;
		}

};

#endif
