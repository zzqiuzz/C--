#include <list>
#include <map> 
#include <set>
#include <unordered_map>
#include <vector>
#include <iostream>
using std::list;
using std::map;
using std::pair;
using std::set;

using std::cout;
using std::tuple;
using std::unordered_map;
using std::vector;

int main(){
    list<int> l = {1}; // 初始化
    l.push_back(2);
    l.push_front(0); // 0, 1, 2 
    auto it = l.begin();
    ++it;
    l.insert(it, 3); // 0 3 1 2 
    l.pop_back(); // 0 3 1
    l.pop_front(); // 3 1
    for (const auto& elem : l) {
        std::cout << elem << " ";
    }

    //vector 是模板
    {
        
    }
    //map

    //pair

    //set
    
    //unorderd_map

    //tuple



    return 0;
}