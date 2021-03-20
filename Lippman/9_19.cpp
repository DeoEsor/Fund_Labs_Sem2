#include <list>
#include <string>
#include <iterator>
#include <iostream>

int main(){
    std::list<std::string> list(5);
    std::list<std::string> :: iterator it=list.begin();
    std::string str;
    while(it!=list.end())
        *(it++)=str;
    return 0;
}
