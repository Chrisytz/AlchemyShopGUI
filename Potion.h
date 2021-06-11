//
// Created by 16136 on 2021-06-10.
//

#ifndef ALCHEMY_SHOP_TESTING_POTION_H
#define ALCHEMY_SHOP_TESTING_POTION_H
#include <iostream>
#include <QLabel>
#include <QMouseEvent>
#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>

using namespace std;


class Potion: public QGraphicsPixmapItem{
private:
    QPixmap image;
    int ing1;
    int ing2;
    string name;
    int id;
    bool isMade;
    static int count;
public:
    Potion();
    Potion(int ing1, int ing2, string name, bool isMade, QPixmap image);
    void setBaseIngredient1(int ing1);
    void setBaseIngredient2(int ing2);
    void setName(string name);
    void setIsMade(bool isMade);
    int getBaseIngredient1();
    int getBaseIngredient2();
    string getName();
    bool getIsMade();
    int getId();
    string toString();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};
#endif //ALCHEMY_SHOP_TESTING_POTION_H
