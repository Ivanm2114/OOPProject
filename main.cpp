#include <iostream>
#include <unordered_map>
#include <string>
#include "EditConnectionMessage.h"

using namespace std;


int main() {
    string c = "Skibidi Toilet";
    string s = "Borya";
    unordered_map<string, int> a;
    a.insert({"lol1", 1});
    a.insert({"lol2", 3});
    a.insert({"lol3", 3});
    auto robo = Robot("Borya");
    auto ribi = Robot("Biba");
    auto robba = Robot("Boba");
    robo.setParameter(c, 2);
    cout << robo.getName() << endl;
    auto connectMsg = EditConnectionMessage(&robo, &ribi, true);
    auto connectMsg2 = EditConnectionMessage(&robba, &ribi, true);
    connectMsg.apply();
    connectMsg2.apply();
    robo.printTotalStructure();
    auto params = robo.getParameters();
    cout << params.size()<<endl;

    auto editRobotMsg = EditRobotMessage("Skibidi Toilet", 3);
    robo.applyChanges(editRobotMsg);
    cout << robo.getParameters().size()<<endl;
    cout << robo["Skibidi Toilet"] << endl;
    connectMsg2.setValue(false);
    connectMsg2.apply();
    ribi.printTotalStructure();
    ribi + robba;
    ribi.printTotalStructure();
    ribi - robba;
    ribi.printTotalStructure();
    cout << robo.getConnectedRobots().size() << endl;
    ribi + robba;
    auto baseMsg = BaseMessage("ABOBA", 10);
    robo.sendMassMessage(baseMsg);
    robo.sendMessage(&robba,baseMsg);
    ribi.sendMessage(&robba,baseMsg);
    robo.printTotalStructure();
    robo.deleteFromNet();
    robo.printTotalStructure();



    return 0;
}
