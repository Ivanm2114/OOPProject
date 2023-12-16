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

string star = "*";
string space = " ";

string operator*(const string &s, unsigned int n) {
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

    ~Robot();

    void setName(const string &new_name);

    void setParameters(unordered_map<string, int> &new_parameters);

    void setParameter(string key, int value);

    void deleteParameter(string key);

    void editConnectionWith(Robot *second, bool mode);

    void sendMessage(Robot *target, BaseMessage &message, Robot *origin);

    void sendMassMessage(BaseMessage &message);

    void applyChanges(EditRobotMessage &message);

    void printTotalStructure() const;

    auto getParameters() const;

    auto getName() const;

    const BaseMessage *getLastMessage() const;

    bool isConnected(Robot *robot) const;

    bool isConnected(string &robotsName) const;

    int operator[](const string &key) const;

    void operator+(Robot &second);

    void operator-(Robot &second);

    vector<const Robot *> getConnectedRobots() const;

    string getClass() const;

    void deleteFromNet();

private:
    string name;
    unordered_map<string, int> parameters;
    vector<Robot *> connectedRobots;

    BaseMessage *lastReceivedMessage= nullptr;

    int isInVector(Robot *robot, vector<Robot *> robotList) const;

    void copy_to(unordered_map<string, int> &origin, unordered_map<string, int> &destination);

    bool transferMessage(Robot *origin, Robot *transmitter, Robot *target,
                         BaseMessage &message, vector<Robot *> route);

    void copy_to(vector<Robot *> &origin, vector<Robot *> &destination);

    void addConnections(vector<string> *robotsNames, unordered_map<string, vector<string>> *structure, int n = 0) const;

    void innerSendMassMessage(BaseMessage &message, Robot *origin, vector<Robot *> *sentMessages);

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
    return parameters;
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
        cout << "Action is impossible. Robots are already connected or disconnected\n";
    }
}

bool Robot::transferMessage(Robot *origin, Robot *transmitter, Robot *target,
                            BaseMessage &message, vector<Robot *> route) {
    bool flag = false;
    if (this != target) {
        auto t = isInVector(target, connectedRobots);
        if (t >= 0 and connectedRobots[t]->getLastMessage() != &message) {
            route.push_back(this);
            flag = connectedRobots[t]->transferMessage(origin, this, target, message, route);
        } else {
            int i = 0;
            do {
                if (!connectedRobots.empty() and connectedRobots[i] != origin and connectedRobots[i] != transmitter and
                    isInVector(connectedRobots[i], route) == -1) {
                    route.push_back(this);
                    flag = connectedRobots[i]->transferMessage(origin, this, target, message,
                                                               route);
                }
                i++;
            } while (i < connectedRobots.size() and !flag);
            return flag;
        }
    } else {
        cout << "Robot " + this->name + " recieved message from robot " + origin->name +
                ". The message: " + message.getMessage() + "\n";
        lastReceivedMessage = &message;
        return true;
    }
    return flag;
}

const BaseMessage *Robot::getLastMessage() const {
    return lastReceivedMessage;
}

void Robot::sendMessage(Robot *target, BaseMessage &message, Robot *origin = nullptr) {
    vector<Robot *> route;
    bool flag = false;
    if (origin == nullptr) origin = this;
    if (target != this) {
        flag = transferMessage(origin, this, target, message, route);
    } else {
        cout << "You don`t need to send message its the same robot\n";
    }
    if (!flag) {
        cout << "Couldn`t send the message\n";
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
    return isInVector(robot, connectedRobots) > -1;
}

bool Robot::isConnected(std::string &robotsName) const {
    for (int i = 0; i < connectedRobots.size(); i++) {
        if (connectedRobots[i]->getName() == robotsName) return true;
    }
    return false;
}

void Robot::addConnections(vector<std::string> *robotsNames, unordered_map<std::string, vector<std::string>> *structure,
                           int n) const {
    vector<string> connections;
    string spaces;
    for (int i = 0; i < robotsNames->size(); i++) {
        if (isConnected((*robotsNames)[i])) {
            spaces = space * ((int) (*robotsNames)[i].length() - 1);
            connections.push_back(star + spaces);
            spaces = space * ((int) name.length() - 1);
            structure->at((*robotsNames)[i]).push_back(star + spaces);
        } else {
            spaces = space * ((int) (*robotsNames)[i].length());
            connections.push_back(spaces);
            spaces = space * ((int) name.length());
            structure->at((*robotsNames)[i]).push_back(spaces);
        }
    }
    spaces = space * (int) (name.length() - 1);
    connections.push_back(star + spaces);
    structure->insert({name, connections});
    robotsNames->push_back(name);
    ++n;
    for (int i = 0; i < connectedRobots.size(); i++) {
        if (structure->find(connectedRobots[i]->getName()) == structure->end()) {
            connectedRobots[i]->addConnections(robotsNames, structure, n);
        }
    }


}

void Robot::printTotalStructure() const {
    unordered_map<string, vector<string>> structure;
    vector<std::string> robotsOrder;
    int maxLen = -1;
    addConnections(&robotsOrder, &structure);
    for (int i = 0; i < robotsOrder.size(); i++) {
        int curLen = (int) robotsOrder[i].length();
        if (curLen > maxLen) maxLen = curLen;
    }
    cout << space * maxLen << "|";
    for (int i = 0; i < robotsOrder.size(); i++) {
        cout << robotsOrder[i] << '|';
    }
    cout << endl;
    for (int i = 0; i < robotsOrder.size(); i++) {
        cout << space * (maxLen - robotsOrder[i].length()) << robotsOrder[i] << "|";
        auto line = structure.at(robotsOrder[i]);
        for (int j = 0; j < line.size(); j++) {
            cout << line[j] << "|";
        }
        cout << endl;
    }

}

int Robot::operator[](const string &key) const {
    if (parameters.find(key) != parameters.end())
        return parameters.at(key);
    return 0;
}

void Robot::operator+(Robot &second) {
    editConnectionWith(&second, true);
    second.editConnectionWith(this, true);
}

void Robot::operator-(Robot &second) {
    editConnectionWith(&second, false);
    second.editConnectionWith(this, false);
}

vector<const Robot *> Robot::getConnectedRobots() const {
    vector<const Robot *> t;
    for (int i = 0; i < connectedRobots.size(); i++) {
        t.push_back(connectedRobots[i]);
    }
    return t;
}

void Robot::sendMassMessage(BaseMessage &message) {
    vector<Robot *> sentMessages;
    sentMessages.push_back(this);
    innerSendMassMessage(message, this, &sentMessages);
}

void Robot::innerSendMassMessage(BaseMessage &message, Robot *origin, vector<Robot *> *sentMessages) {
    for (int i = 0; i < connectedRobots.size(); ++i) {
        if(isInVector(connectedRobots[i],*sentMessages)==-1){
        sendMessage(connectedRobots[i], message, origin);
        sentMessages->push_back(connectedRobots[i]);
        connectedRobots[i]->innerSendMassMessage(message, origin,sentMessages);
        }
    }

}

void Robot::deleteFromNet() {
    for(int i=0;i<connectedRobots.size();i++){
        for(int j=i+1;j<connectedRobots.size();j++){
            if(i!=j and !connectedRobots[i]->isConnected(connectedRobots[j])){
                *connectedRobots[i]+*connectedRobots[j];
            }
        }
    }
    auto initialSize = connectedRobots.size();
    for(int i=0;i<initialSize;i++){
        *this-*connectedRobots[0];
    }
}

Robot::~Robot() {
    deleteFromNet();
}

string Robot::getClass() const {
    return "Robot";
}

void Robot::deleteParameter(string key) {
    if(parameters.find(key)!=parameters.end()){
        parameters.erase(key);
    }

}
