#include "Game.h"
#include "Customer.h"
#include "Popup.h"
#include <fstream>
#include <string>
#include <string.h>

void outputCustomer(Customer *c, int xcoor, int ycoor, QGraphicsScene *scene, QGraphicsSimpleTextItem *customerTextList[], int index) {
    string temp = c->toString();
    QString text = QString::fromStdString(temp);

    QGraphicsSimpleTextItem *customerText = new QGraphicsSimpleTextItem();
    customerText -> setText(text);
    scene->addItem(customerText);
    customerText->setPos(xcoor, ycoor);
    customerTextList[index] = customerText;
}

// placing customers from the customer list into the ordering list
Customer *generateCustomerOrderingList(Customer *customerOrderingList[], Customer *customerList[], int available[], QGraphicsScene *scene, QGraphicsSimpleTextItem *customerTextList[]) {
    //same as above, rng generator that catches if a customer is already in queue
    for (int i = 0; i < 3; i++) {
        int x;
        int y;
        do {
            y = rand() % 10;
            x = available[y];
            available[y] = -1;
        } while (x == -1);

        customerOrderingList[i] = customerList[x];
        outputCustomer(customerOrderingList[i], (i*158)+ 30 + (i*20) , 30, scene, customerTextList, i);

    }
    return *customerOrderingList;
}

//checks if potion made is the right potion that the customer ordered
int Game::giveCustomer(int potion, int customer, Customer *customerOrderingList[], int points) {
    //if the potion the customer ordered is the potion delivered, increase the points and set isMade to true
    Popup message;
    if (customerOrderingList[customer]->getRequest() == potion) {
        message.popup_getPoint();
        customerOrderingList[customer]->setIsMade(true);
        points++;

        //if the potion the customer ordered is not the potion delivered, decrease the points and set isMad to true
    } else {
        message.popup_losePoint();
        customerOrderingList[customer]->setIsMad(true);
        points--;

    }
    //update the flex list
    //flex(customerOrderingList, customer);

    return points;
}

// updating the customer ordering list after a customer leaves
void Game::updateCustomerOrderingList(Customer *customerOrderingList[], Customer *customerList[], int available[], QGraphicsScene *scene) {
    for (int i = 0; i < 3; i++) {
        int temp;
        if (customerOrderingList[i]->getIsMad() == true || customerOrderingList[i]->getIsMade() == true) {

            int x;
            int y;
            //loops until index of available customer is randomly selected
            do {
                //random index is selected
                y = rand() % 10;
                //id of customer at that index is taken from availability list
                x = available[y];
                //availability list at index is set to -1 (customer is not available)
                available[y] = -1;
            } while (x == -1);

            //resets customer status
            customerOrderingList[i]->setIsMade(false);
            customerOrderingList[i]->setIsMad(false);

            //setting temp to the id of the customer that just left
            temp = customerOrderingList[i] -> getId();

            //a customer from customerList is selected and put into customerOrderingList
            customerOrderingList[i] = customerList[x];

            // after customer leaves, customer becomes available
            available[temp] = temp;
            scene->removeItem(customerTextList[0]);
            scene->removeItem(customerTextList[1]);
            scene->removeItem(customerTextList[2]);
            delete customerTextList[0];
            delete customerTextList[1];
            delete customerTextList[2];

            qDebug() << "A new customer arrived! Here is your customer list: ";
            for (int j = 0; j < 3; j++) {

                outputCustomer(customerOrderingList[j], (j*158)+ 30 + (j*20) , 30, scene, customerTextList, j);
            }

        }
    }

    //return *customerOrderingList;
}

Game::Game(QWidget *parent) {
    srand(time(0));
    scene = new QGraphicsScene(0, 0, 554, 540);

    setScene(scene); //this is needed to visual the scene since Game is a QGraphicsView Widget?? it can be used to visualize scenes
    rect1 = new QGraphicsRectItem(20,20,158,100);
    rect2 = new QGraphicsRectItem(198,20,158,100);
    rect3 = new QGraphicsRectItem(376,20,158,100);
    workspace = new QGraphicsRectItem(20,140,514,380);
    sidebar = new QGraphicsRectItem(20,140,158,380);
    trash = new QGraphicsRectItem(470,456,64,64);
    save = new QGraphicsRectItem(406,456,64,64);

    scene -> addItem(rect1);
    scene -> addItem(rect2);
    scene -> addItem(rect3);
    scene -> addItem(workspace);
    scene -> addItem(sidebar);
    scene -> addItem(trash);
    scene -> addItem(save);

    potionList;
    p0 = new Potion(0, 3, "Fish potion", false, QPixmap("C:\\Users\\16136\\CLionProjects\\Alchemy-Shop-Testing\\Potions\\Fish Potion.png"));
    p1 = new Potion(0, 1, "Aging potion", false, QPixmap("C:\\Users\\16136\\CLionProjects\\Alchemy-Shop-Testing\\Potions\\Aging Potion.png"));
    p2 = new Potion(1, 8, "Poison potion", false, QPixmap("C:\\Users\\16136\\CLionProjects\\Alchemy-Shop-Testing\\Potions\\poison potion.png"));
    p3 = new Potion(2, 4, "Arson potion", false, QPixmap("C:\\Users\\16136\\CLionProjects\\Alchemy-Shop-Testing\\Potions\\arson potion.png"));
    p4 = new Potion(2, 7, "Knockout potion", false, QPixmap("C:\\Users\\16136\\CLionProjects\\Alchemy-Shop-Testing\\Potions\\Knockout Potion.png"));
    p5 = new Potion(3, 9, "Clean teeth potion", false, QPixmap("C:\\Users\\16136\\CLionProjects\\Alchemy-Shop-Testing\\Potions\\Clean Teeth Potion.png"));
    p6 = new Potion(4, 8, "Eternal hunger potion", false, QPixmap("C:\\Users\\16136\\CLionProjects\\Alchemy-Shop-Testing\\Potions\\bread potion.png"));
    p7 = new Potion(5, 6, "Computer science skills potion", false, QPixmap("C:\\Users\\16136\\CLionProjects\\Alchemy-Shop-Testing\\Potions\\Computer Science Skills Potion.png"));
    p8 = new Potion(5, 7, "Levitation potion", false, QPixmap("C:\\Users\\16136\\CLionProjects\\Alchemy-Shop-Testing\\Potions\\Levitation Potion.png"));
    p9 = new Potion(6, 9, "Auto-scrubbing potion", false, QPixmap("C:\\Users\\16136\\CLionProjects\\Alchemy-Shop-Testing\\Potions\\Auto-Scrubbing Potion.png"));

    potionList[0] = p0;
    potionList[1] = p1;
    potionList[2] = p2;
    potionList[3] = p3;
    potionList[4] = p4;
    potionList[5] = p5;
    potionList[6] = p6;
    potionList[7] = p7;
    potionList[8] = p8;
    potionList[9] = p9;

    ingList;

    life = new Label(30, 150, QPixmap("C:\\Users\\16136\\CLionProjects\\Alchemy-Shop-Testing\\life.png"));
    death = new Label(104, 150, QPixmap("C:\\Users\\16136\\CLionProjects\\Alchemy-Shop-Testing\\death.png"));
    wood = new Label(30, 224, QPixmap("C:\\Users\\16136\\CLionProjects\\Alchemy-Shop-Testing\\wood (1).png"));
    water = new Label(104, 224, QPixmap("C:\\Users\\16136\\CLionProjects\\Alchemy-Shop-Testing\\Water SBG.png"));
    fire = new Label(30, 298,
                            QPixmap("C:\\Users\\16136\\CLionProjects\\Alchemy-Shop-Testing\\smol fire clone.png"));
    love = new Label(104, 298, QPixmap("C:\\Users\\16136\\CLionProjects\\Alchemy-Shop-Testing\\Love SBG.png"));
    electricity = new Label(30, 372,
                                   QPixmap("C:\\Users\\16136\\CLionProjects\\Alchemy-Shop-Testing\\Electricity SBG.png"));
    air = new Label(104, 372, QPixmap("C:\\Users\\16136\\CLionProjects\\Alchemy-Shop-Testing\\Air SBG.png"));
    cupcake = new Label(30, 446, QPixmap("C:\\Users\\16136\\CLionProjects\\Alchemy-Shop-Testing\\cupcake.png"));
    toothbrush = new Label(104, 446,
                                  QPixmap("C:\\Users\\16136\\CLionProjects\\Alchemy-Shop-Testing\\Toothbrush SBG.png"));
    lableList[0] = life;
    lableList[1] = death;
    lableList[2] = wood;
    lableList[3] = water;
    lableList[4] = fire;
    lableList[5] = love;
    lableList[6] = electricity;
    lableList[7] = air;
    lableList[8] = cupcake;
    lableList[9] = toothbrush;

    scene->addItem(life);
    scene->addItem(death);
    scene->addItem(wood);
    scene->addItem(water);
    scene->addItem(fire);
    scene->addItem(love);
    scene->addItem(electricity);
    scene->addItem(air);
    scene->addItem(cupcake);
    scene->addItem(toothbrush);


    c0 = new Customer("Bob", "333-666-9999", rand() % 10, false, false);
    c1 = new Customer("Arys Borderlands", "123-456-7891", rand() % 10, false, false);
    c2 = new Customer("Chibueze Teaman", "545-777-6868", rand() % 10, false, false);
    c3 = new Customer("Chromium Steele", "242-424-2424", rand() % 10, false, false);
    c4 = new Customer("Alfredo Gusteau", "613-232-4444", rand() % 10, false, false);
    c5 = new Customer("Maurice Shoob", "676-937-3829", rand() % 10, false, false);
    c6 = new Customer("Cruella de Vil", "437-234-5948", rand() % 10, false, false);
    c7 = new Customer("Ambrosia Wonton", "816-908-0000", rand() % 10, false, false);
    c8 = new Customer("Demi Burgeress", "169-242-7092", rand() % 10, false, false);
    c9 = new Customer("Fatimah Sweeney", "666-666-1004", rand() % 10, false, false);

    customerList;
    customerOrderingList;
    for (int i = 0; i < 10; i++) {
        available[i] = i;
    }
    customerList[0] = c0;
    customerList[1] = c1;
    customerList[2] = c2;
    customerList[3] = c3;
    customerList[4] = c4;
    customerList[5] = c5;
    customerList[6] = c6;
    customerList[7] = c7;
    customerList[8] = c8;
    customerList[9] = c9;


    generateCustomerOrderingList(customerOrderingList, customerList, available, scene, customerTextList);

    //c9 -> toString();
//    QGraphicsTextItem *customerText = scene->addText(customerList[0] -> getName());
//    customerText->setPos(30, 30);
//    QGraphicsTextItem *customerText = scene->addText("Testing Customer info");
//    customerText->setPos(30, 30);
//    scene -> removeItem(customerText);
//    delete customerText;

    show();

}

