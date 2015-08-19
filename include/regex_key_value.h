#ifndef REGEX_KEY_VALUE_H
#define REGEX_KEY_VALUE_H
#include<iostream>
#include<map>
#include<regex>


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
    private:
        regexMap regMap ;

};

#endif // REGEX_KEY_VALUE_H
