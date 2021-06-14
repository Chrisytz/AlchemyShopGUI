#include <iostream>
#include "Potion.h"
#include <QGraphicsView>
#include <sstream>
#include <QGuiApplication>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "Game.h"
#include "Customer.h"

extern Game *game;

using namespace std;

Potion::Potion() {
    ing1 = -1;
    ing2 = -1;
    name = "empty";
    isMade = false;
}

int Potion::count = 0;

Potion::Potion(int ing1, int ing2, string name, bool isMade, QPixmap image) {
    this -> ing1 = ing1;
    this -> ing2 = ing2;
    this -> name = name;
    this -> isMade = isMade;
    this -> image = image;

    setOffset(324, 298);
    setPixmap(image);
    id = count++;
}
void Potion::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event -> button() == Qt::LeftButton) {

    }
}
void Potion::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    int posx = event -> scenePos().x();
    int posy = event -> scenePos().y();

    setOffset(posx-32, posy-32);
}

void Potion::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    int posx = event -> scenePos().x();
    int posy = event -> scenePos().y();


    if (posy > 20 && posy < 120) {
        if (posx > 20 && posx < 178) {
            qDebug() << "to customer 1";
            game -> scene -> removeItem(this);
            game -> giveCustomer(this->getId(), 0, game->customerOrderingList);
            game -> updateCustomerOrderingList(game->customerOrderingList, game->customerList, game->available, game->scene);
            this -> setOffset(324, 298);
        } else if (posx > 198 && posx < 356) {
            qDebug() << "to customer 2";
            game -> scene -> removeItem(this);
            game -> giveCustomer(this->getId(), 1, game->customerOrderingList);
            game -> updateCustomerOrderingList(game->customerOrderingList, game->customerList, game->available, game->scene);
            this -> setOffset(324, 298);
        } else if (posx > 376 && posx < 534) {
            qDebug() << "to customer 3";
            game -> scene -> removeItem(this);
            game -> giveCustomer(this->getId(), 2, game->customerOrderingList);
            game -> updateCustomerOrderingList(game->customerOrderingList, game->customerList, game->available, game->scene);
            this -> setOffset(324, 298);
        }
    }
    game -> savingInformation(game->customerOrderingList);
}

void Potion::setBaseIngredient1(int ing1) {
    if (0 <= ing1 && ing1 <= 9) {
        this -> ing1 = ing1;
    }
}

void Potion::setBaseIngredient2(int ing2) {
    if (0 <= ing2 && ing2 <= 9) {
        this -> ing2 = ing2;
    }
}

void Potion::setName(string name) {
    this -> name = name;
}

void Potion::setIsMade(bool isMade) {
    this -> isMade = isMade;
}

int Potion::getBaseIngredient1() {
    return ing1;
}

int Potion::getBaseIngredient2() {
    return ing2;
}

string Potion::getName(){
    return name;
}

bool Potion::getIsMade() {
    return isMade;
}

int Potion::getId() {
    return id;
}

string Potion::toString() {
    stringstream ss;

    ss << "name: ";
    ss << name;
    ss << "; ingredient1: ";
    ss << ing1;
    ss << "; ingredient2: ";
    ss << ing2;
    ss << "; order number: ";
    ss << id;
    ss << "; has been made?: ";
    ss << isMade;

    return ss.str();
}
