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
#include <sstream>
#include "EditRobotMessage.h"

string star="*";
string space=" ";

string operator*(const string& s, unsigned int n) {
    stringstream out;
    while (n--)
        out << s;
    return out.str();
}


using namespace std;


class Robot {
public:
    Robot();

    explicit Robot(const string &name);

    Robot(Robot &baseRobot);

    Robot(const string &name, const unordered_map<string, int> &parameters);

    void setName(const string &new_name);

    void setParameters(unordered_map<string, int> &new_parameters);

    void setParameter(string key, int value);

    void editConnectionWith(Robot *second, bool mode);

    void sendMessage(Robot *target, BaseMessage &message, bool massMessage = false);

    void applyChanges(EditRobotMessage &message);

    void printTotalStructure() const;

    auto getParameters() const;

    auto getName() const;

    const BaseMessage *getLastMessage() const;

    bool isConnected(Robot *robot) const;

    bool isConnected(string& robotsName) const;

private:
    string name;
    unordered_map<string, int> parameters;
    vector<Robot *> connectedRobots;

    BaseMessage *lastReceivedMessage;

    int isInVector(Robot *robot, vector<Robot *> robotList) const;

    void copy_to(unordered_map<string, int> &origin, unordered_map<string, int> &destination);

    bool transferMessage(Robot *origin, Robot *transmitter, Robot *target,
                         BaseMessage &message, vector<Robot *> route, bool massMessage);

    void copy_to(vector<Robot *> &origin, vector<Robot *> &destination);

    void addConnections(vector<string> *robotsNames, unordered_map<string, vector<string>> *structure, int n=0) const;

};


void Robot::copy_to(unordered_map<string, int> &origin, unordered_map<string, int> &destination) {
    for (const auto &[key, value]: origin) {
        destination.insert({key, value});
    }
}


Robot::Robot() = default;


Robot::Robot(const string &name) {
    setName(name);
};

Robot::Robot(Robot &baseRobot) {
    name = baseRobot.name;
    copy_to(baseRobot.parameters, parameters);
    copy_to(baseRobot.connectedRobots, connectedRobots);
}


Robot::Robot(const string &name, const unordered_map<string, int> &parameters) {
    setName(name);

}


void Robot::setName(const std::string &new_name) {
    if (!new_name.empty()) {
        name = new_name;
    } else {
        cout << "This name cannot be set";
    }
}


void Robot::setParameter(string key, int value) {
    parameters.insert_or_assign(key, value);
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

int Robot::isInVector(Robot *robot, vector<Robot *> robotList) const {
    for (int i = 0; i < robotList.size(); i++) {
        if (robotList[i] == robot) return i;
    }
    return -1;
}


void Robot::editConnectionWith(Robot *second, bool mode) {
    auto t = isInVector(second, connectedRobots);
    if (mode and t < 0)
        this->connectedRobots.push_back(second);
    else if (t >= 0 and !mode) {
        connectedRobots.erase(connectedRobots.begin() + t);
    } else {
        cout << "Action is impossible. Robots are already connected or disconnected";
    }
}

bool Robot::transferMessage(Robot *origin, Robot *transmitter, Robot *target,
                            BaseMessage &message, vector<Robot *> route, bool massMessage) {
    if (this != target) {
        auto t = isInVector(target, connectedRobots);
        if (t >= 0 and connectedRobots[t]->getLastMessage() != &message) {
            route.push_back(this);
            connectedRobots[t]->transferMessage(origin, this, target, message, route, massMessage);
        } else {
            int i = 0;
            bool flag = false;
            do {
                if (connectedRobots[i] != origin and connectedRobots[i] != transmitter and
                    !isInVector(connectedRobots[i], route)) {
                    route.push_back(this);
                    flag = connectedRobots[i]->transferMessage(origin, this, target, message,
                                                               route, massMessage);
                }
                i++;
            } while (i < connectedRobots.size() and !flag);
        }
    } else {
        cout << "Robot " + this->name + "recieved message from robot" + origin->name +
                ". The message: " + message.getMessage();
        lastReceivedMessage = &message;
        return true;
    }
    return false;
}

const BaseMessage *Robot::getLastMessage() const {
    return lastReceivedMessage;
}

void Robot::sendMessage(Robot *target, BaseMessage &message, bool massMessage) {
    vector<Robot *> route;
    bool flag = false;
    if (target != this) {
        flag = transferMessage(this, this, target, message, route, massMessage);
    } else {
        cout << "You don`t need to send message its the same robot";
    }
    if (!flag) {
        cout << "Couldn`t send the message";
    }

}

void Robot::copy_to(vector<Robot *> &origin, vector<Robot *> &destination) {
    for (auto i: origin) {
        destination.push_back(i);
    }
}


void Robot::applyChanges(EditRobotMessage &message) {
    setParameter(message.getKey(), message.getValue());

}

bool Robot::isConnected(Robot *robot) const {
    isInVector(robot,connectedRobots);
}

bool Robot::isConnected(std::string& robotsName) const {
    for(int i=0;i<connectedRobots.size();i++){
        if(connectedRobots[i]->getName()==robotsName) return true;
    }
    return false;
}

void Robot::addConnections(vector<std::string> *robotsNames, unordered_map<std::string, vector<std::string>> *structure,
                           int n) const {
    vector<string> connections;
    string spaces;
    for (int i = 0; i < robotsNames->size(); i++) {
        if(isConnected((*robotsNames)[i])){
            spaces = space*((int)(*robotsNames)[i].length()-1);
            connections.push_back(star+spaces);
            spaces = space*((int)name.length()-1);
            structure->at((*robotsNames)[i]).push_back(star+spaces);
        }
        else{
            spaces = space*((int)(*robotsNames)[i].length());
            connections.push_back(spaces);
            spaces = space*((int)name.length());
            structure->at((*robotsNames)[i]).push_back(spaces);
        }
    }
    spaces = space*(int)(name.length()-1);
    connections.push_back(star+spaces);
    structure->insert({name,connections});
    robotsNames->push_back(name);
    ++n;
    for(int i=0;i<connectedRobots.size();i++){
        if(structure->find(connectedRobots[i]->getName())==structure->end()){
            connectedRobots[i]->addConnections(robotsNames,structure,n);
        }
    }


}

void Robot::printTotalStructure() const {
    unordered_map<string, vector<string>> structure;
    vector<std::string> robotsOrder;
    int maxLen=-1;
    addConnections(&robotsOrder,&structure);
    for(int i=0;i<robotsOrder.size();i++){
        int curLen = (int)robotsOrder[i].length();
        if(curLen>maxLen) maxLen=curLen;
    }
    cout<<space*maxLen<<"|";
    for(int i=0;i<robotsOrder.size();i++){
        cout<<robotsOrder[i] << '|';
    }
    cout << endl;
    for(int i=0;i<robotsOrder.size();i++){
        cout<<space*(maxLen-robotsOrder[i].length()) <<robotsOrder[i] <<"|";
        auto line = structure.at(robotsOrder[i]);
        for(int j=0;j<line.size();j++){
            cout << line[j] <<"|";
        }
        cout<<endl;
    }

}