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

public:
    FlexListTabs(int x, int y);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif //ALCHEMYSHOPGUI_FLEXLISTTABS_H
