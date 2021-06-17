#include "Label.h"
#include <QGuiApplication>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include "Game.h"
#include "splashScreen.h"

extern Game *game;

int Label::count = 0; //used to give each Label(base ingredients) their id
int Label::count2 = 0; //used to check if two base ingredients have been dragged onto the workspace

//constructor (setting the id, position and image of each base ingredient, without increasing count)
Label::Label(int og_x, int og_y, QPixmap image, int id) {
    this->id = id;
    this->og_x = og_x;
    this->og_y = og_y;
    this->image = image;

    //setting position and image
    setOffset(og_x, og_y);
    setPixmap(image);
}
//constructor (setting position and image)
Label::Label(int og_x, int og_y, QPixmap image) {
    this->og_x = og_x;
    this->og_y = og_y;
    this->image = image;

    //setting position and image
    setOffset(og_x, og_y);
    setPixmap(image);

    id = count++;

}

//destructor
Label::~Label() {

}

//when mouse is pressed
void Label::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    //getting mouse position
    int posx = event->scenePos().x();
    int posy = event->scenePos().y();
    //on left button click
    if (event->button() == Qt::LeftButton) {
        //making a new image to replace the old image in the same position
        Label *img = new Label(og_x, og_y, image, id);
        img->setPixmap(image);
        img->setOffset(og_x, og_y);
        //increasing count2 (a base ingredient has been added to the scene)
        count2++;
        game->scene->addItem(img);
        //adding the clicked ingredient into a ingredient list array to later be checked to see which potion is made
        game->ingList[count2 - 1] = img;

        //detects if mouse presses in save button area (closes current game and takes to splash screen to begin new one)
        if (posx > 406 && posx < 470 && posy > 456 && posy < 520) {
            game->close();
            game = new Game();
            splashScreen *screen = new splashScreen();
            Game::setPoints();
            Label::setCount();
        }
    }
}

//drag functionality for click and drag
void Label::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    int posx = event->scenePos().x();
    int posy = event->scenePos().y();

    //constantly sets Label(base ingredient) position to be the same as the cursor position
    setOffset(posx - 32, posy - 32);
}

//drop functionality for drag and drop
void Label::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    int posx = event->scenePos().x();
    int posy = event->scenePos().y();

    //ingredient is removed if dragged outside of workspace
    if ((posx < 178 || posx > 534 || posy < 140 || posy > 520) ||
        (posx > 470 && posx < 534 && posy > 456 && posy < 520)) {
        game->scene->removeItem(game->lableList[game->ingList[count2 - 1]->getId()]);
        //resets lableList with removed ingredient
        game->lableList[game->ingList[count2 - 1]->getId()] = game->ingList[count2 - 1];
        //decreases count of ingredients in workspace
        count2--;
    }
    // if two ingredients have been dragged onto the workspace
    if (count2 == 2) {
        //iterating through potionList to determine which (if any) potion the two base ingredients create
        for (int i = 0; i < 10; i++) {
            if ((game->ingList[0]->getId() == game->potionList[i]->getBaseIngredient1() &&
                 game->ingList[1]->getId() == game->potionList[i]->getBaseIngredient2()) ||
                (game->ingList[0]->getId() == game->potionList[i]->getBaseIngredient2() &&
                 game->ingList[1]->getId() == game->potionList[i]->getBaseIngredient1())) {
                //if one is created add the potion to the scene
                game->scene->addItem(game->potionList[i]);
                break;
            }
        }
        //removes ingredients from workspace (replaced with potion that was just added)
        //if the two ingredients are the same remove both from the workspace but only reset lableList once
        if (game->ingList[0]->getId() == game->ingList[1]->getId()) {
            game->scene->removeItem(game->lableList[game->ingList[0]->getId()]);
            game->scene->removeItem(game->ingList[0]);
            game->lableList[game->ingList[0]->getId()] = game->ingList[1];

        }
        //if ingredients are different, remove both from workspace and reset lableList for both ingredients
        else {
            game->scene->removeItem(game->lableList[game->ingList[0]->getId()]);
            game->scene->removeItem(game->lableList[game->ingList[1]->getId()]);
            game->lableList[game->ingList[0]->getId()] = game->ingList[0];
            game->lableList[game->ingList[1]->getId()] = game->ingList[1];
        }
        //reset count2 to 0 as no base ingredients are in the workspace
        count2 = 0;
    }

}

//getting the id of a base ingredient
int Label::getId() {
    return id;
}