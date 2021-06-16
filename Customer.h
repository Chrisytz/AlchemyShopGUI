#include <iostream>
#include <string>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsScene>

using namespace std;

#ifndef ALCHEMY_SHOP_TESTING_CUSTOMER_H
#define ALCHEMY_SHOP_TESTING_CUSTOMER_H

class Customer: public QGraphicsSimpleTextItem {
private:
    string name;
    string phone;
    int request;
    int id;
    bool isMad;
    bool isMade;
    static int count;

public:
    Customer();
    Customer(string, string, int, bool, bool);
    ~Customer();
    string getName();
    string getPhone();
    int getRequest();
    bool getIsMad();
    int getId();
    void setName(string);
    void setPhone(string);
    void setIsMade(bool isMade);
    void setRequest(int);
    void setIsMad(bool);
    bool getIsMade();
    void setId(int);
    string toString();
};

#endif //ALCHEMY_SHOP_TESTING_CUSTOMER_H
