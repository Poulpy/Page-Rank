#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>

#include "Matrix.hpp"

using namespace std;

/**
 * Page rank algorithm with the power method
 *
 * matrix: adjacency list of the graph
 * d: damping
 * max_iterations:
 * epsilon:
 */
vector<double> page_rank_power_method(MatrixD matrix, size_t nodes_count,
                                      double damping = 0.85,
                                      size_t max_iterations = 100,
                                      double epsilon = 0.000001) {

    vector<double> v(nodes_count);
    for (size_t i = 0; i != nodes_count; i++) v[i] = ((double) rand() / (RAND_MAX));

    MatrixD e(nodes_count, nodes_count);
    e *= 0;
    e += (1.0 - damping) / nodes_count;

    MatrixD hat_matrix = matrix * damping;
    hat_matrix += e;

    vector<double> v_last(nodes_count);
    double err;

    for (size_t i = 0; i != max_iterations; i++) {
        v_last = v;
        v = hat_matrix * v;
        err = 0.0;

        for (size_t j = 0; j != nodes_count; j++) {
            err += err + std::fabs(v[j] - v_last[j]);
        }

        if (err < epsilon) {
            return v;
        }
    }

    return v;
}

int main() {
    std::ifstream file;
    std::ofstream output_file;
    vector<std::pair<int, int>> pairs;
    int maximum = 0;
    int n1 = 0, n2 = 0;
    size_t nodes_count;

    file.open("resources/joshua.txt");
    while (file >> n1 >> n2) {
        maximum = max(maximum, n1);
        maximum = max(maximum, n2);

        pairs.push_back( { n1, n2 });
    }
    file.close();
    nodes_count = maximum;
    MatrixD matrix(nodes_count, nodes_count);

    // init with 0
    matrix *= 0.0;
    for (size_t i = 0; i != pairs.size(); i++) {
        matrix(pairs.at(i).first - 1, pairs.at(i).second - 1) = 1.0;
        matrix(pairs.at(i).second - 1, pairs.at(i).first - 1) = 1.0;
    }

    for (size_t i = 0; i != matrix.nCols(); i++) {
        int count = 0;
        for (size_t j = 0; j != matrix.nRows(); j++) {
            if (matrix(j, i) == 1.0) {
                count++;
            }
        }
        for (size_t j = 0; j != matrix.nRows(); j++) {
            if (matrix(j, i) == 1.0) {
                matrix(j, i) = matrix(j, i) / count;
            }
        }
    }


    auto result = page_rank_power_method(matrix, nodes_count);

    output_file.open("outputjoshua.txt");

    for (size_t i = 0; i != result.size(); i++) {
        output_file << result[i] << "\n";
    }
    output_file.close();

    return 0;
}
