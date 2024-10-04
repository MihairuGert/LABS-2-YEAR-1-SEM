#pragma once

// TODO: DO WE NEED IT AT ALL?
class Cell {
private:
    int x;
    int y;
public:
    Cell(int x, int y);
    void setXY(int x, int y);
    int getX();
    int getY();
};

