#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

#include "Matrix.hpp"

using namespace std;

/**
 * Page rank implementation method
 *
 * reference: https://isarth.github.io/pagerank/
 *            wikipedia article on page rank
 */
vector<double> page_rank_power_method(MatrixD transition_matrix,
                                      vector<double> v, size_t nodes,
                                      double damping = 0.85,
                                      size_t max_iterations = 100,
                                      double epsilon = 0.0001) {

    double err;
    vector<double> r(nodes), rlast(nodes);
    MatrixD hat_m(nodes, nodes), e;

    r = v;
    e = MatrixD::fill(nodes, nodes, 1);// matrix of all ones

    hat_m = damping * transition_matrix + ((1 - damping) / nodes) * e;

    err = 123.0;// random number, must be > 0 at start
    for (size_t i = 0; i != max_iterations && err > epsilon; i++) {
        rlast = r;

        r = hat_m * r;

        err = 0.0;
        for (size_t j = 0; j != r.size(); j++) err += fabs(r[j] - rlast[j]);
    }

    return r;
}

/**
 * to adjacency list of a stochastic matrix
 */
MatrixD read_matrix_from_file(string filepath) {
    std::ifstream file;
    vector<std::pair<int, int>> pairs;
    int n1, n2;
    int nodes = 0;

    file.open(filepath);
    while (file >> n1 >> n2) {
        nodes = max(nodes, n1);
        nodes = max(nodes, n2);

        pairs.push_back({ n1, n2 });
    }
    file.close();

    MatrixD matrix = MatrixD::fill(nodes + 1, nodes + 1, 0.0);

    for (size_t i = 0; i != pairs.size(); i++) {
        // OLD: nodes often starts at 1, and the matrix index starts at 0,
        // hence the - 1
        matrix(pairs.at(i).second, pairs.at(i).first) = 1.0;
    }

    return matrix;
}

/**
 * Converts an adjacency list to a transition matrix
 * We divide the links (1) with the number of neighbours
 * The matrix must be column stochastic
 */
MatrixD adjacency_list_to_transition_matrix(MatrixD m) {
    int count;
    MatrixD result = m;

    for (size_t i = 0; i != m.nCols(); i++) {
        count = 0;
        for (size_t j = 0; j != m.nRows(); j++) {
            if (result(j, i) == 1.0) {
                count++;
            }
        }

        for (size_t j = 0; j != m.nRows(); j++) {
            if (result(j, i) == 1.0) {
                result(j, i) = result(j, i) / count;
            }
        }
    }

    return result;
}

/**
 * Writes a vector to a file
 */
void write_vector_to_file(vector<double> v, string filepath) {
    std::ofstream output_file;
    output_file.open(filepath);

    for (size_t i = 0; i != v.size(); i++) {
        output_file << v[i] << "\n";
    }

    output_file.close();
}

/**
 * Returns a vector filled with the value 1/size. The sum of all elements then
 * is 1
 */
vector<double> probability_distribution(size_t size) {
    vector<double> v(size);

    for (size_t i = 0; i != v.size(); i++) v[i] = 1.0 / size;

    return v;
}

int main(int argc, char **argv) {
    string input_file, output_file;
    size_t nodes;
    vector<double> v, result;
    MatrixD m, tm;
    double damping = 0.85;

    if (argc < 3) {
        cout << "Not enough parameters" << endl;
        return 0;
    }

    stringstream(argv[1]) >> input_file;
    stringstream(argv[2]) >> output_file;
    if (argc > 3) stringstream(argv[3]) >> damping;

    m = read_matrix_from_file(input_file);

    nodes = m.nCols();// or nRows()

    v = probability_distribution(nodes);

    tm = adjacency_list_to_transition_matrix(m);

    auto start = chrono::steady_clock::now();
    result = page_rank_power_method(tm, v, nodes, damping);
    auto end = chrono::steady_clock::now();

    write_vector_to_file(result, output_file);
    cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() <<" milliseconds" << endl;

    return 0;
}

