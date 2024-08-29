// Compute PI using Buffon's methon (avoiding M_PI or other trigonometric functions)

#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <cmath>
#include <numeric>
#include <iomanip>
#include <algorithm>

using namespace std;


// Statistical uncertainty estimation
template <typename T>
double error(const std::vector<T>& AV, const std::vector<T>& AV2, int n) {

    return (n == 0) ? 0 : sqrt((AV2[n] - pow(AV[n], 2))/n);
}

// Check if needle hits the line
// Arguments: centre of the needle, cosine of angle with vertical, line spacing, needle length
template <typename T>
bool hit_line(T x0, T costheta, T d, T L) {
    bool hit = false;

    if (x0 >= d/2.) {                         // Line above
        if ((L/2.) * costheta >= d - x0)
            hit = true;
    }
    else {                                    // Line below
        if ((L/2.) * costheta >= x0)
            hit = true;
    }

    return hit;
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
    if (argc != 6) {
        cerr << endl << "Wrong  call " << argv[0] << endl;
        cerr << "Required arguments for execution are: <line spacing> <needle length> <points> <blocks> <rng seed>" << endl << endl;
        return 1;
    }

    const float distance = atof(argv[1]);
    const float length = atof(argv[2]);
    const long int points = strtol(argv[3], nullptr, 10);
    const long int blocks = strtol(argv[4], nullptr, 10);
    const long int R = points/blocks;                       // points per block
    const int seed = atoi(argv[5]);

    if (length >= distance) {
        cout << "WARNING: This method is valid only for 'short needles' (length < distance)" << endl;
        cout << "Aborting" << endl;
        return 1;
    }

    std::vector<float> x0(points), costheta(points);
    std::vector<double> v_pi(blocks), v_pi2(blocks);
    std::vector<double> sum_prog(blocks), su2_prog(blocks), err_prog(blocks);

    // Generator and distribution
    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> distribution_0d(0, distance), distribution_11(-1, 1);

    // Make arrays with random numbers (x0 = needle centre, theta = angle with vertical [0,PI/2])
    for (long int i = 0; i < points; i++) {
        float x1, y1;
        x0[i] = distribution_0d(rng);

        do{
            x1 = distribution_11(rng);
            y1 = distribution_11(rng);
        } while(pow(x1, 2) + pow(y1, 2) > 1);

        costheta[i] = fabs(x1) / sqrt(pow(x1, 2) + pow(y1, 2));
    }

    // Run MC
    for (long int i = 0; i < blocks; i++) {
        int hits = 0, k = 0;

        for (long int j = 0; j < R; j++) {
            k = j + i * R;

            if (hit_line(x0[k], costheta[k], distance, length))
                hits++;
        }

        v_pi[i] = 2. * length * R / (hits * distance);      // Compute PI in each block
        v_pi2[i] = pow(v_pi[i], 2);
    }

    // Compute MC error
    for (long int i = 0; i < blocks; i++) {
        sum_prog[i] = accumulate(v_pi.begin(), v_pi.begin() + i + 1, 0., std::plus<double>()) / (i + 1);
        su2_prog[i] = accumulate(v_pi2.begin(), v_pi2.begin() + i + 1, 0., std::plus<double>()) / (i + 1);
        err_prog[i] = error(sum_prog, su2_prog, i);
    }

    // Print results to file
    print_to_file("../../results/pi_buffon.dat", sum_prog, err_prog, 6);


    return 0;
}