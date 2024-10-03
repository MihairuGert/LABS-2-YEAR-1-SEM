#include "Cell.h"

Cell::Cell(int x, int y) {
    this->x = x;
    this->y = y;
}

void Cell::setXY(int x, int y) {
    this->x = x;
    this->y = y;
}

int Cell::getX() {
    return x;
}

int Cell::getY() {
    return y;
}
