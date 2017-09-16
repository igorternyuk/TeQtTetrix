#include <QPainter>

#include "tetrisfield.h"
#include "tetriscontroller.h"


TetrisField::TetrisField(TetrisModel *model, TetrisController *controller, QWidget *parent) :
    QFrame(parent), model_(model), controller_(controller)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    QPalette pal;
    pal.setColor(QPalette::Background, Qt::black);
    this->setPalette(pal);
    this->setAutoFillBackground(true);
    setFocusPolicy(Qt::StrongFocus);
    setFixedSize(Block::getBlockSize() * model_->getFieldWidth() + 2,
                 Block::getBlockSize() * model_->getFieldHeight() + 2);
}

void TetrisField::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    QPainter painter(this);
    drawField(painter);
    if(!model_->isGameOver())
       drawActivePiece(painter);
    else
       showGameOver(painter, Qt::white);
    if(model_->isGamePaused())
       showPause(painter, Qt::white);
}

void TetrisField::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
    case Qt::Key_Up :
    case Qt::Key_W :
        controller_->onUpButtonPressed();
        break;
    case Qt::Key_Down :
    case Qt::Key_S :
        controller_->onDownButtonPressed();
        break;
    case Qt::Key_Left :
    case Qt::Key_A :
        controller_->onLeftButtonPressed();
        break;
    case Qt::Key_Right :
    case Qt::Key_D :
        controller_->onRightButtonPressed();
        break;
    case Qt::Key_Space :
    case Qt::Key_P :
        controller_->onSpaceButtonPressed();
        break;
    case Qt::Key_Return :
        controller_->onReturnButtonPressed();
        break;
    case Qt::Key_N :
        controller_->onNewGameButtonPressed();
        break;
    case Qt::Key_Q :
        controller_->onQuitButtonPressed();
        break;
    default:
        QFrame::keyPressEvent(event);
        break;
    }
}

QColor TetrisField::convertColor(const Color &blockColor)
{
    QColor color;
    switch(blockColor){
        case BLACK :
            color = Qt::black;
            break;
        case RED :
            color = Qt::red;
            break;
        case GREEN :
            color = Qt::green;
            break;
        case BLUE :
            color = Qt::blue;
            break;
        case YELLOW :
            color = Qt::yellow;
            break;
        case CYAN :
            color = Qt::cyan;
            break;
        case MAGENTA :
            color = Qt::magenta; break;
        case DARKGREEN :
            color = Qt::darkGreen; break;
        case WHITE :
            color = Qt::white;
    }
    return color;
}

void TetrisField::drawActivePiece(QPainter &painter)
{
    QRect rect = contentsRect();
    QColor color = convertColor(model_->getActivePiece().getColor());
    for(Block block : model_->getActivePiece().getBlocks()) {
            drawSquare(painter, rect.left() + block.getX() * Block::getBlockSize(),
                       rect.top() + block.getY() * Block::getBlockSize(), color);
        }
}

void TetrisField::drawField(QPainter &painter)
{
    QRect rect = contentsRect();
    QColor color(Qt::gray);
    painter.setPen(color.dark());
    // Here we draw field grid
    for (int x = 0; x < model_->getFieldHeight(); ++x) {
        painter.drawLine(rect.left(),
                         rect.top() + x * Block::getBlockSize(),
                         rect.left() + model_->getFieldWidth() * Block::getBlockSize(),
                         rect.top() + x * Block::getBlockSize());
    }
    for (int y = 0; y < model_->getFieldHeight(); ++y) {
        painter.drawLine(rect.left() + y * Block::getBlockSize(),
                         rect.top(),
                         rect.left() + y * Block::getBlockSize(),
                         rect.top() + model_->getFieldHeight() * Block::getBlockSize());
    }
    // Here we draw field
    for (int x = 0; x < model_->getFieldWidth(); ++x) {
        for (int y = 0; y < model_->getFieldHeight(); ++y) {
            if(model_->getColorAt(x, y) > 0)
            drawSquare(painter, rect.left() + x * Block::getBlockSize(),
                       rect.top() + y * Block::getBlockSize(), convertColor(model_->getColorAt(x, y)));
        }
    }
}

void TetrisField::drawTextFromMatrix(QPainter &painter, boolMatrix textMatrix, QColor color)
{
    static const int TOP_OFFSET = 230; // Text offset from field top bound
    QRect rect = contentsRect();
    for (int y = 0; y < int(textMatrix.size()); ++y) {
        for (int x = 0; x < int(textMatrix[0].size()); ++x) {
            if(textMatrix[y][x]) {
                drawSquare(painter, rect.left() + x * Block::getBlockSize(),
                           rect.top() + TOP_OFFSET + y * Block::getBlockSize(), color);
            }
        }
    }
}

void TetrisField::drawSquare(QPainter &painter, int x, int y, QColor color)
{
     static const int SPACE_FOR_BLOCK_CONTOUR = 2;
     painter.fillRect(x + 1, y + 1, Block::getBlockSize() - SPACE_FOR_BLOCK_CONTOUR,
                      Block::getBlockSize() - SPACE_FOR_BLOCK_CONTOUR, color);
     painter.setPen(color.light());
     painter.drawLine(x, y + Block::getBlockSize() - 1, x, y);
     painter.drawLine(x, y, x + Block::getBlockSize() - 1, y);
     painter.setPen(color.dark());
     painter.drawLine(x + 1, y + Block::getBlockSize() - 1, x + Block::getBlockSize() - 1, y + Block::getBlockSize() - 1);
     painter.drawLine(x + Block::getBlockSize() - 1, y + Block::getBlockSize() - 1, x + Block::getBlockSize() - 1, y + 1);
}

void TetrisField::showPause(QPainter &painter, const QColor &color)
{
    drawTextFromMatrix(painter, model_->getPauseTextCode(), color);
}

void TetrisField::showGameOver(QPainter &painter, const QColor &color)
{
    drawTextFromMatrix(painter, model_->getGameOverTextCode(), color);
}
