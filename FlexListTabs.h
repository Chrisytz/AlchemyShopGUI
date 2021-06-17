#ifndef ALCHEMYSHOPGUI_FLEXLISTTABS_H
#define ALCHEMYSHOPGUI_FLEXLISTTABS_H

#include <iostream>
#include <QLabel>
#include <QMouseEvent>
#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>

using namespace std;

class FlexListTabs: public QGraphicsRectItem {

private:
    int x;
    int y;
public:
    FlexListTabs(int x, int y);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

#endif //ALCHEMYSHOPGUI_FLEXLISTTABS_H
