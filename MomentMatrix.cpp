

#include "MomentMatrix.h"
#include <cmath>


double square(double x) { return x * x; }

double MomentMatrix::m(int k, int s) { // M [ Момент порядка ]
    double sum = 0;
    for (int n = 0; n < ySize; n++) { // Y-axis
        for (int m = 0; m < xSize; m++) { // X-axis
            sum += pow(m, k) * pow(n, s) * get(m, n);
        }
    }
    return sum;
}

double MomentMatrix::eta(int k, int s) { // Eta [ Центральные моменты ]
    if (k == 0 && s == 0) return m(k, s);
    if (k == 1 && s == 0) return 0;
    if (k == 0 && s == 1) return 0;
    if (k == 2 && s == 0) return m(k, s) - avgX * m(1, 0);
    if (k == 0 && s == 2) return m(k, s) - avgY * m(0, 1);
    if (k == 1 && s == 1) return m(k, s) - avgY * m(1, 0);
    if (k == 3 && s == 0) return m(k, s) - 3*m(2, 0)*avgX + 2*m(1, 0)*square(avgX);
    if (k == 0 && s == 3) return m(k, s) - 3*m(0, 2)*avgY + 2*m(0, 1)*square(avgY);
    if (k == 1 && s == 2) return m(k, s) - 2*m(1,1)*avgY - avgX*m(0, 2) + 2*m(1,0)*square(avgY);
    if (k == 2 && s == 1) return m(k, s) - 2*m(1,1)*avgX - avgY*m(2, 0) + 2*m(0,1)*square(avgX);
    return 0;
}

double MomentMatrix::mu(int k, int s) { // Mu [ Нормализованные моменты ]
    if (std::max(k, s) > 3) throw std::runtime_error("Incorrect k and s values");

    if (muCache[k][s] != 0) return muCache[k][s];

    double z = ((double)k + (double)s) / 2 + 1;

    return muCache[k][s] = eta(k, s) / pow(eta(0, 0),z );
}


MomentMatrix::MomentMatrix(int x, int y, const std::string& fileName) : Matrix(x, y, fileName) {
    avgX = m(1, 0) / m(0, 0);
    avgY = m(0, 1) / m(0, 0);
}

double MomentMatrix::phi1() {  // Phi1 [ 1-й инвариант ]
    return mu(2, 0) + mu(0, 2);
}

double MomentMatrix::phi2() {  // Phi2 [ 2-й инвариант ]
    return square(mu(2, 0) - mu(0, 2))
           + 4*square(mu(1, 1));
}

double MomentMatrix::phi3() {  // Phi3 [ 3-й инвариант ]
    return square(mu(3, 0) - 3*mu(1, 2))
           + square(3*mu(2, 1) + mu(0, 3));
}

double MomentMatrix::phi4() {  // Phi4 [ 4-й инвариант ]
    return square(mu(3, 0) - 3*mu(1, 2))
           + square(3*mu(2, 1) + mu(0, 3));
}

double MomentMatrix::phi5() {  // Phi5 [ 5-й инвариант ]
    return 1.0
           * (mu(3, 0) - 3*mu(1, 2))
           * (mu(3, 0) + mu(1, 2))
           * ( square(mu(3, 0) + mu(1, 2)) - 3*square(mu(2, 1) + mu(0, 3)) )
           + 1.0
             * (3*mu(2, 1) - mu(0, 3))
             * (mu(2, 1) + mu(0, 3))
             * ( 3*square(mu(3, 0) + mu(1, 2)) - square(mu(2, 1) + mu(0, 3)) );
}

double MomentMatrix::phi6() {  // Phi6 [ 6-й инвариант ]
    return 1.0
           * (mu(2,0) - mu(0,2))
           * (square(mu(3,0) + mu(1,2)) - square(mu(2,1) + mu(0,3)))
           + 4 * mu(1,1) * (mu(3,0)
                            + mu(1,2)) * (mu(2,1)
                                          + mu(0,3));
}

double MomentMatrix::phi7() {  // Phi7 [ 7-й инвариант ]
    return 1.0
           * (3 * mu(2,1) - mu(0,3))
           * (mu(3,0) + mu(1,2))
           * (square(mu(3,0) + mu(1,2))-3*square(mu(2,1)+mu(0,3)))
           - (mu(2,1) - 3*mu(1,2))*(mu(2,1) + mu(0,3))
             * (3*square(mu(3,0) + mu(1,2)) - square(mu(2,1)+mu(0,3)));
}