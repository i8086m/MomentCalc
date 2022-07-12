

#pragma once

#include <iostream>

typedef unsigned char byte;


class Matrix {
protected:
    int xSize, ySize;
    byte *mat;

public:
    Matrix(int x, int y, const std::string& fileName);

    ~Matrix();

    double get(int x, int y);
};

