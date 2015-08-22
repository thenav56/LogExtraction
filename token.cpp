#include<iostream>
#include<vector>
#include<regex>
#include<string>
#include"include/regex_key_value.h"

using namespace std ;

//global variable and objects
regex_key_value ourRegex ;

string remove_extra_space(std::string word) ;
string key_value_extrac(std::string word)  ;
string key_value_extrac_search(std::string word) ;

int main(){

//    ourRegex.add("ip_address" , "([0-9]+)\\.([0-9]+)\\.([0-9]+)\\.([0-9]+)(::([0-9]+)|)") ;
//    ourRegex.add("date","(199[0-9]|200[0-9])-([1-9]|0[1-9]|1[012])-([1-9]|[0-2][1-9]|3[01])") ;
//    ourRegex.add("url","([a-zA-Z]+)\\.([a-zA-Z]+)\\.([a-zA-Z]+)") ;
//    ourRegex.add("time","(([0-1][0-9])|([2][0-3])):([0-5][0-9]):([0-5][0-9])") ;
//    ourRegex.add("file","((https|http|ftp|http)\://|/)[a-zA-Z0-9\-\.]+\.[a-zA-Z]{2,3}(/\\S*)") ;

    ourRegex.readFromFile("regex.txt") ;

    string word = "cleveland.directrouter.com 192.168.0.1 - - [2007-03-14 23:57:05 -0800] \"GET /fotos/lenew.jpg HTTP/1.0\" 200 1241 \"-\" \"-\"" ;

    word = remove_extra_space(word) ;
    //cout<<word<<"\n" ;
    vector<std::string> vec_string ;
    string temp  ;
   // int quotation_flag ;
    for(int unsigned i= 0 ; i < word.size() ; i++){
        if(word[i] == ' '){
            vec_string.push_back(temp) ;
            temp.clear() ;
            continue ;
        }
        temp += word[i] ;
    }
cout<<"---------------USING-REGEX-MATCH-----------------------------------------------\n\n" ;
    for(int unsigned i = 0 ; i < vec_string.size() ; i++){
        cout<<key_value_extrac(vec_string[i])<<"\n" ;
        cout<<"---------------------------------------------\n" ;
    }

cout<<"\n\n---------------USING-REGEX-SEARCH-----------------------------------------------\n\n" ;

    for(int unsigned i = 0 ; i < vec_string.size() ; i++){
        cout<<key_value_extrac_search(vec_string[i])<<"\n" ;
        cout<<"---------------------------------------------\n" ;
    }

    return 0 ;
}


string remove_extra_space(std::string word){
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

string key_value_extrac(std::string word){

    std::pair<int,std::string> result = ourRegex.doRegex(word) ;

    return string(std::get<1>(result)+"( "+ std::to_string(std::get<0>(result)) +" )" + " :: " + word ) ;
}

string key_value_extrac_search(std::string word){
    std::smatch string_matches ;
    std::pair<int,std::string> result = ourRegex.doRegex_search(word,string_matches ) ;

    return string(std::get<1>(result)+"( "+ std::to_string(std::get<0>(result)) +" )" + " :: " + string_matches.str() ) ;
}
