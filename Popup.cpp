#include "Popup.h"

//pop ups that provide information
void Popup::popup_win() {
    QMessageBox::information(
            this,
            tr("Winner"),
            tr("Great job! Your alchemy shop has a stellar reputation. You win!"));

}

void Popup::popup_lose() {
    QMessageBox::information(
            this,
            tr("Defeat"),
            tr("Sorry, you ran out of points. Better luck next time!"));
}

void Popup::popup_getPoint() {
    QMessageBox::information(
            this,
            tr("Nice Job!"),
            tr("You have successfully given the potion to the customer! You gained 1 point."));
}

void Popup::popup_losePoint() {
    QMessageBox::information(
            this,
            tr("Nice Try!"),
            tr("The customer was unhappy with the potion they received. You lost 1 point."));
}

void Popup::popup_instr() {
    QMessageBox::information(
            this,
            tr("Game Instructions"),
            tr("1. Welcome to your Alchemy Shop! Click play to start a new game or load to continue from a past game.\n"
               "2. Drag two ingredients (located in the sidebar on the left) into the workspace (box located on the right) to see if they combine to make a potion!\n"
               "3. If they do, the potion will appear in the workspace. Otherwise, the workspace will be reset and you can try again.\n"
               "4. If you’d like to delete an ingredient or a potion at any point, drag it to the trash can in the bottom right corner of the workspace.\n"
               "5. Once you have created a potion that you are happy with, drag it to one of the three customers at the top of the screen to fulfill their request.\n"
               "6. If you give them the correct potion, they leave happy and you gain a point! If not, they will be very disappointed and you will lose a point.\n"
               "7. You start with 3 points and win the game once you have a total of 10! But be careful because if your total gets to 0, you lose the game!\n"
               "8. Upon winning or losing, you will be shown a list with all your past customers and their information so that you can show off your success and reflect on your failures. Click restart once you’ve finished reminiscing and would like to go back to the starting screen.\n"
               "9. If you’d like to save your progress and quit the game at any point, click the save button in the bottom right corner of the workspace and you’ll be taken back to the starting screen.\n"
               "10. Have fun playing!"));
}

