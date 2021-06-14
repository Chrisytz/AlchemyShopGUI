#ifndef ALCHEMY_SHOP_TESTING_POPUP_H
#define ALCHEMY_SHOP_TESTING_POPUP_H

#include <QMessageBox>
#include <QInputDialog>
#include <QIcon>

class Popup : public QWidget {
public:
    void popup_win();
    void popup_lose();
    bool popup_reload();
    void popup_getPoint();
    void popup_losePoint();
    bool popup_playAgain();
};

#endif //ALCHEMY_SHOP_TESTING_POPUP_H
