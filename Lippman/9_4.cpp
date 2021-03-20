#include <vector>
#include <iterator>
#include <iostream>

bool Func(std::vector <int> :: iterator it,std::vector <int> :: iterator im, int o){
    if(*it==o || *im==o) return true;
    if((it++)==(im--)) return false;
}

int main(){
    std::vector <int> i_am_vector;
    std::vector <int> :: iterator it= i_am_vector.begin();
    std::vector <int> :: iterator im= i_am_vector.begin();
    std::cout<< Func(it,im,5);
    return 0;
}