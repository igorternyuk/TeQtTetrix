#ifndef TETRISFIELD_H
#define TETRISFIELD_H

#include <QtWidgets>
#include <QFrame>
#include <QKeyEvent>
#include <vector>

#include "tetrismodel.h"

class TetrisController;
class TetrisField : public QFrame
{
    Q_OBJECT
public:
    TetrisField(TetrisModel *model, TetrisController *controller, QWidget *parent = nullptr);
    static QColor convertColor(const Color &blockColor);
    static void drawSquare(QPainter &painter, int x, int y, QColor color);
protected:
      void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
      void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
private:
      TetrisModel *model_;
      TetrisController *controller_;
      void drawActivePiece(QPainter &painter);
      void drawField(QPainter &painter);
      void drawTextFromMatrix(QPainter &painter, boolMatrix textMatrix, QColor color);
      void showPause(QPainter &painter, const QColor &color);
      void showGameOver(QPainter &painter, const QColor &color);
};

#endif // TETRISFIELD_H
