#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

#include "page_rank.hpp"

#define LOWER_BOUND 0.1
#define UPPER_BOUND 1.0
#define PACE 0.02

/*
 * ./bin/wrprettof <filepath> <output_file>
 *
 *
 */
int main(int argc, char **argv) {
    string input_file, output_file;
    // execution time, damping
    vector<pair<int, double>> results;
    vector<double> eigen_vector;

    // Handle arguments

    if (argc < 3) {
        cout << "Not enough parameters, expected 2, got " << argc - 1 << endl;
        return 0;
    }

    stringstream(argv[1]) >> input_file;
    stringstream(argv[2]) >> output_file;

    SparseMatrix matrix = read_matrix_from_file(input_file);

    SparseMatrix transition_matrix = matrix.to_transition_matrix();

    // Run page rank for each damping factor
    for (double damping = LOWER_BOUND; damping <= UPPER_BOUND; damping += PACE) {
        auto start = chrono::steady_clock::now();
        eigen_vector = page_rank_power_method(transition_matrix, damping);
        auto end = chrono::steady_clock::now();

        results.push_back({ chrono::duration_cast<chrono::milliseconds>(end - start).count(), damping });
    }

    write_vector_of_pairs_to_file(results, output_file);

    return 0;
}
