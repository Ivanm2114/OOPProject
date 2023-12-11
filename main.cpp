#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

typedef std::unordered_map<string, int> Mymap;
int main() {
    std::cout << "Hello, World!" << std::endl;
    Mymap a;
    a.insert(Mymap::value_type("lol",1));
    a.insert(Mymap::value_type("lol2",2));
    a.insert(Mymap::value_type("lol3",3));
    cout << a.at("lol2");



    return 0;
}
