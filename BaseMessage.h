//
// Created by ivanm2114 on 11.12.2023.
//

#ifndef OOPPROJECT_MESSAGE_H
#define OOPPROJECT_MESSAGE_H

#endif //OOPPROJECT_MESSAGE_H

#include <string>
#include <iostream>


using namespace std;


class BaseMessage {
public:
    BaseMessage();

    BaseMessage(BaseMessage& initialMessage);

    explicit BaseMessage(const string &string_value);

    explicit BaseMessage(int digit_value);

    BaseMessage(const string &string_value, int digit_value);

    virtual void setValue(int value);

    void setValue(const string& value);

    void setValue( string& string_value,int int_value);

    virtual string getMessage() const;

    string getText() const;

    int getInt() const;

    virtual string getClass() const;

protected:
    string text_value;
    int digit_value=0;
};


BaseMessage::BaseMessage() = default;

BaseMessage::BaseMessage(BaseMessage &initialMessage) {
    text_value = initialMessage.text_value;
    digit_value = initialMessage.digit_value;
}

BaseMessage::BaseMessage(const string &value) {
    text_value = value;
}

BaseMessage::BaseMessage(int value) {
    digit_value = value;
};


BaseMessage::BaseMessage(const string &string_value, int digit_value){
    this->digit_value=digit_value;
    this->text_value = string_value;
}

string BaseMessage::getMessage() const {
    return text_value + std::to_string(digit_value);
};


void BaseMessage::setValue(int value) {
    digit_value = value;
}

void BaseMessage::setValue(const std::string& value) {
    if (!value.empty()) {
        text_value = value;
    } else {
        cout << "This value can`t be set\n";
    }
}

void BaseMessage::setValue(std::string &string_value, int int_value) {
    setValue(int_value);
    setValue(string_value);
}


string BaseMessage::getClass() const {
    return "BaseMessage";
};

int BaseMessage::getInt() const {
    return digit_value;
}


string BaseMessage::getText() const {
    return text_value;
}

