#include "Popup.h"

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

bool Popup::popup_reload() {
    switch( QMessageBox::question(
            this,
            tr("Reload?"),
            tr("Your last game's progress was saved! Would you like to reload your saved game? If not, a new game will be started."),

            QMessageBox::Yes |
            QMessageBox::No,

            QMessageBox::No ) )
    {
        case QMessageBox::Yes:
            qDebug( "yes" );
            return true;
        case QMessageBox::No:
            qDebug( "no" );
            return false;
        default:
            qDebug( "close" );
            return false;
    }
}

bool Popup::popup_playAgain() {
    switch( QMessageBox::question(
            this,
            tr("Play Again"),
            tr("Would you like to play again?"),

            QMessageBox::Yes |
            QMessageBox::No,

            QMessageBox::No ) )
    {
        case QMessageBox::Yes:
            qDebug( "yes" );
            return true;
        case QMessageBox::No:
            qDebug( "no" );
            return false;
        default:
            qDebug( "close" );
            return false;
    }
}

