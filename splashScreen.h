//
// Created by 16136 on 2021-06-14.
//

#ifndef ALCHEMYSHOPGUI_SPLASHSCREEN_H
#define ALCHEMYSHOPGUI_SPLASHSCREEN_H

#include <iostream>
#include <QMouseEvent>
#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QAbstractButton>
#include <QPushButton>

class splashScreen: public QWidget {
Q_OBJECT

private:
public:
    QPushButton *play;
    QPushButton *load;
    splashScreen();
private slots:
    void onPlayPressed();
    void onLoadPressed();
};
#endif //ALCHEMYSHOPGUI_SPLASHSCREEN_H