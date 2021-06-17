#ifndef ALCHEMYSHOPGUI_SAVE_H
#define ALCHEMYSHOPGUI_SAVE_H

#include <iostream>
#include <QMouseEvent>
#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QAbstractButton>
#include <QPushButton>

class Save: public QGraphicsPixmapItem {
private:
    int x1;
    int y1;
    QPixmap image1;
public:
    Save(int x, int y, QPixmap image);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif //ALCHEMYSHOPGUI_SAVE_H
