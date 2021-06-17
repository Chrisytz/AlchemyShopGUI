#include "FlexListTabs.h"
#include <QGuiApplication>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include "Game.h"
#include "Potion.h"
#include "splashScreen.h"
#include <QGraphicsRectItem>
#include "FlexListButton.h"

extern Game * game;

FlexListTabs::FlexListTabs(int x, int y) {
    this -> x = x;
    this -> y = y;
    setRect(x, y, 246, 26);
}

void FlexListTabs::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    int posx = event -> scenePos().x();
    int posy = event -> scenePos().y();
    FlexListButton *returnButton = new FlexListButton();
    if (event -> button() == Qt::LeftButton) {
        QGraphicsPixmapItem *backgroundChrono = new QGraphicsPixmapItem;
        backgroundChrono -> setPixmap(QPixmap("C:\\Users\\16136\\CLionProjects\\AlchemyShopGUI\\UI Flex List Tab 1.png"));
        QGraphicsPixmapItem *backgroundChronoBorder = new QGraphicsPixmapItem;
        backgroundChronoBorder -> setPixmap(QPixmap("C:\\Users\\16136\\CLionProjects\\AlchemyShopGUI\\UI Flex List Tab 1 Border.png"));
        QGraphicsPixmapItem *backgroundSorted = new QGraphicsPixmapItem;
        backgroundSorted -> setPixmap(QPixmap("C:\\Users\\16136\\CLionProjects\\AlchemyShopGUI\\UI Flex List Tab 2 (1).png"));
        QGraphicsPixmapItem *backgroundSortedBorder = new QGraphicsPixmapItem;
        backgroundSortedBorder -> setPixmap(QPixmap("C:\\Users\\16136\\CLionProjects\\AlchemyShopGUI\\UI Flex List Tab 2 Border.png"));
        game->scene->addItem(backgroundChrono);
        if (posx > 31 && posx < 277 && posy > 27 && posy < 53) {
            qDebug() << "tab chrono button pressed";
            game->chronoPressed = true;
            game->scene->addItem(backgroundChrono);
            game->outputResults(game->scene, game->scrollValue);
            game->scene->addItem(backgroundChronoBorder);
            FlexListButton *returnButton = new FlexListButton();
        }
        if (posx > 278 && posx < 524 && posy > 27 && posy <53) {
            qDebug() << "tab alpha button pressed";
            game->chronoPressed = false;
            game->scene->addItem(backgroundSorted);
            game->selectSort(game->getFlexList(),game->countLines() / 5, game->scene, game->scrollValue);
            game->scene->addItem(backgroundSortedBorder);
            FlexListButton *returnButton = new FlexListButton();
        }
    }
}