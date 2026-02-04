#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

int main() {
    unordered_map<string, int> map={{"one", 1}, {"two", 2}};
    unordered_map<string, int> map1;
    cout<<map1.size()<<endl;
    cout<<map["one"]<<endl;
    map.insert({"one", 2});
    cout<<map.size()<<endl;
    cout <<map.at("one")<<endl;
    cout<<(map.find("one")!=map.end())<<endl;
    return 0;

}