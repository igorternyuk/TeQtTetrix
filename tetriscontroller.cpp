#include "tetriscontroller.h"
#include "tetrisview.h"

TetrisController::TetrisController(TetrisModel *model, TetrisView *view, QObject *parent) :
    QObject(parent), model_(model), view_(view)
{
}

void TetrisController::onUpButtonPressed()
{
    model_->rotateLeft();
}

void TetrisController::onDownButtonPressed()
{
    model_->rotateRight();
}

void TetrisController::onLeftButtonPressed()
{
    model_->moveLeft();
}

void TetrisController::onRightButtonPressed()
{
    model_->moveRight();
}

void TetrisController::onSpaceButtonPressed()
{
    if(!model_->isGameStarted()) {
        model_->start();
        return;
    }
    if(!model_->isGameOver()) {

        if(model_->isGamePaused())
            model_->start();
        else
            model_->pause();
    }
}

void TetrisController::onReturnButtonPressed()
{
    model_->dropDown();
}

void TetrisController::onStartButtonPressed()
{
    model_->start();
}

void TetrisController::onNewGameButtonPressed()
{
    model_->newGame();
}

void TetrisController::onQuitButtonPressed()
{
    view_->close();
}
