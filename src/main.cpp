#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <ctime>

#include "Matrix.hpp"

using namespace std;

/**
 *
 * https://isarth.github.io/pagerank/
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

    err = 123.0;
    for (size_t i = 0; i != max_iterations && err > epsilon; i++) {
        rlast = r;

        r = hat_m * r;

        err = 0.0;
        for (size_t j = 0; j != r.size(); j++) err += fabs(r[j] - rlast[j]);
    }

    return r;
}

/**
 */
double vector_norm(vector<double> v) {
    double result = 0.0;

    for (size_t i = 0; i != v.size(); i++) {
        result += v[i] * v[i];
    }

    return sqrt(result);
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

    MatrixD matrix = MatrixD::fill(nodes, nodes, 0.0);

    for (size_t i = 0; i != pairs.size(); i++) {
        // nodes often starts at 1, and the matrix index starts at 0, hence
        // the - 1
        matrix(pairs.at(i).second - 1, pairs.at(i).first - 1) = 1.0;
    }

    return matrix;
}

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
 * |R| = 1
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

    if (argc != 3) {
        cout << "Not enough parameters" << endl;
        return 0;
    }

    stringstream(argv[1]) >> input_file;
    stringstream(argv[2]) >> output_file;

    m = read_matrix_from_file(input_file);

    nodes = m.nCols();// or nRows()

    v = probability_distribution(nodes);
    for (size_t i = 0; i != v.size(); i++) cout << v[i] << ", "; cout << endl;

    tm = adjacency_list_to_transition_matrix(m);

    result = page_rank_power_method(tm, v, nodes);

    write_vector_to_file(result, output_file);

    return 0;
}

