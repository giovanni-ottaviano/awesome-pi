// Compute PI by simulating a elastic block-collision process

#include <iostream>
#include <cstdlib>

using namespace std;

int main (int argc, char const *argv[]) {

    // Check input parameters
    if (argc != 3) {
        cerr << endl << "Wrong  call " << argv[0] << endl;
        cerr << "Required arguments for execution are <mass> <velocity>, where mass = 10^(2n) and velocity < 0" << endl << endl;
        return 1;
    }

    double m1 = atof(argv[1]), m2 = 1.;
    double v1 = atof(argv[2]), v2 = 0.;
    long int n_collisions = 0;
    bool block_collision = true;

    while (true) {
        if (v1 > 0 && v2 > 0 && v1 >= v2)
            break;
    
        // Collision between blocks
        if (block_collision) {
            double m_tot = m1 + m2;
            double m_dif = m1 - m2;

            v1 = (m_dif / m_tot) * v1 + (2. * m2 / m_tot) * v2;
            v2 = -(m_dif / m_tot) * v2 + (2. * m1 / m_tot) * v1;
            
            block_collision = false;
        }
        else {
            // Collision between block 2 and wall
            v2 = -v2;

            block_collision = true;
        }

        n_collisions++;
    }
    cout << n_collisions << endl;

    return 0;
}