#include <forward_list>
#include <string>
#include <iterator>
#include <iostream>

int main(){
    
    return 0;
}

void func(std::string s, std::string oldVal, std::string newVal){
    
    std::string ::iterator it=s.begin();
    
    while(it!=s.end()){
        if(*it==oldVal[0])
            s.insert_after(it,newVal);
        it++;
    }
}