#ifndef TETRISMODEL_H
#define TETRISMODEL_H

#include <QObject>
#include <QDebug>
#include <QBasicTimer>
#include <vector>
#include "tetramino.h"

class TetrisModel : public QObject
{
    Q_OBJECT

public:
    explicit TetrisModel(QObject *parent = nullptr, int fieldWidth = DEFAULT_FIELD_WIDTH,
                         int fieldHeight = DEFAULT_FIELD_HEIGHT);
    virtual ~TetrisModel();
    int getFieldWidth() const;
    int getFieldHeight() const;
    int getNumBlocksInPiece() const;
    int getCurrentLevel() const;
    Tetramino getActivePiece() const;
    Tetramino getNextPiece() const;
    Color getColorAt(int x, int y) const;
    bool isGameStarted() const;
    bool isGameOver() const;
    boolMatrix getGameOverTextCode() const;
    bool isGamePaused() const;
    boolMatrix getPauseTextCode() const;
signals:
   void updateView();
   void showNextPiece();
   void scoreChanged(int score);
   void levelChanged(int level);
   void linesRemovedChanged(int numLines);
public slots:
   void start();
   void pause();
   void newGame();
   void moveLeft();
   void moveRight();
   void rotateLeft();
   void rotateRight();
   void dropDown();

protected:
   void timerEvent(QTimerEvent*) Q_DECL_OVERRIDE;
private:
   static const int DEFAULT_FIELD_WIDTH = 23;
   static const int DEFAULT_FIELD_HEIGHT = 36;
   const int NUM_BLOCKS_IN_PIECE = 4;
   const int BASE_TIMER_TIMEOUT_TIME = 1200;
   const int NUM_DROPPED_PIECES_FOR_NEXT_LEVEL = 25;
   int fieldWidth_;
   int fieldHeight_;
   int score_;
   int speed_;
   int level_;
   int numLinesRemoved_;
   int numPiecesDropped_;
   bool isGameOver_;
   bool isGameStarted_;
   bool isGamePaused_;
   Matrix gameField_;                // 2D Vector represents game field
   Tetramino activePiece_;
   Tetramino nextPiece_;
   QBasicTimer timer_;
   TetrisModel(TetrisModel&);        // Private copy constructor
   void reset();                     // Prepares next game
   int  timeOutTime();               // Changes timer timeout time according to current game level
   void oneLineDown();
   bool isCrossGround() const;       // checks field for overfill
   bool isTouchGround() const;       // returns true if active piece touches field bottom
   bool isTouchWall(const Tetramino &tetramino, Direction dir) const; // returns true if active piece touches field walls
   bool hasCollisions(const Tetramino &tetramino) const;   // Collision checking during rotation
   void uniteWithDroppedPieces();    // Unites current piece with allready dropped pieces
   void clearField();                // Clears the game field
   void fillFieldBottom();           // Creates field bottom
   void prepareAfterPieceDropping(const int &dropHeight); // awards player for dropped pieces
   void removeFullLines();           // Removes filled lines
   int getScoreForRemovedLines(const int &numRemovedLines) const; // Returns points for removed lines
   void newPiece();                  // Forms new piece
};

#endif // TETRISMODEL_H
