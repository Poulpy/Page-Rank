
#include "SparseMatrix.hpp"

SparseMatrix read_matrix_from_file(string filepath) {
    std::ifstream file;
    vector<tuple<size_t, size_t, double>> tuples;
    int n1, n2;
    int nodes = 0;

/*    cout << "read_matrix_from_file" << endl;
*/
    file.open(filepath);
    while (file >> n1 >> n2) {

        nodes = max(nodes, n1);
        nodes = max(nodes, n2);

/*        cout << ">" << n1 << ", " << n2 << endl;
*/
        tuples.push_back({ n1, n2, 1.0 });
    }
    file.close();

/*    cout << tuples.size() << endl;
*/
    return SparseMatrix(nodes + 1, tuples);
}

int main() {
    SparseMatrix matrix = read_matrix_from_file("resources/imane.txt");

    cout << matrix.to_string() << endl;

    return 0;
}
