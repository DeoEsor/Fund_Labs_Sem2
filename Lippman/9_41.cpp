#include <vector>
#include <string>
#include <iterator>
#include <iostream>

int main(){
    std::string str="";
    std::vector<char> vec;
    for(int i =0;i<vec.size();i++)
        str+=vec[i];
    return 0;
}
