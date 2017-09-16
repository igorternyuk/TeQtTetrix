#include "tetrisview.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>

TetrisView::TetrisView(QMainWindow *parent) :
    QMainWindow(parent)
{
    model_ = new TetrisModel();
    controller_ = new TetrisController(model_, this);
    scoreLCD_ = new LCDWidget(DIGITAL_DISPLAY_WIDTH, DIGITAL_DISPLAY_HEIGHT,
                              DIGITAL_DISPLAY_DIGITS_NUMBER, Qt::red);
    levelLCD_ = new LCDWidget(DIGITAL_DISPLAY_WIDTH, DIGITAL_DISPLAY_HEIGHT,
                              DIGITAL_DISPLAY_DIGITS_NUMBER, Qt::green);
    linesLCD_ = new LCDWidget(DIGITAL_DISPLAY_WIDTH, DIGITAL_DISPLAY_HEIGHT,
                              DIGITAL_DISPLAY_DIGITS_NUMBER, Qt::cyan);
    startButton  = new QPushButton("Start");
    startButton->setFocusPolicy(Qt::NoFocus);
    newGameButton  = new QPushButton("NewGame");
    newGameButton->setFocusPolicy(Qt::NoFocus);
    pauseButton = new QPushButton("Pause");
    pauseButton->setFocusPolicy(Qt::NoFocus);
    aboutButton = new QPushButton("Info");
    aboutButton->setFocusPolicy(Qt::NoFocus);
    exitButton = new QPushButton("Quit");
    exitButton->setFocusPolicy(Qt::NoFocus);
    field_ = new TetrisField(model_, controller_);
    QVBoxLayout *rightVBoxLayout = new QVBoxLayout;
    rightVBoxLayout->setSpacing(SPACING_BETWEEN_BUTTONS);
    rightVBoxLayout->addWidget(createLabel("NEXT PIECE:"));
    nextPieceLabel_ = new QLabel();
    rightVBoxLayout->addWidget(nextPieceLabel_);
    rightVBoxLayout->addWidget(createLabel("SCORE"));
    rightVBoxLayout->addWidget(scoreLCD_);
    rightVBoxLayout->addWidget(createLabel("LEVEL"));
    rightVBoxLayout->addWidget(levelLCD_);
    rightVBoxLayout->addWidget(createLabel("LINES REMOVED"));
    rightVBoxLayout->addWidget(linesLCD_);
    rightVBoxLayout->addWidget(newGameButton);
    rightVBoxLayout->addWidget(startButton);
    rightVBoxLayout->addWidget(pauseButton);
    rightVBoxLayout->addWidget(aboutButton);
    rightVBoxLayout->addWidget(exitButton);
    rightVBoxLayout->insertStretch(VERTICAL_SPACER_INDEX );
    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    hBoxLayout->addWidget(field_);
    hBoxLayout->addLayout(rightVBoxLayout);
    QWidget *widget = new QWidget;
    widget->setLayout(hBoxLayout);
    this->setCentralWidget(widget);
    this->setWindowTitle(WINDOW_TITLE);
    this->setFixedSize(WINDOW_WIDTH_WITHOUT_FIELD + model_->getFieldWidth() * Block::getBlockSize(),
                       WINDOW_HEIGHT_WITHOUT_FIELD + model_->getFieldHeight() * Block::getBlockSize());
    connect(newGameButton, SIGNAL(clicked(bool)), controller_, SLOT(onNewGameButtonPressed()));
    connect(startButton, SIGNAL(clicked(bool)), controller_, SLOT(onStartButtonPressed()));
    connect(pauseButton, SIGNAL(clicked(bool)), controller_, SLOT(onSpaceButtonPressed()));
    connect(aboutButton, SIGNAL(clicked(bool)),this, SLOT(showInfoAboutTetris()));
    connect(exitButton, &QPushButton::clicked, [&]() {close();});
    connect(model_, SIGNAL(updateView()), this, SLOT(update()));
    connect(model_, SIGNAL(linesRemovedChanged(int)), linesLCD_, SLOT(update(int)));
    connect(model_, SIGNAL(levelChanged(int)), levelLCD_, SLOT(update(int)));
    connect(model_, SIGNAL(scoreChanged(int)), scoreLCD_, SLOT(update(int)));
    connect(model_, SIGNAL(showNextPiece()), this, SLOT(drawNextPiece()));
    levelLCD_->update(model_->getCurrentLevel());
}
void TetrisView::update()
{
    field_->update();
}

void TetrisView::drawNextPiece()
{
    Tetramino nextPiece = model_->getNextPiece();
    int dx = nextPiece.maxX() - nextPiece.minX() + 1;
    int dy = nextPiece.maxY() - nextPiece.minY() + 1;
    QPixmap pixmap(dx * Block::getBlockSize(), dy * Block::getBlockSize());
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), nextPieceLabel_->palette().background());
    std::vector<Block> nextPieceBlocks = nextPiece.getBlocks();
    for (int i = 0; i < model_->getNumBlocksInPiece(); ++i) {
        int x = nextPieceBlocks[i].getX() - nextPiece.minX();
        int y = nextPieceBlocks[i].getY() - nextPiece.minY();
        TetrisField::drawSquare(painter, x * Block::getBlockSize(), y * Block::getBlockSize(),
                   TetrisField::convertColor(nextPiece.getColor()));
    }
    nextPieceLabel_->setPixmap(pixmap);
    nextPieceLabel_->setAlignment(Qt::AlignCenter | Qt::AlignBottom);
}

QLabel *TetrisView::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
    return label;
}

void TetrisView::showInfoAboutTetris() const
{
    QMessageBox infoMessage;
    infoMessage.setText(INFO_ABOUT_TETRIS);
    infoMessage.exec();
}
