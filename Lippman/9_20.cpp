#include <list>
#include <deque>
#include <string>
#include <iterator>
#include <iostream>

int main(){
    std::list<int> list={0,1,2,3,4,5};
    std::list<int> :: iterator it=list.begin();
    std::deque<int> even;
    std::deque<int> :: iterator iter_even=even.begin();
    std::deque<int> noeven;
    std::deque<int> :: iterator iter_noeven=noeven.begin();
    std::string str;
    while(it!=list.end()){
        if(!(*it % 2))
            *(iter_noeven++)=*(it++);
        else
            *(iter_even++)=*(it++);
    }
    return 0;
}
