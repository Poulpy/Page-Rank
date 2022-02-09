#include "page_rank.hpp"

int main() {
    SparseMatrix matrix = read_matrix_from_file("resources/imane.txt");

    cout << matrix.to_string() << endl;

    SparseMatrix transition_matrix = matrix.to_transition_matrix();

    cout << transition_matrix.to_string() << endl;

    vector<double> eigen_vector = page_rank_power_method(transition_matrix);

    write_vector_to_file("result.txt", eigen_vector);

    return 0;
}
