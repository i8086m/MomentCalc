#include <iostream>
#include <cmath>
#include <fstream>

typedef unsigned char byte;
template<typename T> T square(T x) { return x * x; }

class Matrix {
protected:
    int xSize, ySize;
    byte *mat;

public:
    Matrix(int x, int y, const std::string& fileName) : xSize(x), ySize(y) {
        mat = new byte[xSize * ySize];
        std::ifstream fin(fileName, std::ios::binary);
        if (!fin.is_open()) throw std::runtime_error("Can't open file");

        fin.read((char*)(mat), xSize * ySize);

        fin.close();
    }

    double get(int x, int y) {
        return ( (double)mat[y*xSize+x] / 255 );
    }
};

class MomentMatrix : public Matrix {
protected:
    double avgX, avgY;
    double muCache[4][4]{};

    double m(int k, int s) { // M [ Момент порядка ]
        double sum = 0;
        for (int n = 0; n < ySize; n++) { // Y-axis
            for (int m = 0; m < xSize; m++) { // X-axis
                sum += pow(m, k) * pow(n, s) * get(m, n);
            }
        }
        return sum;
    }

    double eta(int k, int s) { // Eta [ Центральные моменты ]
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

    double mu(int k, int s) { // Mu [ Нормализованные моменты ]
        if (std::max(k, s) > 3) throw std::runtime_error("Incorrect k and s values");

        if (muCache[k][s] != 0) return muCache[k][s];

        double z = ((double)k + (double)s) / 2 + 1;

        return muCache[k][s] = eta(k, s) / pow(eta(0, 0),z );
    }

public:
    MomentMatrix(int x, int y, const std::string& fileName) : Matrix(x, y, fileName) {
        avgX = m(1, 0) / m(0, 0);
        avgY = m(0, 1) / m(0, 0);
    }

    double phi1() {  // Phi1 [ 1-й инвариант ]
        return mu(2, 0) + mu(0, 2);
    }

    double phi2() {  // Phi2 [ 2-й инвариант ]
        return square(mu(2, 0) - mu(0, 2))
             + 4*square(mu(1, 1));
    }

    double phi3() {  // Phi3 [ 3-й инвариант ]
        return square(mu(3, 0) - 3*mu(1, 2))
             + square(3*mu(2, 1) + mu(0, 3));
    }

    double phi4() {  // Phi4 [ 4-й инвариант ]
        return square(mu(3, 0) - 3*mu(1, 2))
               + square(3*mu(2, 1) + mu(0, 3));
    }

    double phi5() {  // Phi5 [ 5-й инвариант ]
        return 1.0
             * (mu(3, 0) - 3*mu(1, 2))
             * (mu(3, 0) + mu(1, 2))
             * ( square(mu(3, 0) + mu(1, 2)) - 3*square(mu(2, 1) + mu(0, 3)) )
             + 1.0
             * (3*mu(2, 1) - mu(0, 3))
             * (mu(2, 1) + mu(0, 3))
             * ( 3*square(mu(3, 0) + mu(1, 2)) - square(mu(2, 1) + mu(0, 3)) );
    }

    double phi6() {  // Phi6 [ 6-й инвариант ]
        return 1.0
             * (mu(2,0) - mu(0,2))
             * (square(mu(3,0) + mu(1,2)) - square(mu(2,1) + mu(0,3)))
             + 4 * mu(1,1) * (mu(3,0)
             + mu(1,2)) * (mu(2,1)
             + mu(0,3));
    }

    double phi7() {  // Phi7 [ 7-й инвариант ]
        return 1.0
             * (3 * mu(2,1) - mu(0,3))
             * (mu(3,0) + mu(1,2))
             * (square(mu(3,0) + mu(1,2))-3*square(mu(2,1)+mu(0,3)))
             - (mu(2,1) - 3*mu(1,2))*(mu(2,1) + mu(0,3))
             * (3*square(mu(3,0) + mu(1,2)) - square(mu(2,1)+mu(0,3)));
    }

};




int main() {

    std::string dir = "data\\";
    std::string images[] {
        "0.txt",
        "1.txt",
        "2.txt",
    };

    for (const std::string& img : images) {
        auto image = MomentMatrix(640, 480, dir + img);

        std::cout << "Image: " << img << std::endl
                  << "Phi1 = " << image.phi1() << std::endl
                  << "Phi2 = " << image.phi2() << std::endl
                  << "Phi3 = " << image.phi3() << std::endl
                  << "Phi4 = " << image.phi4() << std::endl
                  << "Phi5 = " << image.phi5() << std::endl
                  << "Phi6 = " << image.phi6() << std::endl
                  << "Phi7 = " << image.phi7() << std::endl
                  << std::endl << std::endl;
    }


}
