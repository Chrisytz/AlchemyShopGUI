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
    QPushButton *instructions;
    splashScreen();
private slots:
    void onPlayPressed();
    void onLoadPressed();
    void onInstrPressed();
};
#endif //ALCHEMYSHOPGUI_SPLASHSCREEN_H
