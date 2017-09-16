#ifndef BLOCK_H
#define BLOCK_H

class Block
{
public:
    Block(const int &x, const int &y);
    void setX(const int &x);
    void setY(const int &y);
    int getX() const;
    int getY() const;
    static int getBlockSize();
private:
    int coordX_, coordY_;
};

#endif // BLOCK_H
