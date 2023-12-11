//
// Created by ivanm2114 on 11.12.2023.
//

#ifndef OOPPROJECT_ROBOT_H
#define OOPPROJECT_ROBOT_H

#endif //OOPPROJECT_ROBOT_H
#include "Message.h"
#include <unordered_map>
#include <vector>
#include <memory>

using namespace std;

template<class K,class V>
class Robot{
public:
    Robot();
    Robot(string name);
    Robot(string name, unordered_map<K,V> parameters);
    void setParameters(unordered_map<K,V> parameters);
    void setParameter(K key, V data);
    void transferMessage(Robot& robot,BaseMessage<V> message) const;
    void transferMessage(Robot& robot, EditRobotMessage<K,V> message) const;
    void transferMessage(Robot& robot, EditConnectionMessage<K,V> message) const;
    void applyChanges(EditRobotMessage<V,K> message);
    void applyChanges(EditConnectionMessage<V,K> message);
    void printStructure() const;

private:
    string name;
    unordered_map<K,V> parameters;
    vector<shared_ptr<Robot<K,V>>> connectedRobots;
};