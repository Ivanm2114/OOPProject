//
// Created by ivanm2114 on 11.12.2023.
//

#ifndef OOPPROJECT_MESSAGE_H
#define OOPPROJECT_MESSAGE_H

#endif //OOPPROJECT_MESSAGE_H

#include "Robot.h"
#include <string>
#include "boost/tuple/tuple.hpp"
#include <iostream>

using namespace std;


template<class V>
class BaseMessage {
public:
    BaseMessage();
    BaseMessage(V data);
    virtual void setData(V data);
    virtual V getMessage() const;
    virtual string getClass() const;
protected:
    V data;
};

template<class K, class V>
class EditRobotMessage: public BaseMessage<V> {
public:
    EditRobotMessage();
    EditRobotMessage(K key, V data);
    void setKey(K key);
    string getClass() const override;
    tuple<K,V> getMessage() const override;

private:
    V data;
    K key;
};

template<class K, class V>
class EditConnectionMessage: public BaseMessage<V> {
public:
    EditConnectionMessage();
    EditConnectionMessage(Robot<K,V>& first, Robot<K,V>& second, string mode);
    EditConnectionMessage(Robot<K,V>& first, Robot<K,V>& second, bool mode);
    void setRobots(Robot<K,V>& first, Robot<K,V>& second);
    void setMode(string mode);
    void setMode(bool mode);
    string getClass() const override;
    tuple<Robot<K,V>&, Robot<K,V>&, bool> getMessage() const override;
private:
    Robot<K,V>& first,second;
    bool mode;
};

template<class V>
BaseMessage<V>::BaseMessage() {};

template<class V>
BaseMessage<V>::BaseMessage(V data) {
    this->data = data;
};

template<class V>
V BaseMessage<V>::getMessage() const {
    return data;
};


template<class V>
void BaseMessage<V>::setData(V data) {
    if(bool(data)){
        this->data=data;
    }
    else{
        cout << "This data can`t be set";
    }
}

template<class V>
string BaseMessage<V>::getClass() const {
    return "BaseMessage";
};


template<class K,class V>
EditRobotMessage<K,V>::EditRobotMessage() {};

template<class K,class V>
EditRobotMessage<K,V>::EditRobotMessage(K key,V data) {
    this->key = key;
    this->data = data;
};



template<class K,class V>
void EditRobotMessage<K,V>::setKey(K key){
    if(bool(key)){
        this->key=key;
    }
    else{
        cout << "This key can`t be set";
    }
};


template<class K,class V>
string EditRobotMessage<K,V>::getClass() const{
    return "EditRobotMessage";
}

template<class K,class V>
tuple<K,V> EditRobotMessage<K,V>::getMessage() const{
    return tuple<K,V>(key,data);
}

template<class K, class V>
EditConnectionMessage<K,V>::EditConnectionMessage(){};

template<class K, class V>
void EditConnectionMessage<K, V>::setRobots(Robot <K, V> &first, Robot <K, V> &second) {
    this->first=first;
    this->second=second;
}

template<class K,class V>
void EditConnectionMessage<K,V>::setMode(bool mode) {
    this->mode = mode;
};

template<class K, class V>
void EditConnectionMessage<K,V>::setMode(std::string mode) {
    if(mode=="connect"){
        setMode(true);
    }
    if(mode=="disconnect"){
        setMode(false);
    }
};

template<class K,class V>
string EditConnectionMessage<K,V>::getClass() const {
    return "EditConnectionMessage";
};


template<class K,class V>
tuple<Robot<K,V>&, Robot<K,V>&, bool> EditConnectionMessage<K,V>::getMessage() const {
    return tuple<Robot<K,V>&, Robot<K,V>&, bool>(first,second,mode);
};

template<class K,class V>
EditConnectionMessage<K,V>::EditConnectionMessage(Robot <K, V> &first, Robot <K, V> &second, bool mode) {
    setRobots(first,second);
    setMode(mode);
}

template<class K,class V>
EditConnectionMessage<K,V>::EditConnectionMessage(Robot <K, V> &first, Robot <K, V> &second, std::string mode) {
    setRobots(first,second);
    setMode(mode);
}

