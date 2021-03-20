#include <vector>
#include <iterator>
#include <iostream>

int main(){
    std::vector <int> first={3, 4, 5};
    std::vector <int> second={3, 4, 8,7};
    if(first.size()!=second.size()) std::cout<<false;
    else{

        std::vector <int> :: iterator i_first = first.begin();
        std::vector <int> :: iterator i_second = second.begin();

        for(int i=0;i<first.size();i++){
            if(*i_first==*i_second) continue;
            else {std::cout<<false; break;}
        }
        if(i_second==second.end()) std::cout<<true;
    }
    return 0;
}