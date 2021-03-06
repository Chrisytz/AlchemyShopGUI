#include "Customer.h"
#include <sstream>
#include <QGuiApplication>
#include "Game.h"

extern Game * game;

//static variable declaration
int Customer::count = 0;

//constructor
Customer::Customer() {
    name = "Bob";
    phone = "000-000-0000";
    request = 0;
    isMad = false;
    isMade = false;
}

//parameterized constructor
Customer::Customer(string n, string p, int r, bool m, bool me) {
    setName(n);
    setPhone(p);
    setRequest(r);
    setIsMad(m);
    setIsMade(me);
    id = count++;

}
//deconstructor
Customer::~Customer() {
    //qDebug() << "customer deleted";
}
//accessor methods
string Customer::getName() {
    return name;
}
string Customer::getPhone() {
    return phone;
}
int Customer::getRequest() {
    return request;
}
bool Customer::getIsMad() {
    return isMad;
}
bool Customer::getIsMade() {
    return isMade;
}
int Customer::getId() {
    return id;
}
//mutator methods
void Customer::setName(string n) {
    name = n;
}
void Customer::setPhone(string p) {
    if (p.length() == 12 && p[3] == '-' && p[7] == '-') {
        phone = p;
    }
    else {
        phone = "000-000-0000";
    }
}
void Customer::setRequest(int r) {
    if (0 <= r && r <= 9) {
        request = r;
    }
    else {
        request = 0;
    }
}
void Customer::setIsMad(bool m) {
    isMad = m;
}
void Customer::setIsMade(bool isMade) {
    this -> isMade = isMade;
}
void Customer::setId(int i) {
    id = i;
}
//convert to string
string Customer::toString() {
    string potionName[] = {"Fish Potion", "Aging Potion", "Poison Potion", "Arson Potion", "Knockout Potion", "Clean Teeth Potion", "Hunger Potion", "CS Skills Potion", "Levitation Potion", "Scrubbing Potion"};
    stringstream ss;

    ss << "Name: ";
    ss << name;
    ss << "\nOrder: ";
    ss << potionName[request];
    ss << "\nContact: ";
    ss << phone;


    return ss.str();
}