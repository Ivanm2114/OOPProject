#include <iostream>
#include <unordered_map>
#include <string>
#include "EditConnectionMessage.h"
#include <assert.h>

using namespace std;


int main() {
    auto baseMsg = BaseMessage();
    assert(baseMsg.getText().empty()== true);
    baseMsg.setValue("");
    assert(baseMsg.getText().empty());
    baseMsg.setValue("ABOBA");
    assert(baseMsg.getText()=="ABOBA");
    baseMsg.setValue(10);
    assert(baseMsg.getInt()==10);
    baseMsg.setValue("ABOBA2",30);
    assert(baseMsg.getText()=="ABOBA2" and baseMsg.getInt()==30);
    assert(baseMsg.getClass()=="BaseMessage");

    auto robbo = Robot();
    assert(robbo.getName().empty()==true);
    robbo.setName("");
    assert(robbo.getName().empty()==true);
    robbo.setName("Borya");
    assert(robbo.getName()=="Borya");
    assert(robbo.getParameters().empty()== true);
    robbo.setParameter("Skibidi Dop Dop yes yes", 20);
    assert(robbo.getParameters().size()==1);
    unordered_map<string,int> a;
    a.insert({"LOL",2});
    a.insert({"SUSSY",224});
    robbo.setParameters(a);
    assert(robbo.getParameters().size()==3);
    auto boba = Robot("BOBA");
    auto biba = Robot("BIBA");
    auto robot = Robot("Robotnik");
    auto conMsg = EditConnectionMessage(&robbo,&boba,true);
    assert(robbo.getConnectedRobots().empty()== true);
    conMsg.apply();
    assert(robbo.getConnectedRobots().size()==1);
    assert(boba.getConnectedRobots().size()==1);
    auto conMsg2 = EditConnectionMessage(&robbo,&biba,"connect");
    conMsg2.apply();
    auto conMsg3 = EditConnectionMessage(&biba, &robot,true);
    assert(conMsg3.getClass()=="EditConnectionMessage");
    conMsg3.apply();
    assert(robbo.getConnectedRobots().size()==2);
    auto robot2 = Robot(robot);
    robot2.setName("Robotnik2");
    auto conMsg4 = EditConnectionMessage(&robot2,&biba,true);
    conMsg4.apply();
    robbo.printTotalStructure();
    robbo.sendMessage(&robot,baseMsg);
    assert(robot.getLastMessage()==&baseMsg);
    robot2.sendMassMessage(baseMsg);
    assert(biba.getLastMessage()==&baseMsg);
    assert(biba.getConnectedRobots().size()==3);
    assert(robbo.getConnectedRobots().size()==2);
    biba.deleteFromNet();
    robbo.printTotalStructure();
    biba.printTotalStructure();
    assert(biba.getConnectedRobots().empty()== true);
    assert(robbo.getConnectedRobots().size()==3);
    auto baseMsg2 = BaseMessage("Test",333);
    biba.sendMessage(&robbo,baseMsg2);
    assert(robbo.getLastMessage()!=&baseMsg2);
    assert(robbo.getClass()=="Robot");

    auto editMesg = EditRobotMessage();
    assert(editMesg.getClass()=="EditRobotMessage");
    assert(editMesg.getValue()==0 and editMesg.getKey().empty()== true);
    editMesg.setValue(123);
    editMesg.setKey("");
    assert(editMesg.getValue()==123 and editMesg.getKey().empty()== true);
    editMesg.setKey("BIBOBUBA");
    assert(editMesg.getValue()==123 and editMesg.getKey()=="BIBOBUBA");
    biba.applyChanges(editMesg);
    assert(biba.getParameters().empty()==false and biba.getParameters().size()==1);
    biba.deleteParameter("BIBOBUBA");
    assert(biba.getParameters().empty()== true);





    return 0;
}
