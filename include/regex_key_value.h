#ifndef REGEX_KEY_VALUE_H
#define REGEX_KEY_VALUE_H
#include<iostream>
#include<map>
#include<regex>
#include<fstream>


typedef std::pair<std::string, std::string> regexPair  ;
typedef std::map<int,regexPair>::iterator regexMap_itr ;
typedef std::map<int,regexPair> regexMap ;

class regex_key_value
{
    public:
        void add(std::string ty , std::string rx) ;
        void readFromFile(std::string filename) ;
        void displayAll() ;
        std::string getRegex(int key) ;
        std::string gettype(int key) ;
        std::pair<int,std::string> doRegex(std::string token) ;
        std::pair<int,std::string> doRegex_search(std::string token,std::smatch &string_matches) ;
        std::string remove_extra_space(std::string word);
        std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) ;
        std::vector<std::string> split(const std::string &s, char delim) ;

    private:
        regexMap regMap ;

};

#endif // REGEX_KEY_VALUE_H
