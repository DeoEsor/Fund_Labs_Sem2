#include <vector>
#include <list>
#include <iterator>
#include <iostream>

int main(){
    std::vector <std::string> strings;              std::vector <std::string> :: iterator i_strings = strings.begin();
    std::list <char*> chars={"it", "or", "myu"};    std::list <char*>:: iterator i_chars = chars.begin();
    

    strings.reserve(chars.size());

    for(int i=0; i<chars.size();i++)
        *(i_strings++)=*(i_chars++);
    
    
    return 0;
}