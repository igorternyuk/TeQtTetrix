#include "tetrismodel.h"

TetrisModel::TetrisModel(QObject *parent, int fieldWidth, int fieldHeight) :
    QObject(parent), fieldWidth_(fieldWidth), fieldHeight_(fieldHeight),
    score_(0), speed_(0), level_(1), numLinesRemoved_(0),
    numPiecesDropped_(0), isGameOver_(false), isGameStarted_(false),
    isGamePaused_(false)
{
    gameField_.resize(fieldHeight_ + 1); // + 1 - additional row witch represents field bottom
    for(auto &row : gameField_)
        row.resize(fieldWidth_);
    newGame();
}

TetrisModel::~TetrisModel()
{}

int TetrisModel::getFieldWidth() const
{
    return fieldWidth_;
}

int TetrisModel::getFieldHeight() const
{
    return fieldHeight_;
}

int TetrisModel::getNumBlocksInPiece() const
{
    return NUM_BLOCKS_IN_PIECE;
}

int TetrisModel::getCurrentLevel() const
{
    return level_;
}

void TetrisModel::moveLeft()
{
    if(!isTouchWall(activePiece_, LEFT)) {
        activePiece_.move(LEFT);
        emit updateView();
    }
}

void TetrisModel::moveRight()
{
    if(!isTouchWall(activePiece_, RIGHT)) {
        activePiece_.move(RIGHT);
        emit updateView();
    }
}

void TetrisModel::rotateLeft()
{
    Tetramino tmp = activePiece_;
    if(!hasCollisions(tmp.rotate(LEFT))) {
        activePiece_ = tmp;
        emit updateView();
    }
}

void TetrisModel::rotateRight()
{
    Tetramino tmp = activePiece_;
    if(!hasCollisions(tmp.rotate(RIGHT))) {
        activePiece_ = tmp;
        emit updateView();
    }
}

void TetrisModel::oneLineDown()
{
    activePiece_.oneStepDown();
}

void TetrisModel::dropDown()
{
    int dropHeight = 0;
    while(!isTouchGround()) {
        activePiece_.oneStepDown();
        ++dropHeight;
    }
    prepareAfterPieceDropping(dropHeight);
}

Tetramino TetrisModel::getActivePiece() const
{
    return activePiece_;
}

Tetramino TetrisModel::getNextPiece() const
{
    return nextPiece_;
}

Color TetrisModel::getColorAt(int x, int y) const
{
    return static_cast<Color>(gameField_[y][x]);
}

bool TetrisModel::isGameStarted() const
{
    return isGameStarted_;
}

bool TetrisModel::isGameOver() const
{
    return isGameOver_;
}

boolMatrix TetrisModel::getGameOverTextCode() const
{
    static const boolMatrix GAME_OVER_TEXT_CODE = {
        {0,0,1,1,0,0,0,1,1,1,0,1,1,1,1,0,0,1,1,1,1,0},
        {0,1,0,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,0,0,0},
        {0,1,0,1,1,0,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,0},
        {0,1,0,0,1,0,1,0,0,1,0,1,0,1,0,1,0,1,0,0,0,0},
        {0,0,1,1,0,0,1,0,0,1,0,1,0,1,0,1,0,1,1,1,1,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,1,1,1,0,1,0,0,1,0,1,1,1,1,0,1,1,1,1,0,1},
        {0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,1},
        {0,1,0,0,1,0,1,0,0,1,0,1,1,1,1,0,1,1,1,1,0,1},
        {0,1,0,0,1,0,1,0,1,0,0,1,0,0,0,0,1,0,1,0,0,0},
        {0,1,1,1,1,0,1,1,0,0,0,1,1,1,1,0,1,0,0,1,0,1}
    };
    return GAME_OVER_TEXT_CODE;
}

bool TetrisModel::isGamePaused() const
{
    return isGamePaused_;
}

boolMatrix TetrisModel::getPauseTextCode() const
{
    static const boolMatrix GAME_PAUSED_TEXT_CODE = {
        {0,0,1,1,1,0,0,1,1,0,1,0,1,0,1,1,1,0,1,1,1,0},
        {0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,0,0},
        {0,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1,1,1,0},
        {0,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,0,0},
        {0,0,1,0,0,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0}
    };
    return GAME_PAUSED_TEXT_CODE;
}

void TetrisModel::start()
{
    if(!isGameStarted())
        isGameStarted_  = true;
    isGamePaused_ = false;
    timer_.start(timeOutTime(), this);
    emit updateView();
}

void TetrisModel::pause()
{
    isGamePaused_ = true;
    timer_.stop();
    emit updateView();
}

void TetrisModel::newGame()
{
    reset();
    newPiece();
    emit showNextPiece();
    emit updateView();
}

void TetrisModel::timerEvent(QTimerEvent*)
{
    if(isGameOver_) {
        timer_.stop();
        return;
    }
    emit updateView();
    emit showNextPiece();
     if(isTouchGround()) {
        uniteWithDroppedPieces();
        prepareAfterPieceDropping(0);
        removeFullLines();
        newPiece();
        emit showNextPiece();
        isGameOver_ = isCrossGround();
    } else {
        oneLineDown();
    }    
}

TetrisModel::TetrisModel(TetrisModel &) : QObject(nullptr)
{}

void TetrisModel::reset()
{
    if(timer_.isActive())
        timer_.stop();
    score_ = 0;
    speed_= 0;
    level_ = 1;
    numLinesRemoved_ = 0;
    numPiecesDropped_ = 0;
    isGameOver_ = false;
    isGameStarted_ = false;
    isGamePaused_ = false;
    clearField();
    fillFieldBottom();
    emit levelChanged(1);
    emit scoreChanged(score_);
    emit linesRemovedChanged(numLinesRemoved_);
}

int TetrisModel::timeOutTime()
{
    return BASE_TIMER_TIMEOUT_TIME / (level_ + 1);
}

bool TetrisModel::isCrossGround() const
{
    for(auto block : activePiece_.getBlocks()) {
        if(gameField_[block.getY()][block.getX()] > 0) {
            return true;
        }
    }
    return false;
}

bool TetrisModel::isTouchGround() const
{
    for(auto block : activePiece_.getBlocks()) {
        if(gameField_[block.getY() + 1][block.getX()] > 0) {
            return true;
        }
    }
    return false;
}

bool TetrisModel::isTouchWall(const Tetramino &tetramino, Direction dir) const
{
    for(auto block : tetramino.getBlocks()) {
        if(dir == LEFT && (block.getX() - 1 < 0 ||
             gameField_[block.getY()][block.getX() - 1] > 0)) return true;
        if(dir == RIGHT && (block.getX() + 1 >= fieldWidth_ ||
             gameField_[block.getY()][block.getX() + 1] > 0)) return true;
    }
    return false;
}

bool TetrisModel::hasCollisions(const Tetramino &tetramino) const
{
    for(auto block : tetramino.getBlocks()) {
        if(block.getX() < 0 || block.getX() >= fieldWidth_ ||
                gameField_[block.getY()][block.getX()] > 0) return true;
    }
    return false;
}

void TetrisModel::uniteWithDroppedPieces()
{
    for(auto block : activePiece_.getBlocks()) {
        gameField_[block.getY()][block.getX()] = activePiece_.getColor();
        //gameField_[block.getY()][block.getX()] = WHITE; // Если все блоки должны становится белыми
    }
}

void TetrisModel::clearField()
{
    for(int i = 0; i < fieldHeight_; ++i)
        for(int j = 0; j < fieldWidth_; ++j)
                gameField_[i][j] =  0;
}

void TetrisModel::fillFieldBottom()
{
    for(int j = 0; j < fieldWidth_; ++j)
        gameField_[fieldHeight_][j] = 1;
}

void TetrisModel::prepareAfterPieceDropping(const int &dropHeight)
{
    ++numPiecesDropped_;
    if(numPiecesDropped_ > NUM_DROPPED_PIECES_FOR_NEXT_LEVEL &&
       numPiecesDropped_ % NUM_DROPPED_PIECES_FOR_NEXT_LEVEL == 0) {
        ++level_;
        timer_.start(timeOutTime(),this);
        emit levelChanged(level_);
    }
    score_ += dropHeight;
    emit scoreChanged(score_);
}

void TetrisModel::removeFullLines()
{
   int numRemovedLines = 0;
   for(int i = 0; i < fieldHeight_; ++i) {
       bool isCurrentLineFilled = true;
       for(int j = 0; j < fieldWidth_; ++j) {
           if(gameField_[i][j] == 0)
               isCurrentLineFilled = false;
       }
       if(isCurrentLineFilled) {
           ++numRemovedLines;
           for(int j = 0; j < fieldWidth_; ++j)
               gameField_[i][j] = 0;
           for(int k = i; k > 0; --k)
               for(int j = 0; j < fieldWidth_; ++j)
                   gameField_[k][j] = gameField_[k - 1][j];
       }
   }
   numLinesRemoved_ += numRemovedLines;
   emit linesRemovedChanged(numLinesRemoved_);
   score_ += getScoreForRemovedLines(numRemovedLines);
   emit scoreChanged(score_);
}

int TetrisModel::getScoreForRemovedLines(const int &numRemovedLines) const
{
    static const int SCORES[] = {100, 300, 700, 1500}; // Массив очков за очищенные ряды
    static const int MAX_POSSIBLE_NUM_LINES_TO_REMOVE = 4;
    int score;
    if(numRemovedLines <= 0) score = 0;
    if(numRemovedLines > MAX_POSSIBLE_NUM_LINES_TO_REMOVE)
        score = SCORES[3];
    else
        score = SCORES[numRemovedLines - 1];
    return score;
}

void TetrisModel::newPiece()
{
    activePiece_ = nextPiece_;
    nextPiece_ = Tetramino();
}
