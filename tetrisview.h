#ifndef TETRISVIEW_H
#define TETRISVIEW_H

#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

#include "tetrismodel.h"
#include "tetriscontroller.h"
#include "tetrisfield.h"
#include "lcdwidget.h"

class TetrisView : public QMainWindow
{
    Q_OBJECT
public:
    explicit TetrisView(QMainWindow *parent = nullptr);
public slots:
    void update();
    void drawNextPiece();
    void showInfoAboutTetris() const;
protected:
private:
   const QString WINDOW_TITLE = QString::fromStdString("Tetris");
   const QString INFO_ABOUT_TETRIS = QString::fromStdString("The object of the game is to stack pieces dropped from the top of the"
        " playing area so that they fill entire rows at the bottom of the playing area."
        " When a row is filled, all the blocks on that row are removed, the player earns a number of points,"
        " and the pieces above are moved down to occupy that row."
        " If more than one row is filled, the blocks on each row are removed, and the player earns extra points."
        " The Left cursor key moves the current piece one space to the left, the Right cursor key moves it one "
        " space to the right, the Up cursor key rotates the piece counter-clockwise by 90 degrees,"
        " and the Down cursor key rotates the piece clockwise by 90 degrees. Press 'Enter' to drop active piece. "
        " Space key starts and pauses the game. Press N for starting new game and Q to quit application.\n    "
        " This clone of classical Tetrix game was wtitten by Ternyuk I.O. in 2017, Jan 29.");
   static const int WINDOW_WIDTH_WITHOUT_FIELD = 180;
   static const int WINDOW_HEIGHT_WITHOUT_FIELD = 17;
   static const int SPACING_BETWEEN_BUTTONS = 10;
   static const int VERTICAL_SPACER_INDEX = -1;
   static const int DIGITAL_DISPLAY_WIDTH = 150;
   static const int DIGITAL_DISPLAY_HEIGHT = 40;
   static const int DIGITAL_DISPLAY_DIGITS_NUMBER = 7;
   TetrisModel *model_;
   TetrisController *controller_;
   LCDWidget *scoreLCD_;
   LCDWidget *levelLCD_;
   LCDWidget *linesLCD_;
   QPushButton *newGameButton;
   QPushButton *startButton;
   QPushButton *pauseButton;
   QPushButton *aboutButton;
   QPushButton *exitButton;
   TetrisField *field_;
   QLabel *nextPieceLabel_;
   QLabel* createLabel(const QString &text);
};

#endif // TETRISVIEW_H
