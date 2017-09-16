#ifndef TETRISCONTROLLER_H
#define TETRISCONTROLLER_H

#include <QObject>
#include "tetrismodel.h"

class TetrisView;
class TetrisController : public QObject
{
    Q_OBJECT
public:
    explicit TetrisController(TetrisModel *model, TetrisView *view, QObject *parent = nullptr);

public slots:
    void onUpButtonPressed();
    void onDownButtonPressed();
    void onLeftButtonPressed();
    void onRightButtonPressed();
    void onSpaceButtonPressed();
    void onReturnButtonPressed();
    void onStartButtonPressed();
    void onNewGameButtonPressed();
    void onQuitButtonPressed();
private:
    TetrisModel *model_;
    TetrisView *view_;
};

#endif //TETRISCONTROLLER_H
