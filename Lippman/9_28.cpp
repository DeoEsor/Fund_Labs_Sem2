#include <forward_list>
#include <string>
#include <iterator>
#include <iostream>

int main(){
    
    return 0;
}

void func(std::forward_list<std::string> li,std::string first, std::string second){
    
    std::forward_list<std::string> ::iterator it=li.before_begin();
    
    while(it!=li.end()){
        if(*it==first)
            li.insert_after(it,second);
        it++;
    }
    if(it==li.end())
        li.insert_after(it,second);
}