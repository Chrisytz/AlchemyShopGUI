//
// Created by 16136 on 2021-06-10.
//

#ifndef ALCHEMY_SHOP_TESTING_GAME_H
#define ALCHEMY_SHOP_TESTING_GAME_H
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "Label.h"
#include "Potion.h"
#include "Customer.h"

class Game: public QGraphicsView{
public:
    Game(QWidget *parent=0);
    int giveCustomer(int potion, int customer, Customer *customerOrderingList[], int points);
    void updateCustomerOrderingList(Customer *customerOrderingList[], Customer *customerList[], int available[], QGraphicsScene *scene);

    QGraphicsScene *scene;

    QGraphicsRectItem *rect1;
    QGraphicsRectItem *rect2;
    QGraphicsRectItem *rect3;
    QGraphicsRectItem *workspace;
    QGraphicsRectItem *sidebar;
    QGraphicsRectItem *trash;
    QGraphicsRectItem *save;

    Label *lableList[10];
    Label *life;
    Label *death;
    Label *wood;
    Label *water;
    Label *fire;
    Label *love;
    Label *electricity;
    Label *air;
    Label *cupcake;
    Label *toothbrush;
    Label *ingList[2];


    Potion *potionList[10];
    Potion *p0;
    Potion *p1;
    Potion *p2;
    Potion *p3;
    Potion *p4;
    Potion *p5;
    Potion *p6;
    Potion *p7;
    Potion *p8;
    Potion *p9;

    Customer *c0;
    Customer *c1;
    Customer *c2;
    Customer *c3;
    Customer *c4;
    Customer *c5;
    Customer *c6;
    Customer *c7;
    Customer *c8;
    Customer *c9;
    QGraphicsSimpleTextItem *customerTextList[3];
    Customer *customerOrderingList[3];
    Customer *customerList[10];
    int available[10];

};
#endif //ALCHEMY_SHOP_TESTING_GAME_H
