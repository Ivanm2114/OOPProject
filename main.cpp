#include <iostream>
#include <unordered_map>
#include <string>
#include "Robot.h"

using namespace std;


int main() {
    string c = "Skibidi Toilet";
    string s= "Borya";
    std::cout << "Hello, World!" << std::endl;
    unordered_map<string ,int> a;
    a.insert({"lol1",1});
    a.insert({"lol2",3});
    a.insert({"lol3",3});
    cout << a.at("lol2");
    auto robo = Robot("Borya"s);
    robo.setParameter(c, 2);
    cout << robo.getName();




    return 0;
}
