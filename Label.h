#ifndef ALCHEMY_SHOP_TESTING_LABEL_H
#define ALCHEMY_SHOP_TESTING_LABEL_H

#include <iostream>
#include <QLabel>
#include <QMouseEvent>
#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>

using namespace std;

class Label: public QGraphicsPixmapItem {

private:
    int og_x;
    int og_y;
    QPixmap image;
    int id;
    static int count;
    static int count2;

public:
    Label(int og_x, int og_y, QPixmap image);
    Label(int og_x, int og_y, QPixmap image, int id);
    ~Label();
    int getId();
    static void setCount() { count = 0; };


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif //ALCHEMY_SHOP_TESTING_LABEL_H
