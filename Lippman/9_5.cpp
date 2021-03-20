#include <vector>
#include <iterator>
#include <iostream>

static std::vector <int> :: iterator error;

std::vector <int> :: iterator Func(std::vector <int> :: iterator it,std::vector <int> :: iterator im, int o){
    if(*it==o ) return it;
    if(*im==o) return im;
    if((it++)==(im--)) return error;
}

int main(){
    std::vector <int> i_am_vector;
    std::vector <int> :: iterator it = i_am_vector.begin();
    error =i_am_vector.begin();
    std::vector <int> :: iterator im = i_am_vector.end();
    std::cout<< *Func(it,im,5);
    return 0;
}