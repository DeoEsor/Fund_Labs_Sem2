#include <vector>
#include <list>
#include <iterator>
#include <iostream>

int main(){
    int ia[]={0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
    std::vector<int> vec;
    std::list<int> li;
    std::list<int>::iterator it=li.begin();
    std::vector<int>::iterator iter=vec.begin();
    for(int i=0;ia[i]<=89;i++){
        vec[i]=ia[i];
        li.push_back(ia[i]);
    }
    while(iter!=vec.end()){
        if(*iter % 2)
            vec.erase(iter);
        else
            iter++;
    }
    while(it!=li.end()){
        if(*it % 2)
            li.erase(it);
        else
            it++;
    }
    return 0;
}