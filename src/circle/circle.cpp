// Compute PI using a simple Monte Carlo method

#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <numeric>
#include <iomanip>
#include <algorithm>

using namespace std;


// Statistical uncertainty estimation
template <typename T>
double error(const std::vector<T>& AV, const std::vector<T>& AV2, int n) {

    return (n == 0) ? 0 : sqrt((AV2[n] - pow(AV[n], 2))/n);
}


// Print results to file
template <typename T, typename U>
void print_to_file(const std::string& name, const std::vector<T>& v1, const std::vector<U>& v2, int prec = 5) {
    ofstream fileout;
    int size = std::min(v1.size(), v2.size());

    if (v1.size() != v2.size())
        cout << "WARNING: function print_to_file received vectors with different size." << endl;

    fileout.open(name);
    if (fileout.is_open()) {
        for (int i = 0; i < size; i++) {
            fileout << std::setprecision(prec) << std::fixed;
            fileout << i << " " << v1[i] << " " << v2[i] << endl;
        }
    }
    else {
        cerr << "ERROR: Unable to write file " << name << endl;
    }

    fileout.close();
}


/***************************************   MAIN   ***********************************/
int main (int argc, char const *argv[]) {

    // Check input parameters
    if (argc != 5) {
        cerr << endl << "Wrong  call " << argv[0] << endl;
        cerr << "Required arguments for execution are: <radius> <points> <blocks> <rng seed>" << endl << endl;
        return 1;
    }

    const float r = atof(argv[1]);
    const long int points = strtol(argv[2], nullptr, 10);
    const long int blocks = strtol(argv[3], nullptr, 10);
    const long int R = points/blocks;                       // points per block
    const int seed = atoi(argv[4]);

    std::vector<float> x0(points), y0(points);
    std::vector<double> v_pi(blocks), v_pi2(blocks);
    std::vector<double> sum_prog(blocks), su2_prog(blocks), err_prog(blocks);

    // Generator and distribution
    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> distribution(-1.*r, r);

    // Make arrays with random couples (x,y)
    for (long int i = 0; i < points; i++) {
        x0[i] = distribution(rng);
        y0[i] = distribution(rng);
    }

    // Run MC
    for (long int i = 0; i < blocks; i++) {
        int hits = 0, k = 0;

        for (long int j = 0; j < R; j++) {
            k = j + i * R;

            if (pow(x0[k], 2) + pow(y0[k], 2) < pow(r, 2))
                hits++;
        }

        v_pi[i] = 4. * hits / R;      // Compute PI in each block
        v_pi2[i] = pow(v_pi[i], 2);
    }

    // Compute MC error
    for (long int i = 0; i < blocks; i++) {
        sum_prog[i] = accumulate(v_pi.begin(), v_pi.begin() + i + 1, 0., std::plus<double>()) / (i + 1);
        su2_prog[i] = accumulate(v_pi2.begin(), v_pi2.begin() + i + 1, 0., std::plus<double>()) / (i + 1);
        err_prog[i] = error(sum_prog, su2_prog, i);
    }

    // Print results to file
    print_to_file("../../results/pi_circle.dat", sum_prog, err_prog);


    return 0;
}