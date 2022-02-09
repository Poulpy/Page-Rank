#include "page_rank.hpp"

/*
 * ./bin/wreivtof <filepath> <output_file> [damping]
 * Damping factor is 0.85 by default.
 * The eigen vector (the result) is written to output file
 */
int main(int argc, char **argv) {
    string input_file, output_file;
    double damping = 0.85;

    // Handle arguments
    
    if (argc < 3) {
        cout << "Not enough parameters, expected at least 2, got " << argc - 1 << endl;
        return 0;
    }

    stringstream(argv[1]) >> input_file;
    stringstream(argv[2]) >> output_file;

    if (argc > 3) stringstream(argv[3]) >> damping;

    // Page rank

    SparseMatrix matrix = read_matrix_from_file(input_file);

    SparseMatrix transition_matrix = matrix.to_transition_matrix();

    vector<double> eigen_vector = page_rank_power_method(transition_matrix, damping);

    write_vector_to_file(output_file, eigen_vector);

    return 0;
}
