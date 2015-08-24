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
bool is_outerbound(char bound) ;
bool checkRelation(char x , char y ) ;
vector<std::string> tokenize(string word) ;


int main(){
    ourRegex.readFromFile("regex.txt") ;

    string word = "cleveland.directrouter.com 192.168.0.1 - - [2007-Oct-14 23:57:05 -0800] \"GET /fotos/lenew.jpg HTTP/1.0\" 200 1241 \"-\" \"-\"" ;

    vector<std::string> vec_string = tokenize(word) ;

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

vector<std::string> tokenize(string word){
    word = remove_extra_space(word) ;
    //cout<<word<<"\n" ;
    vector<std::string> vec_string ;
    string temp  ;
    vector<char> bound_stack ;
    bool bound = false ;

    for(int unsigned i= 0 ; i < word.size() ; i++){
        if(word[i] ==  '[' || word[i] ==  '{' || word[i] ==  '\"' || word[i] ==  '\'' ){
            if((word[i] == '\"' || word[i] == '\'') && word[i] == bound_stack[bound_stack.size()-1]){
                bound = false ;
                bound_stack.pop_back() ;
            }else{
                bound = true  ;
                bound_stack.push_back(word[i]) ;
                }
        }else if(word[i] == ']' || word[i] ==  '}' || word[i] ==  '\"' || word[i] ==  '\''){
            bool bool_t = false ;
            if(word[i] == ']' && bound_stack[bound_stack.size()-1] == '[' ){
                bool_t = true ;
            }else if(word[i] == '}' && bound_stack[bound_stack.size()-1] == '{' ){
                bool_t = true ;
            }else if(word[i] == bound_stack[bound_stack.size()-1]){
                bool_t = true ;
            }

            if(bool_t){
                bound = false ;
                bound_stack.pop_back() ;
            }
        }
        if( !bound && (word[i] == ' ' || (i == word.size()-1))){
            vec_string.push_back(temp) ;
            temp.clear() ;
            continue ;
        }
        temp += word[i] ;
    }
    cout<<temp<<"\n" ;
    bound_stack.empty() ;
    for(int unsigned i = 0 ;  i < vec_string.size() ; i++){
            if(is_outerbound(vec_string[i][0])){
                bound_stack.push_back(vec_string[i][0]) ;
                vec_string[i].erase(0,1) ;
                i-- ;
            }else if(is_outerbound(vec_string[i][vec_string[i].size() - 1 ])){
                if(checkRelation(bound_stack[bound_stack.size() - 1] , vec_string[i][vec_string[i].size() - 1 ] ) ){
                        bound_stack.pop_back() ;
                        vec_string[i].erase(vec_string[i].size() - 1 )  ;
                }
            }

    }
    return vec_string   ;
}


bool is_outerbound(char bound){
    if(bound == '\'' || bound == '"' || bound == '[' || bound == ']' || bound == '{' || bound == '}')
        return true ;
    return false ;
}

bool checkRelation(char x , char y ){
    if(x == '[' && y == ']')
        return true ;
    if(x == '\'' && y == '\'')
        return true ;
    if(x == '"' && y == '"')
        return true ;
    if(x == '{' && y == '}')
        return true ;
    return false ;
}

