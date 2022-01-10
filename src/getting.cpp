#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>

#include "Matrix.hpp"
#define TEST_FILEPATH "../resources/email-Eu-core.txt"

using namespace std;
// using namespace simple_matrix;

int main() {
    std::ifstream file;
    std::ofstream output_file;
    vector<std::pair<int, int>> triplet_list;
    int maximum = 0;
    int n1 = 0, n2 = 0;
    unsigned nodes_count;

    file.open(TEST_FILEPATH);
    while (file >> n1 >> n2) {
        maximum = max(maximum, n1);
        maximum = max(maximum, n2);

        triplet_list.push_back( { n1, n2 });
        triplet_list.push_back( { n2, n1 });
    }
    file.close();
    //cout << triplet_list;

    //MatrixD m(2, 2, { 2, 2, 2, 2});

    //cout << m;

    return 0;
}
