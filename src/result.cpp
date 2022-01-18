#include "page_rank.hpp"

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

