#include "Save.h"
#include <QtGui>
#include "Game.h"
#include "splashScreen.h"
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>

extern Game *game;

//constructor
Save::Save(int x, int y, QPixmap image) {
    x1 = x;
    y1 = y;
    image1 = image;

    setOffset(x1, y1);
    setPixmap(image1);
}

//closes game and takes user to splashscreen (resets game)
void Save::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event -> button() == Qt::LeftButton) {
        game->close();
        game = new Game();
        splashScreen *screen = new splashScreen();
        Game::setPoints();
        Label::setCount();
    }
}