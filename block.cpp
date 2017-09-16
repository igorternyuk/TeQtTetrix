#include "block.h"

Block::Block(const int &x, const int &y) :
    coordX_(x), coordY_(y)
{}

void Block::setX(const int &x)
{
    this->coordX_ = x;
}

void Block::setY(const int &y)
{
    this->coordY_ = y;
}

int Block::getX() const
{
    return coordX_;
}

int Block::getY() const
{
    return coordY_;
}

int Block::getBlockSize()
{
    static const int blockSize = 18;
    return blockSize;
}
