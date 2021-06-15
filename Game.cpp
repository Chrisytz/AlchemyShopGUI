#include "Game.h"
#include "Customer.h"
#include "Popup.h"
#include <fstream>
#include <string>
#include <string.h>
#include "FlexListButton.h"
#include "splashScreen.h"

int Game::points = 3;
int Game::scrollValue = 0;



//saving the game
void Game::savingInformation(Customer *customerOrderingList[]) {
    ofstream MyFile("saveGame.txt");
    // include customers currently in queue and total points
    for (int i = 0; i < 3; i++) {
        MyFile << customerOrderingList[i]->getName() << "\n";
        MyFile << customerOrderingList[i]->getPhone() << "\n";
        MyFile << customerOrderingList[i]->getRequest() << "\n";
        MyFile << customerOrderingList[i]->getId() << "\n";
    }
    MyFile << points << "\n";
    MyFile.close();
}

//list of past customers
void Game::flex(Customer *customerOrderingList[], int index) {
    ofstream outfile;
    outfile.open("flexList.txt", ios_base::app);
    outfile << customerOrderingList[index]->getName() << "\n";
    outfile << customerOrderingList[index]->getPhone() << "\n";
    outfile << customerOrderingList[index]->getRequest() << "\n";
    outfile << customerOrderingList[index]->getIsMad() << "\n";
    outfile << "\n";
}

int countLines() {
    //initializing variables
    int numLines = 0;
    string line;
    ifstream myFile("flexList.txt");
    //counting number of lines
    while (getline(myFile, line)) {
        ++numLines;
    }
    return numLines;
}
void outputCustomer(Customer *c, int xcoor, int ycoor, QGraphicsScene *scene, QGraphicsSimpleTextItem *customerTextList[], int index) {
    string temp = c->toString();
    QString text = QString::fromStdString(temp);

    QGraphicsSimpleTextItem *customerText = new QGraphicsSimpleTextItem();
    customerText -> setText(text);
    scene->addItem(customerText);
    customerText->setPos(xcoor, ycoor);
    customerTextList[index] = customerText;
}
//replacing customer queue with saved information
Customer* Game::getInformation(Customer *customerOrderingList[], int available[], QGraphicsScene *scene, QGraphicsSimpleTextItem *customerTextList[]) {
    cout << "get information running" << endl;
    string tempArray[13];
    //resetting availability list in order to replace customer queue
    for (int i = 0; i < 10; i++) {
        available[i] = i;
    }
    int count = 0;
    string myText;
    //retrieving saved information from last save and quit
    cout << "hello???" << endl;
    ifstream MyReadFile("saveGame.txt");
    while (getline(MyReadFile, myText)) {
        tempArray[count] = myText;
        count++;
    }
    for (int i = 0; i < 13; i++){
        cout << tempArray[i] << endl;
    }

//    for (int i=0; i<3; i++) {
//        cout << customerOrderingList[i]->toString();
//    }
    cout << "why u not wokringggg" << endl;
    //replacing existing customer queue with saved information
    for (int i = 0; i < 3; i++) {
        Customer* customer = new Customer();
        customer->setName(tempArray[((3 * i) + i)]);
        customer->setPhone(tempArray[((3 * i) + i) + 1]);
        customer->setRequest(stoi(tempArray[((3 * i) + i) + 2]));
        customer->setId(stoi(tempArray[((3 * i) + i) + 3]));

        customerOrderingList[i] = customer;
        available[stoi(tempArray[((3 * i) + i) + 3])] = -1;
        cout << "exist? 6" << endl;
        delete customer;
    }

    cout << "how about now" << endl;
    //replacing existing points with saved points
    points = stoi(tempArray[12]);
    for (int i = 0; i < 3; i++) {
        cout << "whya re u bad" << endl;
        cout << customerOrderingList[i]->toString() << endl;
        outputCustomer(customerOrderingList[i], (i*158)+ 30 + (i*20) , 30, scene, customerTextList, i);
    }
    cout << "still wokring??" << endl;
    //return points;
    return *customerOrderingList;
}

string **getFlexList() {
    // creating a 2D array
    string **matrix;
    int numCustomers = countLines() / 5;
    matrix = new string *[numCustomers];
    for (int i = 0; i < numCustomers; i++) {
        matrix[i] = new string[5];
    }

    // putting all lines from flex list into temp array
    string tempArray[numCustomers * 5];
    string line;
    ifstream myFile("flexList.txt");
    int count1 = 0;
    int count2 = 0;
    while (getline(myFile, line)) {
        tempArray[count1] = line;
        count1++;
    }

    // moving all values from tempArray to matrix (a 2d array)
    for (int i = 0; i < numCustomers; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = tempArray[count2];
            count2++;
        }
    }
    return matrix;
}

//sorting flex list alphabetically
void selectSort(string **arr, int length) {
    int pos_max;
    string temp[5];

    for (int i = length - 1; i > 0; i--) {
        //setting first index as temporary largest position
        pos_max = 0;
        for (int j = 1; j <= i; j++) {
            //checks if current position is greater alphabetically
            if (strcmp(arr[j][0].c_str(), arr[pos_max][0].c_str()) < 0) {

                pos_max = j; //if larger found, set new largest
            }
        }
        //swapping element at i (and all the elements that are associated with it in 2d list) with largest element in unsorted section
        for (int k = 0; k < 5; k++) {

            temp[k] = arr[i][k];
            arr[i][k] = arr[pos_max][k];
            arr[pos_max][k] = temp[k];
        }

    }
    //outputting order
    for (int i = length - 1; i >= 0; i--) {
        for (int j = 0; j < 5; j++) {
            cout << arr[i][j] << endl;
        }
    }
}

//outputting flex list at end of game
void outputResults(QGraphicsScene *scene, int scrollNum) {
    string results;
    ifstream MyReadFile("flexList.txt");
    int count = 0;
    while (getline(MyReadFile, results)) {
        string temp = results;
        QString text = QString::fromStdString(temp);

        QGraphicsSimpleTextItem *customerText = new QGraphicsSimpleTextItem();
        customerText -> setText(text);
        scene->addItem(customerText);
        customerText->setPos(0, count+scrollNum);
        count += 20;
    }
    MyReadFile.close();
}

void Game::wheelEvent(QWheelEvent *event) {
    if (points == 0 || points == 10) {
        if (event->angleDelta().y() > 0) {
            scene->clear();
            scrollValue += event->angleDelta().y() / 6;
            outputResults(scene, scrollValue);
        } else {
            scene->clear();
            scrollValue += event->angleDelta().y() / 6;
            outputResults(scene, scrollValue);

        }
    }
}

void delFlexList() {
    fstream ofs;
    ofs.open("flexList.txt", ios::out | ios::trunc);
    ofs.close();
}

//clear contents of save game
void delSaveGame() {
    fstream ofs;
    ofs.open("saveGame.txt", ios::out | ios::trunc);
    ofs.close();
}

// placing customers from the customer list into the ordering list
Customer* Game::generateCustomerOrderingList(Customer *customerOrderingList[], Customer *customerList[], int available[], QGraphicsScene *scene, QGraphicsSimpleTextItem *customerTextList[]) {
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
int Game::giveCustomer(int potion, int customer, Customer *customerOrderingList[]) {
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

    if (points == 0){
        message.popup_lose();

        scene -> clear();
        outputResults(scene, 0);
        FlexListButton *button = new FlexListButton();

    }
    else if (points == 10) {
        message.popup_win();
        scene -> clear();
        outputResults(scene, 0);
        FlexListButton *button = new FlexListButton();

    }
    //update the flex list
    flex(customerOrderingList, customer);

    qDebug() << "points:" << points;
    return points;
}

// updating the customer ordering list after a customer leaves
void Game::updateCustomerOrderingList(Customer *customerOrderingList[], Customer *customerList[], int available[], QGraphicsScene *scene) {
    if (points != 0 && points != 10) {
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
                temp = customerOrderingList[i]->getId();

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

                    outputCustomer(customerOrderingList[j], (j * 158) + 30 + (j * 20), 30, scene, customerTextList, j);
                }
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




    show();

}

//Game::~Game() {
//    qDebug() << "delete working";
//    delete c9;
//    delete c8;
//    delete c7;
//    delete c6;
//    delete c5;
//    delete c4;
//    delete c3;
//    delete c2;
//    delete c1;
//    delete c0;
//
//    delete toothbrush;
//    delete cupcake;
//    delete air;
//    delete electricity;
//    delete love;
//    delete fire;
//    delete wood;
//    delete death;
//    delete life;
//
//    delete p9;
//    delete p8;
//    delete p7;
//    delete p6;
//    delete p5;
//    delete p4;
//    delete p3;
//    delete p2;
//    delete p1;
//    delete p0;
//
//    delete save;
//    delete trash;
//    delete sidebar;
//    delete workspace;
//    delete rect3;
//    delete rect2;
//    delete rect1;
//    delete scene;
//
//}

