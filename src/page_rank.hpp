#ifndef PAGE_RANK_HPP
#define PAGE_RANK_HPP

#include <numeric>

#include "SparseMatrix.hpp"

/*
 * Reads a graph from a file and returns the sparse matrix
 * of it.
 *
 * Example:
 *     SparseMatrix m = read_matrix_from_file("graphe.txt");
 *
 * Complexity: O(n), with n the number of edges.
 */
SparseMatrix read_matrix_from_file(string filepath) {
    std::ifstream file;
    vector<tuple<size_t, size_t, double>> tuples;
    int n1, n2;
    int nodes = 0;

    file.open(filepath);
    while (file >> n1 >> n2) {
        nodes = max(nodes, n1);
        nodes = max(nodes, n2);

        tuples.push_back({ n1, n2, 1.0 });
    }

    file.close();

    return SparseMatrix(nodes + 1, tuples);
}

/*
 * Page rank implementation using a sparse matrix.
 *
 * transition_matrix: a transition matrix, ie a 2D array showing the probability
 *                    of walking from a node A to a node B
 * damping: factor indicating if the walker should take a link/edge from the graph
 * max_iterations: number of maximum walks in the graph
 * epsilon: the precision error
 *
 * Example:
 *     SparseMatrix m = read_matrix_from_file("graphe.txt");
 *     vector<double> v = page_rank_power_method(transition_matrix);
 *
 * Complexity: O(max_iterations * (2n + m))
 *             with n the number of tuples, m the size of the matrix.
 */
vector<double> page_rank_power_method(SparseMatrix transition_matrix, double damping = 0.85,
                                      size_t max_iterations = 100, double epsilon = 0.0000001) {

    double err;
    size_t len = transition_matrix.len;
    vector<double> r(len, 1.0 / (float) len), rlast(len);
    double jumping = 1.0 - damping;

    err = 10.0;// random number, must be > 0 at start
    for (size_t i = 0; i != max_iterations && err > epsilon; i++) {
        rlast = r;

        r = transition_matrix.dot(rlast);
        
        #pragma omp parallel for
        for (size_t k = 0; k != r.size(); k++) r.at(k) = damping * r.at(k) + jumping / len;

        err = 0.0;
        #pragma omp parallel for
        for (size_t j = 0; j != r.size(); j++) err += fabs(r[j] - rlast[j]);
    }

    return r;
}

/*
 * Writes a vector to a file. Adds a newline to each element.
 * 
 * Example:
 *     vector<double> v = { 1.0, 2.0 };
 *     write_vector_to_file("vec.txt", v);
 * 
 * Complexity: O(|v|)
 */
void write_vector_to_file(string filepath, vector<double> v) {
    std::ofstream output_file;
    output_file.open(filepath);
    string newline = "\n";

    for (size_t i = 0; i != v.size(); i++) {
        output_file << v[i] << newline;
    }

    output_file.close();
}

/*
 * Writes a vector of pairs to a file. Adds a newline to each element.
 *
 * Complexity: O(|v|)
 */
void write_vector_of_pairs_to_file(vector<pair<int, double>> v, string filepath) {
    std::ofstream output_file;
    output_file.open(filepath);
    string separator = " ";

    for (size_t i = 0; i != v.size(); i++) {
        output_file << v[i].first << separator << v[i].second << "\n";
    }

    output_file.close();
}

/*
 * Compares 2 doubles with a precision error. The precision error is 0.1.
 *
 * Example:
 *     assert(doublecmpr(1.0, 0.91));
 *     assert(!doublecmpr(1.0, 0.81));
 */
bool doublecmpr(double a, double b) {
    return fabs(a - b) <= 0.1;
}

/*
 * Checks if a vector is normalized, ie the sum of its elements is 1 (nearly).
 */
bool is_vector_normalized(vector<double> v) {
    double sum = accumulate(v.begin(), v.end(), 0.0);

    return doublecmpr(sum, 1.0);
}

#endif
