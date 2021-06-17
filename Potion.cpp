#include <iostream>
#include "Potion.h"
#include <sstream>
#include <QGuiApplication>
#include <QGraphicsSceneMouseEvent>
#include "Game.h"
#include "Customer.h"

extern Game *game;

using namespace std;

//constructor
Potion::Potion() {
    ing1 = -1;
    ing2 = -1;
    name = "empty";
    isMade = false;
}

//count used to set potion id
int Potion::count = 0;

//constructors with parameters
Potion::Potion(int ing1, int ing2, string name, bool isMade, QPixmap image) {
    this -> ing1 = ing1;
    this -> ing2 = ing2;
    this -> name = name;
    this -> isMade = isMade;
    this -> image = image;

    //setting position and image of each potion
    setOffset(324, 298);
    setPixmap(image);
    id = count++;
}

//destructor
Potion::~Potion() {

}

//detects left click on potions
void Potion::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event -> button() == Qt::LeftButton) {

    }
}

//detects drag of potion
void Potion::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    //mouse position
    int posx = event -> scenePos().x();
    int posy = event -> scenePos().y();
    //constantly setting the position of the potion to the position of the cursor
    setOffset(posx-32, posy-32);
}

//detects when potion is released
void Potion::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    //mouse position
    int posx = event -> scenePos().x();
    int posy = event -> scenePos().y();

    //detects which customer (customer box) the potion is dragged to
    if (posy > 20 && posy < 120) {
        if (posx > 20 && posx < 178) {
            //removes potion from scene
            game -> scene -> removeItem(this);
            //checks if correct potion given
            game -> giveCustomer(this->getId(), 0, game->customerOrderingList);
            //updates customerOrderingList and list of available customers
            game -> updateCustomerOrderingList(game->customerOrderingList, game->customerList, game->available, game->scene);
            //positions potion to center of workspace (resets for when appears in future)
            this -> setOffset(324, 298);
        } else if (posx > 198 && posx < 356) {
            game -> scene -> removeItem(this);
            game -> giveCustomer(this->getId(), 1, game->customerOrderingList);
            game -> updateCustomerOrderingList(game->customerOrderingList, game->customerList, game->available, game->scene);
            this -> setOffset(324, 298);
        } else if (posx > 376 && posx < 534) {
            game -> scene -> removeItem(this);
            game -> giveCustomer(this->getId(), 2, game->customerOrderingList);
            game -> updateCustomerOrderingList(game->customerOrderingList, game->customerList, game->available, game->scene);
            this -> setOffset(324, 298);
        }
    // if potion is dragged elsewhere, remove it from the scene
    } else if (posx > 470 && posx < 534  && posy > 456 && posy < 520) {
        game -> scene -> removeItem(this);
        this -> setOffset(324, 298);
    }
    //saves customer queue to save game file
    game -> savingInformation(game->customerOrderingList);
}

void Potion::setIsMade(bool isMade) {
    this -> isMade = isMade;
}

//accessor methods
int Potion::getBaseIngredient1() {
    return ing1;
}

int Potion::getBaseIngredient2() {
    return ing2;
}

string Potion::getName(){
    return name;
}

bool Potion::getIsMade() {
    return isMade;
}

int Potion::getId() {
    return id;
}