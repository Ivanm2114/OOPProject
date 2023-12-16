//
// Created by ivanm2114 on 16.12.2023.
//

#ifndef EDITCONNECTIONMESSAGE_H
#define EDITCONNECTIONMESSAGE_H

#endif //EDITCONNECTIONMESSAGE_H

#include "Robot.h"


class EditConnectionMessage {
public:
    EditConnectionMessage();

    EditConnectionMessage(Robot *first, Robot *second, const string &mode);

    EditConnectionMessage(Robot *first, Robot *second, bool mode);

    ~EditConnectionMessage();

    void setValue(Robot *first, Robot *second);

    void setValue(const string &mode);

    void setValue(bool mode);

    string getClass() const;

    Robot *getFirst() const;

    Robot *getSecond() const;

    void apply();

    bool getMode() const;

    string getMessage() const;

private:
    Robot *second = nullptr;
    Robot *first = nullptr;
    bool mode = true;
};

EditConnectionMessage::EditConnectionMessage() = default;

EditConnectionMessage::EditConnectionMessage(Robot *first, Robot *second, bool mode = true) {
    this->first = first;
    this->second = second;
    setValue(mode);
}


EditConnectionMessage::EditConnectionMessage(Robot *first, Robot *second, const string &mode = "connected") {
    this->first = first;
    this->second = second;
    setValue(mode);
}


void EditConnectionMessage::setValue(Robot *first, Robot *second) {
    this->first = first;
    this->second = second;
}


void EditConnectionMessage::setValue(bool mode) {
    this->mode = mode;
}


void EditConnectionMessage::setValue(const string &mode) {
    if (mode == "connect") {
        setValue(true);
    }
    if (mode == "disconnect") {
        setValue(false);
    }
}


string EditConnectionMessage::getClass() const {
    return "EditConnectionMessage";
}


Robot *EditConnectionMessage::getFirst() const {
    return first;
}


Robot *EditConnectionMessage::getSecond() const {
    return second;
}


bool EditConnectionMessage::getMode() const {
    return mode;
}


string EditConnectionMessage::getMessage() const {
    string t;
    if (!mode) {
        t += "dis";
    }
    t += "connect ";
    t += first->getName();
    t += " and ";
    t += second->getName();
    return t;
};

void EditConnectionMessage::apply() {
    if (first != nullptr and second != nullptr) {
        first->editConnectionWith(second, mode);
        second->editConnectionWith(first, mode);
    }

}

EditConnectionMessage::~EditConnectionMessage() = default;
