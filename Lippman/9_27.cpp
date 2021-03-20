#include <forward_list>
#include <iterator>
#include <iostream>

int main(){
    std::forward_list<int> li;
    std::forward_list<int> ::iterator it=li.before_begin();
    auto iter_next=it;
    while(it!=li.end()){
        iter_next=it;
        if(!(*(++iter_next) % 2))
            li.erase_after(it);
        else
            it++;
    }
    return 0;
}
