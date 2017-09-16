#include <QtCore>
#include <QDebug>
#include <ctime>
#include <stdlib.h>
#include "tetramino.h"

Tetramino::Tetramino() :
    x_(INITIAL_POS_X), y_(INITIAL_POS_Y)
{
    Array3D SHAPES = getMatrixOfShapes();
    setRandomShape();
    size_ = SHAPES[shape_][SHAPES[shape_].size() - 1][0];
    color_ = static_cast<Color>(SHAPES[shape_][SHAPES[shape_].size() - 1][1]);
    if(shape_ == IShape) y_ = -1; // Эсли фигура в форме палки то смещаем ее на 1 вверх
    shapeMatrix_.resize(SHAPES[shape_].size() - 1);
    std::copy(SHAPES[shape_].begin(), SHAPES[shape_].end() - 1, shapeMatrix_.begin());
    fillShapeByBlocks();
}

void Tetramino::move(Direction dir)
{
    if(dir == RIGHT) {
        for(auto &block : blocks_)
            block.setX(block.getX() + 1);
        ++x_;
    }else
    {
        for(auto &block : blocks_)
            block.setX(block.getX() - 1);
        --x_;
    }
}

Tetramino Tetramino::rotate(Direction dir)
{
    if(shape_ == OShape) return *this; // Если форма тетрамины квадратная то не вращаем ее
    // Создаем временную матрицу и заполняем ее нулями
    Matrix tmp;
    tmp.resize(shapeMatrix_.size());
    for(int i = 0; i < size_; ++i)
        tmp[i].resize(size_);
    for(int i = 0; i < size_; ++i)
        for(int j = 0; j < size_; ++j)
            tmp[i][j] = 0;

    if(dir == RIGHT) {
        for(int i = 0; i < size_; ++i)
            for(int j = 0; j < size_; ++j)
                 tmp[i][j] = shapeMatrix_[size_ - 1 - j][i];  // Поворот вправо правильный
    } else {
            for(int i = 0; i < size_; ++i)
                for(int j = 0; j < size_; ++j)
                      tmp[size_ - 1 - j][i] = shapeMatrix_[i][j];
    }
    shapeMatrix_ = tmp;
    blocks_.clear();
    fillShapeByBlocks();
    return *this;
}

void Tetramino::oneStepDown()
{
    for(auto &block : blocks_) {
        block.setY(block.getY() + 1);
    }
    ++y_;
}

Shape Tetramino::getShape() const
{
    return shape_;
}

Color Tetramino::getColor() const
{
    return color_;
}

std::vector<Block> Tetramino::getBlocks() const
{
    return blocks_;
}

Array3D Tetramino::getMatrixOfShapes() const
{
    static const Array3D SHAPES = {
    {{0,0,0,0},
     {1,1,1,1},
     {0,0,0,0},
     {0,0,0,0},
     {4, RED}},       // I
    {{1,1},
     {1,1},
     {2, GREEN}},     // O
    {{1,0,0},
     {1,1,1},
     {0,0,0},
     {3, BLUE}},      // J
    {{0,0,1},
     {1,1,1},
     {0,0,0},
     {3, YELLOW}},    // L
    {{0,1,1},
     {1,1,0},
     {0,0,0},
     {3, CYAN}},      // S
    {{1,1,1},
     {0,1,0},
     {0,0,0},
     {3, MAGENTA}},   // T
    {{1,1,0},
     {0,1,1},
     {0,0,0},
     {3, DARKGREEN}}  // Z
    };
    return SHAPES;
}

int Tetramino::minX() const
{
   std::vector<Block> blocks = getBlocks();
   int minX = blocks[0].getX();
   for(int i = 1; i < int(blocks.size()); ++i)
       minX = qMin(minX, blocks[i].getX());
   return minX;
}

int Tetramino::maxX() const
{
    std::vector<Block> blocks = getBlocks();
    int maxX = blocks[0].getX();
    for(int i = 1; i < int(blocks.size()); ++i)
        maxX = qMax(maxX, blocks[i].getX());
    return maxX;
}

int Tetramino::minY() const
{
    std::vector<Block> blocks = getBlocks();
    int minY = blocks[0].getY();
    for(int i = 1; i < int(blocks.size()); ++i)
        minY = qMin(minY, blocks[i].getY());
    return minY;
}

int Tetramino::maxY() const
{
    std::vector<Block> blocks = getBlocks();
    int maxY = blocks[0].getY();
    for(int i = 1; i < int(blocks.size()); ++i)
        maxY = qMax(maxY, blocks[i].getY());
    return maxY;
}

void Tetramino::setRandomShape()
{
    srand(time(NULL));
    shape_ = static_cast<Shape>(rand() % int(getMatrixOfShapes().size()));
}

void Tetramino::fillShapeByBlocks()
{
    for(int x = 0; x < size_; ++x)
        for(int y = 0; y < size_; ++y)
            if(shapeMatrix_[y][x] == 1) {
                Block block(this->x_ + x, this->y_ + y);
                blocks_.push_back(block);
            }
}
