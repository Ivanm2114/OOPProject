//
// Created by ivanm2114 on 16.12.2023.
//

#ifndef OOPPROJECT_EDITROBOTMESSAGE_H
#define OOPPROJECT_EDITROBOTMESSAGE_H

#endif //OOPPROJECT_EDITROBOTMESSAGE_H

#include <unordered_map>
#include "BaseMessage.h"

class EditRobotMessage : private BaseMessage {
public:
    EditRobotMessage();

    EditRobotMessage(EditRobotMessage &initialMessage);

    EditRobotMessage(const string &key, int value);

    ~EditRobotMessage();

    void setKey(string key);

    void setValue(int value) override;

    string getKey() const;

    int getValue() const;

    string getClass() const override;

    string getMessage() const override;

};


EditRobotMessage::EditRobotMessage() = default;


EditRobotMessage::EditRobotMessage(const string &key, int value) {
    BaseMessage::setValue(key, value);
};

EditRobotMessage::EditRobotMessage(EditRobotMessage &initialMessage) {
    BaseMessage::setValue(initialMessage.text_value, initialMessage.digit_value);
}

string EditRobotMessage::getClass() const {
    return "EditRobotMessage";
}


string EditRobotMessage::getMessage() const {
    string t;
    t += (string) text_value;
    t += ": ";
    t += to_string(digit_value);
    return t;
}


string EditRobotMessage::getKey() const {
    return BaseMessage::getText();
}


int EditRobotMessage::getValue() const {
    return BaseMessage::getInt();
}

void EditRobotMessage::setValue(int value) {
    BaseMessage::setValue(value);
}

void EditRobotMessage::setKey(std::string key) {
    BaseMessage::setValue(key);
}

EditRobotMessage::~EditRobotMessage() = default;

