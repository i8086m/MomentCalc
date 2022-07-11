

#pragma once

#include "Matrix.h"


class MomentMatrix : public Matrix {
protected:
    double avgX, avgY;
    double muCache[4][4]{};

    double m(int k, int s);

    double eta(int k, int s);

    double mu(int k, int s);

public:
    MomentMatrix(int x, int y, const std::string& fileName);

    double phi1();

    double phi2();

    double phi3();

    double phi4();

    double phi5();

    double phi6();

    double phi7();

};
