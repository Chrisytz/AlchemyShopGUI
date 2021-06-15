#include "Label.h"
#include <QGuiApplication>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include "Game.h"
#include "Potion.h"

extern Game * game;

int Label::count = 0;
int Label::count2 = 0;


Label::Label(int og_x, int og_y, QPixmap image, int id) {
    this -> id = id;
    this -> og_x = og_x;
    this -> og_y = og_y;
    this -> image = image;

    setOffset(og_x, og_y);
    setPixmap(image);
}

Label::Label(int og_x, int og_y, QPixmap image) {
    this -> og_x = og_x;
    this -> og_y = og_y;
    this -> image = image;

    setOffset(og_x, og_y);
    setPixmap(image);

    id = count++;

}

void Label::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event -> button() == Qt::LeftButton) {
        Label *img = new Label(og_x, og_y, image, id);
        img -> setPixmap(image);
        img -> setOffset(og_x,og_y);
        count2++;
        game -> scene -> addItem(img);

        game -> ingList[count2 - 1] = img;

    }
}

void Label::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    int posx = event -> scenePos().x();
    int posy = event -> scenePos().y();

    setOffset(posx-32, posy-32);
}

void Label::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    string temp = "nothing is made";


    qDebug() << id << "count: " << count2;
    int posx = event -> scenePos().x();
    int posy = event -> scenePos().y();


    if ((posx < 178 || posx > 534 || posy < 140 || posy > 520) || (posx > 470 && posx < 534  && posy > 456 && posy < 520)) {
        game -> scene -> removeItem(game->lableList[game->ingList[count2 - 1]->getId()]);
        game -> lableList[game->ingList[count2-1]->getId()] = game -> ingList[count2-1];

        count2--;
    }


    if (count2 == 2) {
        for (int i = 0; i < 10; i++) {
            if ((game->ingList[0]->getId() == game->potionList[i]->getBaseIngredient1() && game->ingList[1]->getId() == game->potionList[i]->getBaseIngredient2()) ||
                (game->ingList[0]->getId() == game->potionList[i]->getBaseIngredient2() && game->ingList[1]->getId() == game->potionList[i]->getBaseIngredient1())) {

                game -> scene -> addItem(game->potionList[i]);
                break;

            }
        }
        if (game->ingList[0]->getId() == game->ingList[1]->getId()) {
            game -> scene -> removeItem(game->lableList[game->ingList[0]->getId()]);
            game -> scene -> removeItem(game->ingList[0]);
            game -> lableList[game->ingList[0]->getId()] = game -> ingList[1];
        }
        else {
            game -> scene -> removeItem(game->lableList[game->ingList[0]->getId()]);
            game -> scene -> removeItem(game->lableList[game->ingList[1]->getId()]);
            game -> lableList[game->ingList[0]->getId()] = game -> ingList[0];
            game -> lableList[game->ingList[1]->getId()] = game -> ingList[1];
        }


        count2 = 0;
        cout << temp << endl;
    }

}

int Label::getId()
{
    return id;
}