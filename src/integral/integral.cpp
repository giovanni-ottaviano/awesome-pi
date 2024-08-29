// Compute PI using numerical quadrature (i.e. integrating 1/(1 + x^2))

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


// Integrand function
double f(double x) {

    return 1./(1. + x*x);
}


/***************************************   MAIN   ***********************************/
int main (int argc, char const *argv[]) {

    // Check input parameters
    if (argc != 4) {
        cerr << endl << "Wrong  call " << argv[0] << endl;
        cerr << "Required arguments for execution are: <points> <blocks> <rng seed>" << endl << endl;
        return 1;
    }

    const long int points = strtol(argv[1], nullptr, 10);
    const long int blocks = strtol(argv[2], nullptr, 10);
    const long int R = points/blocks;                       // points per block
    const int seed = atoi(argv[3]);
    const double x_min = 0., x_max = 1.;                    //bounds for integration


    std::vector<float> x0(points);
    std::vector<double> I(blocks), I2(blocks);
    std::vector<double> sum_prog(blocks), su2_prog(blocks), err_prog(blocks);

    // Generator and distribution
    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> distribution(x_min, x_max);

    // Prepare vector with random numbers
    for (long int i = 0; i < points; i++)
        x0[i] = distribution(rng);

    // Run MC
    for (long int i = 0; i < blocks; i++) {
        int k = 0;
        double sum = 0.;

        for (int j = 0; j < R; j++) {
            k = j + i * R;
            sum += f(x0[k]);
        }

        I[i] = (x_max - x_min) * sum / R;   // Integral estimation (for each block)
        I2[i] = pow(I[i], 2);
    }

    // Compute statistical uncertanty
    for (long int i = 0; i < blocks; i++) {
        sum_prog[i] = accumulate(I.begin(), I.begin() + i + 1, 0., std::plus<double>()) / (i + 1);
        su2_prog[i] = accumulate(I2.begin(), I2.begin() + i + 1, 0., std::plus<double>()) / (i + 1);
        err_prog[i] = error(sum_prog, su2_prog, i);
    }

    // Compute value of PI from give integral
    std::transform(sum_prog.begin(), sum_prog.end(), sum_prog.begin(), [](double i) { return 4. * i; });
    std::transform(err_prog.begin(), err_prog.end(), err_prog.begin(), [](double i) { return 4. * i; });

    //Print results to file
    print_to_file("../../results/pi_integral.dat", sum_prog, err_prog, 5);


    return 0;
}
