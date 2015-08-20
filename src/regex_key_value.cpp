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

void regex_key_value::readFromFile(std::string filename){
            std::ifstream infile ;
            std::string data ;
            std::vector<std::string> dataVec ;
            infile.open(filename) ;
            while(1){
            if(std::getline(infile,data)){
                    data = remove_extra_space(data) ;
                    dataVec = split(data,' ') ;
                    add(dataVec[0],dataVec[1]) ;
                    dataVec.empty() ;
                }else{
                    break ;
                }
            }

        }


void regex_key_value::displayAll(){
            std::cout<<"\n" ;
            for(regexMap_itr itr = regMap.begin() ; itr != regMap.end() ; itr++ ){
                std::cout<<itr->first<<" -> "<<std::get<0>(itr->second)<<" -> "<<std::get<1>(itr->second)<<"\n" ;
            }
        }



std::string regex_key_value::remove_extra_space(std::string word){
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



std::vector<std::string> &regex_key_value::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> regex_key_value::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}


