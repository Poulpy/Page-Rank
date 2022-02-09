
#include "SparseMatrix.hpp"

/*
 * Reads a graph from a file and returns the sparse matrix
 * of it.
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
        for (size_t k = 0; k != r.size(); k++) r.at(k) = damping * r.at(k) + jumping / len;

        err = 0.0;
        for (size_t j = 0; j != r.size(); j++) err += fabs(r[j] - rlast[j]);
    }

    return r;
}

void write_vector_to_file(string filepath, vector<double> v) {
    std::ofstream output_file;
    output_file.open(filepath);

    for (size_t i = 0; i != v.size(); i++) {
        output_file << v[i] << "\n";
    }

    output_file.close();
}

int main() {
    SparseMatrix matrix = read_matrix_from_file("resources/imane.txt");

    cout << matrix.to_string() << endl;

    SparseMatrix transition_matrix = matrix.to_transition_matrix();

    cout << transition_matrix.to_string() << endl;

    vector<double> eigen_vector = page_rank_power_method(transition_matrix);

    write_vector_to_file("result.txt", eigen_vector);

    return 0;
}
