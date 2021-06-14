//
// Created by 16136 on 2021-06-14.
//

#ifndef ALCHEMYSHOPGUI_FLEXLISTBUTTON_H
#define ALCHEMYSHOPGUI_FLEXLISTBUTTON_H
#include <iostream>
#include <QMouseEvent>
#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QAbstractButton>
#include <QPushButton>

class FlexListButton: public QWidget {
Q_OBJECT

private:
public:
    QPushButton *buttonRestart;
    FlexListButton();
private slots:
    void onLeftButtonPressed();
};
#endif //ALCHEMYSHOPGUI_FLEXLISTBUTTON_H
