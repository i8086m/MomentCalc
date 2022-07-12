

#include "Matrix.h"
#include <fstream>


Matrix::Matrix(int x, int y, const  std::string& fileName)  : xSize(x), ySize(y) {
    mat = new byte[xSize * ySize];
    std::ifstream fin(fileName, std::ios::binary);
    if (!fin.is_open()) throw std::runtime_error("Can't open file");

    fin.read((char*)(mat), xSize * ySize);

    fin.close();
}

Matrix::~Matrix() {
    delete [] mat;
}

double Matrix::get(int x, int y) {
    return ((double)mat[y*xSize+x] / 255);
}