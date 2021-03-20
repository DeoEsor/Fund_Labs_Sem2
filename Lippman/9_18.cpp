#include <deque>
#include <string>
#include <iterator>
#include <iostream>

int main(){
    std::deque<std::string> deq(5);
    std::deque<std::string> :: iterator it=deq.begin();
    std::string str;
    while(it!=deq.end())
        *(it++)=str;
    return 0;
}