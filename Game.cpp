#include "Game.h"
#include "Customer.h"
#include "Popup.h"
#include <fstream>
#include <string>
#include <string.h>
#include "FlexListButton.h"
#include <string>
#include "Save.h"
#include "FlexListTabs.h"

int Game::points = 3;
int Game::scrollValue = 0;

// when window closes, objects are deleted
void Game::closeEvent(QCloseEvent *event) {

    delete p0;
    delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete p5;
    delete p6;
    delete p7;
    delete p8;
    delete p9;


    delete c0;
    delete c1;
    delete c2;
    delete c3;
    delete c4;
    delete c5;
    delete c6;
    delete c7;
    delete c8;
    delete c9;
//    delete customer1;
//    delete customer2;
//    delete customer3;

//    delete life;
//    delete life;
//    delete death;
//    delete wood;
//    delete water;
//    delete fire;
//    delete love;
//    delete electricity;
//    delete air;
//    delete cupcake;
//    delete toothbrush;
//
//     delete scene;

}

//saving the game (putting information into save game file)
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

//list of past customers (puts information into flex list file)
void Game::flex(Customer *customerOrderingList[], int index) {
    ofstream outfile;
    outfile.open("flexList.txt", ios_base::app);
    outfile << customerOrderingList[index]->getName() << "\n";
    outfile << customerOrderingList[index]->getPhone() << "\n";
    outfile << customerOrderingList[index]->getRequest() << "\n";
    outfile << customerOrderingList[index]->getIsMad() << "\n";
    outfile << "\n";
    outfile.close();
}

//getting number of lines in flex list
int Game::countLines() {
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

//outputs customer information in slot
void outputCustomer(Customer *c, int xcoor, int ycoor, QGraphicsScene *scene, QGraphicsSimpleTextItem *customerTextList[], int index) {
    string temp = c->toString();
    QString text = QString::fromStdString(temp);
    //adding text onto scene
    QGraphicsSimpleTextItem *customerText = new QGraphicsSimpleTextItem();
    customerText -> setText(text);
    scene->addItem(customerText);
    customerText->setPos(xcoor, ycoor);
    customerTextList[index] = customerText;
}

//replacing and outputting customer queue with saved information
Customer* Game:: getInformation(Customer *customerOrderingList[], int available[], QGraphicsScene *scene, QGraphicsSimpleTextItem *customerTextList[]) {
    string tempArray[13];
    //resetting availability list in order to replace customer queue
    for (int i = 0; i < 10; i++) {
        available[i] = i;
    }
    int count = 0;
    string myText;
    //retrieving saved information from last save and quit
    ifstream MyReadFile("saveGame.txt");
    while (getline(MyReadFile, myText)) {
        tempArray[count] = myText;
        count++;
    }

    //creating customer objects with information from save game file
    Customer *customer1 = new Customer();
    Customer *customer2 = new Customer();
    Customer *customer3 = new Customer();

    customer1->setName(tempArray[0]);
    customer1->setPhone(tempArray[1]);
    customer1->setRequest(stoi(tempArray[2]));
    customer1->setId(stoi(tempArray[3]));
    customer2->setName(tempArray[4]);
    customer2->setPhone(tempArray[5]);
    customer2->setRequest(stoi(tempArray[6]));
    customer2->setId(stoi(tempArray[7]));
    customer3->setName(tempArray[8]);
    customer3->setPhone(tempArray[9]);
    customer3->setRequest(stoi(tempArray[10]));
    customer3->setId(stoi(tempArray[11]));

    customerOrderingList[0] = customer1;
    customerOrderingList[1] = customer2;
    customerOrderingList[2] = customer3;

    //setting outputted customers to unavailable
    available[stoi(tempArray[3])] = -1;
    available[stoi(tempArray[7])] = -1;
    available[stoi(tempArray[11])] = -1;

    //replacing existing points with saved points
    points = stoi(tempArray[12]);

    //outputting the three customers into slots
    for (int i = 0; i < 3; i++) {
        outputCustomer(customerOrderingList[i], (i*158)+ 30 + (i*20) , 30, scene, customerTextList, i);
    }

    //outputs current point tally
    outputPoints();

    return *customerOrderingList;
}

//getting information from flex list and returning in 2d string array
string **Game::getFlexList() {
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

//sorting and outputting flex list alphabetically
void Game::selectSort(string **arr, int length, QGraphicsScene *scene, int scrollNum) {
    int pos_max;
    string temp[5];
    int count = 0;

    for (int i = length - 1; i > 0; i--) {
        //setting first index as temporary largest position
        pos_max = 0;
        for (int j = 1; j <= i; j++) {
            //checking if current position is greater alphabetically
            if (strcmp(arr[j][0].c_str(), arr[pos_max][0].c_str()) < 0) {
                pos_max = j; //if larger found, setting new largest
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
            string temp;
            //changing potion id to potion name
            if (j == 2) {
                temp = potionList[stoi(arr[i][j])]->getName();
            }
            //changing isMad bool to if customer was satisfied
            else if (j == 3) {
                int temp1;
                temp1 = stoi(arr[i][j]);
                if (temp1 == 1) {
                    temp = "Customer unhappy";
                }
                else {
                    temp = "Customer happy";
                }
            }
            else {
                temp = arr[i][j];
            }
            //adding to scene
            QString text = QString::fromStdString(temp);
            QGraphicsSimpleTextItem *customerText = new QGraphicsSimpleTextItem();
            customerText -> setText(text);
            scene->addItem(customerText);
            customerText->setPos(35, count+scrollNum);
            //to account for spacing out text (to avoid overlap)
            count += 20;
        }
    }
}

//outputting flex list at end of game
void Game::outputResults(QGraphicsScene *scene, int scrollNum) {
    string results;
    ifstream MyReadFile("flexList.txt");
    int count = 0;
    //reads from flex list file
    while (getline(MyReadFile, results)) {
        string temp;
        //checks if getline is at third line (potion request) of each customer information block to change from id to name
        if (((count/20)-2)%5==0) {
            int temp1 = stoi(results);
            temp = potionList[temp1]->getName();
        }
        //checks if getline is at fourth line (isMad) of each customer info block to change from bool to text
        else if (((count/20)-3)%5==0) {
            int temp2 = stoi(results);
            if (temp2 == 1) {
                temp = "Customer unhappy";
            }
            else {
                temp = "Customer happy";
            }
        }
        else {
            temp = results;
        }
        //adding to scene
        QString text = QString::fromStdString(temp);

        QGraphicsSimpleTextItem *customerText = new QGraphicsSimpleTextItem();
        customerText -> setText(text);
        scene->addItem(customerText);
        customerText->setPos(35, count+scrollNum);
        count += 20;
    }
    MyReadFile.close();
}

//clears contents of flex list
void Game::delFlexList() {
    fstream ofs;
    ofs.open("flexList.txt", ios::out | ios::trunc);
    ofs.close();
}

//clear contents of save game
void Game::delSaveGame() {
    fstream ofs;
    ofs.open("saveGame.txt", ios::out | ios::trunc);
    ofs.close();
}

//controls scrolling of flex list
void Game::wheelEvent(QWheelEvent *event) {
    //creating background objects for flex list output
    QGraphicsPixmapItem *backgroundChrono = new QGraphicsPixmapItem;
    backgroundChrono -> setPixmap(QPixmap("C:\\Users\\16136\\CLionProjects\\AlchemyShopGUI\\UI Flex List Tab 1.png"));
    QGraphicsPixmapItem *backgroundSorted = new QGraphicsPixmapItem;
    backgroundSorted -> setPixmap(QPixmap("C:\\Users\\16136\\CLionProjects\\AlchemyShopGUI\\UI Flex List Tab 2 (1).png"));
    QGraphicsPixmapItem *backgroundChronoBorder = new QGraphicsPixmapItem;
    backgroundChronoBorder -> setPixmap(QPixmap("C:\\Users\\16136\\CLionProjects\\AlchemyShopGUI\\UI Flex List Tab 1 Border.png"));\
    QGraphicsPixmapItem *backgroundSortedBorder = new QGraphicsPixmapItem;
    backgroundSortedBorder -> setPixmap(QPixmap("C:\\Users\\16136\\CLionProjects\\AlchemyShopGUI\\UI Flex List Tab 2 Border.png"));
    //only allow scrolling when user wins or loses (scrolling only on the flex list scene)
    if (points == 0 || points == 10) {
        //everytime user scrolls, scene is cleared
        scene->clear();
        chronoTab = new FlexListTabs(31, 27);//delete
        scene->addItem(chronoTab);
        alphaTab = new FlexListTabs(278, 27);//delete
        scene->addItem(alphaTab);
        //checks which tab is pressed to output correct sorting method
        if (chronoPressed == true) {
            scene->addItem(backgroundChrono);
            outputResults(scene, scrollValue);
            scene->addItem(backgroundChronoBorder);
        } else {
            scene->addItem(backgroundSorted);
            selectSort(getFlexList(), countLines() / 5, scene, scrollValue);
            scene->addItem(backgroundSortedBorder);
        }
        //return button takes user back to the splash screen
        FlexListButton *returnButton = new FlexListButton();
        //how much one scroll adjusts the screen upwards or downwards
        scrollValue += event->angleDelta().y() / 6;
    }
}

// placing customers from the customer list into the ordering list
Customer* Game::generateCustomerOrderingList(Customer *customerOrderingList[], Customer *customerList[], int available[], QGraphicsScene *scene, QGraphicsSimpleTextItem *customerTextList[]) {
    //rng generator that catches if a customer is already in queue (same as updateCustomerOrderingList)
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
    //outputs original point tally
    outputPoints();
    return *customerOrderingList;
}

//outputs point tally
void Game::outputPoints() {
    QString p = QString::fromStdString("Points: "+to_string(points));
    pointText = new QGraphicsSimpleTextItem();
    pointText -> setText(p);
    scene->removeItem(pointText);
    scene->addItem(pointText);
    pointText->setPos(477, 150);
}

//checks if potion made is the right potion that the customer ordered, checks if user won/lost
int Game::giveCustomer(int potion, int customer, Customer *customerOrderingList[]) {
    //if the potion the customer ordered is the potion delivered, increase the points and set isMade to true
    Popup message;
    //creating background objects
    QGraphicsPixmapItem *backgroundChrono = new QGraphicsPixmapItem;
    backgroundChrono -> setPixmap(QPixmap("C:\\Users\\16136\\CLionProjects\\AlchemyShopGUI\\UI Flex List Tab 1.png"));
    QGraphicsPixmapItem *backgroundChronoBorder = new QGraphicsPixmapItem;
    backgroundChronoBorder -> setPixmap(QPixmap("C:\\Users\\16136\\CLionProjects\\AlchemyShopGUI\\UI Flex List Tab 1 Border.png"));
    //checks if potion matches customer request
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

    //replaces old point tally with new point tally
    scene->removeItem(pointText);
    delete pointText;
    outputPoints();

    //checks for win or loss
    if (points == 0 || points == 10){
        //win/lose pop up messages
        if (points == 0) {
            message.popup_lose();
        }
        else {
            message.popup_win();
        }
        // if won or lost clear the scene and print flex list
        scene -> clear();
        // invisible graphicsItems to allow user to click on each tab
        chronoTab = new FlexListTabs(31,27);//delete
        scene -> addItem(chronoTab);
        alphaTab = new FlexListTabs(278,27);//delete
        scene -> addItem(alphaTab);

        // add background and output flex list to scene
        scene->addItem(backgroundChrono);
        outputResults(scene, scrollValue);
        scene->addItem(backgroundChronoBorder);

        //generates a button every time the scene resets
        FlexListButton *button = new FlexListButton();
    }
    //update the flex list
    flex(customerOrderingList, customer);

    return points;
}

// updating the customer ordering list after a customer leaves
void Game::updateCustomerOrderingList(Customer *customerOrderingList[], Customer *customerList[], int available[], QGraphicsScene *scene) {
    if (points != 0 && points != 10) {
        for (int i = 0; i < 3; i++) {
            int temp;
            //if customer leaves, replaces with new customer
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

                //old customer queue is removed from scene
                scene->removeItem(customerTextList[0]);
                scene->removeItem(customerTextList[1]);
                scene->removeItem(customerTextList[2]);
                delete customerTextList[0];
                delete customerTextList[1];
                delete customerTextList[2];

                //new customer queue added to scene
                //qDebug() << "A new customer arrived! Here is your customer list: ";
                for (int j = 0; j < 3; j++) {
                    outputCustomer(customerOrderingList[j], (j * 158) + 30 + (j * 20), 30, scene, customerTextList, j);
                }
            }
        }
    }
}

//constructor for UI (runs when game is called)
Game::Game(QWidget *parent) {
    srand(time(0)); //randomizing random
    scene = new QGraphicsScene(0, 0, 554, 540);
    setScene(scene); //this is needed to visual the scene since Game is a QGraphicsView Widget, it can be used to visualize scenes

    //todo: add trash can and correct save picture to scene
    //creating workspace background and adding to scene
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem;
    background -> setPixmap(QPixmap("C:\\Users\\16136\\CLionProjects\\AlchemyShopGUI\\UI Main Workspace.png"));
    scene -> addItem(background);

    //creating potions
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

    //assigning potions into array
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

    //creating ingredients
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

    //assigning ingredients into array
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

    //adding ingredients to scene
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

    //creating customer objects
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

    //setting availability list to default
    for (int i = 0; i < 10; i++) {
        available[i] = i;
    }
    //assigning customers into array
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

    //creating save button and adding to scene
    Save *saving = new Save(406, 456, QPixmap("C:\\Users\\16136\\CLionProjects\\AlchemyShopGUI\\Save.png"));
    scene->addItem(saving);

    QGraphicsPixmapItem *trash = new QGraphicsPixmapItem;
    trash -> setPixmap(QPixmap("C:\\Users\\16136\\CLionProjects\\AlchemyShopGUI\\Trash.png"));
    trash -> setOffset(470,456);
    scene -> addItem(trash);

    //shows scene
    show();

}