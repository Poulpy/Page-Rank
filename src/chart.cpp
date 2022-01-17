#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

#include "page_rank.hpp"

using namespace std;

int main(int argc, char **argv) {
    string input_file, output_file;
    size_t nodes;
    vector<double> v, result;
    MatrixD m, tm;
    double damping = 0.05;
    vector<int> times;
    vector<double> dampings;
    vector<pair<int, double>> results;

    if (argc < 3) {
        cout << "Not enough parameters" << endl;
        return 0;
    }

    stringstream(argv[1]) >> input_file;
    stringstream(argv[2]) >> output_file;

    m = read_matrix_from_file(input_file);

    nodes = m.nCols();// or nRows()

    v = probability_distribution(nodes);

    tm = adjacency_list_to_transition_matrix(m);

    for (; damping <= 0.95; damping += 0.05) {
        auto start = chrono::steady_clock::now();
        result = page_rank_power_method(tm, v, nodes, damping);
        auto end = chrono::steady_clock::now();
        results.push_back({ chrono::duration_cast<chrono::milliseconds>(end - start).count(), damping });
    }

    write_vectors_to_file(results, output_file);

    return 0;
}

