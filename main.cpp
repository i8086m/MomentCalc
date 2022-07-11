

#include <iostream>
#include "MomentMatrix.h"

using namespace std;

int main() {

    string dir = "data\\";
    string images[] {
        "0.txt",
        "1.txt",
        "2.txt",
    };

    for (const string& img : images) {
        auto image = MomentMatrix(640, 480, dir + img);

        cout << "Image: " << img << endl
             << "Phi1 = " << image.phi1() << endl
             << "Phi2 = " << image.phi2() << endl
             << "Phi3 = " << image.phi3() << endl
             << "Phi4 = " << image.phi4() << endl
             << "Phi5 = " << image.phi5() << endl
             << "Phi6 = " << image.phi6() << endl
             << "Phi7 = " << image.phi7() << endl
             << endl;
    }

}
