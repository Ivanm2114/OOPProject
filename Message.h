//
// Created by ivanm2114 on 11.12.2023.
//

#ifndef OOPPROJECT_MESSAGE_H
#define OOPPROJECT_MESSAGE_H

#endif //OOPPROJECT_MESSAGE_H

#include "Robot.h"
#include <string>
#include "boost/tuple/tuple.hpp"
using namespace std;


template<class V>
class BaseMessage {
public:
    BaseMessage();
    BaseMessage(V data);
    void getMessage() const;
    virtual void getClass() const;
protected:
    V data;
};

template<class V, class K>
class EditRobotMessage: public BaseMessage<V> {
public:
    EditRobotMessage();
    EditRobotMessage(V data, K key);
    bool checkData(V data);
    void setData(V data);
    void getClass() const override;
    tuple<V,K> getMessage();

private:
    V data;
    K key;
};

template<class V>
class EditConnectionMessage: public BaseMessage<V> {
public:
    EditConnectionMessage();
    EditConnectionMessage(Robot first, Robot Second, string mode);
    void setRobots();
    void getClass() const override;

};