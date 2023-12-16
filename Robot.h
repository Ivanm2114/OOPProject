//
// Created by ivanm2114 on 11.12.2023.
//

#ifndef OOPPROJECT_ROBOT_H
#define OOPPROJECT_ROBOT_H

#endif //OOPPROJECT_ROBOT_H


#include <unordered_map>
#include <utility>
#include <vector>
#include <memory>
#include <string>
#include "BaseMessage.h"



using namespace std;


class Robot {
public:
    Robot();

    explicit Robot(const string& name);

    Robot(Robot& baseRobot);

    Robot(const string& name, const unordered_map<string, int>& parameters);

    void setName(const string& new_name);

    void setParameters(unordered_map<string, int> &new_parameters);

    void setParameter(string key, int data);

    void editConnectionWith(Robot* second,bool mode);

    bool transferMessage(Robot* origin,Robot* transmitter,Robot* target, BaseMessage &message) const;

    void applyChanges(BaseMessage &message);

    auto getTotalStructure() const;

    auto getParameters() const;

    auto getName() const;

private:
    string name;
    unordered_map<string, int> parameters;
    vector<Robot*> connectedRobots;

    int isConnectedRobot(Robot* second) const;


    void copy_to(unordered_map<string , int> &origin, unordered_map<string, int> &destination);

};


void Robot::copy_to(unordered_map<string, int> &origin, unordered_map<string, int> &destination) {
    for (const auto &[key, value]: origin) {
        destination.insert({key, value});
    }
}



Robot::Robot() = default;


Robot::Robot(const string& name) {
    setName(name);
};


Robot::Robot(const string& name, const unordered_map<string, int>& parameters) {
    setName(name);

}


void Robot::setName(const std::string& new_name) {
    if (!new_name.empty()) {
        name = new_name;
    } else {
        cout << "This name cannot be set";
    }
}


void Robot::setParameter(string key, int data) {
    parameters.insert_or_assign(key, data);
}



void Robot::setParameters(unordered_map<string, int> &new_parameters) {
    for (const auto &[key, value]: new_parameters) {
        setParameter(key, value);
    }
}


auto Robot::getName() const {
    return name;
}



auto Robot::getParameters() const {
    string t = "Parameters of " + name + ":\n";

    for (const auto &[key, value]: parameters) {
        t += (string) key;
        t += ": ";
        t += std::to_string(value);
        t += "\n";
    }
    return t;
}

int Robot::isConnectedRobot(Robot *second) const {
    for(int i=0;i<connectedRobots.size();i++){
        if(connectedRobots[i]==second) return i;
    }
    return -1;
}


void Robot::editConnectionWith(Robot *second, bool mode) {
    auto t = isConnectedRobot(second);
    if(mode and t<0)
    this->connectedRobots.push_back(second);
    else if(t>=0 and !mode){
        connectedRobots.erase(connectedRobots.begin()+t);
    }
    else{
        cout << "Action is impossible. Robots are already connected or disconnected";
    }
}

bool Robot::transferMessage(Robot* origin,Robot* transmitter,Robot* target, BaseMessage &message) const {
    if(this!=target){
        auto t = isConnectedRobot(target);
        if(t>=0){
            connectedRobots[t]->transferMessage(origin,target,message);
        }
        else{
            int i=0;
            bool flag=false;
            do{
                flag = connectedRobots[i]->transferMessage(origin,target,message);
                i++;
            } while (i<connectedRobots.size() and !flag);
        }
    }
    else{
        cout << "Robot " + this->name + "recieved message from robot" + origin->name +
        ". The message: " + message.getMessage();
        return true;
    }
    return false;
}