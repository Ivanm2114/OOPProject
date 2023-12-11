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
    void setData(V data);
    V getMessage() const;
    virtual string getClass() const;
protected:
    V data;
};

template<class K, class V>
class EditRobotMessage: public BaseMessage<V> {
public:
    EditRobotMessage();
    EditRobotMessage(K key, V data);
    void setData(V data);
    void setKey(K key);
    string getClass() const override;
    tuple<K,V> getMessage() const;

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
    void setRobots(Robot<V,K>& first, Robot<V,K>& Second);
    void setMode(string mode);
    void setMode(bool mode);
    string getClass() const override;
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
void EditRobotMessage<K,V>::setData(V data){
    if(bool(data)){
        this->data=data;
    }
    else{
        cout << "This data can`t be set";
    }
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
tuple<K,V> EditRobotMessage<K,V>::getMessage() const{}