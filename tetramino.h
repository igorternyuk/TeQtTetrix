#ifndef TETRAMINO_H
#define TETRAMINO_H

#include <vector>
#include <algorithm>
#include "block.h"

typedef std::vector< std::vector< std::vector< int > > > Array3D;
typedef std::vector< std::vector< int > > Matrix;
typedef std::vector< std::vector< bool > > boolMatrix;
enum Color {BLACK, RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA, DARKGREEN, WHITE};
enum Shape { IShape, OShape, JShape, LShape, SShape, TShape, ZShape };
enum Direction {LEFT, RIGHT};

class Tetramino
{
public:
    explicit Tetramino();
    //Методы для управления тетраминой
    void move(Direction dir);
    Tetramino rotate(Direction dir);
    void oneStepDown();
    //Методы предоставляющие информацию для отображения
    Shape getShape() const;
    Color getColor() const;
    std::vector<Block> getBlocks() const;
    Array3D getMatrixOfShapes() const;
    int minX() const;
    int maxX() const;
    int minY() const;
    int maxY() const;
private:
    enum IntialCoords {INITIAL_POS_X = 10, INITIAL_POS_Y = 0}; // Начальные координаты фигуры
    int x_, y_;  // Координаты фигуры
    Shape shape_;
    int size_;
    Color color_;
    Matrix shapeMatrix_;
    std::vector<Block> blocks_;
    void setRandomShape();
    void fillShapeByBlocks();
};

#endif // TETRAMINO_H
