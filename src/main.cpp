#include <iostream>
#include <sstream>
#include <fstream>

#include <Eigen/SparseCore>

#define TEST_FILEPATH "../resources/email-Eu-core.txt"

using Eigen::SparseMatrix;
using Eigen::VectorXd;
using namespace std;

typedef Eigen::Triplet<int> T;

VectorXd page_rank_power_method(SparseMatrix<double> matrix,
                                unsigned nodes_count, double d,
                                int max_iterations, double epsilon) {

    VectorXd v(nodes_count);
    for (int i = 0; i != nodes_count; i++) v[i] = 1 / nodes_count;
    VectorXd v_last(nodes_count);
    int err;

    for (size_t i = 0; i != max_iterations; i++) {
        v_last = v;
        v = matrix * v;
        err = 0;

        for (size_t j = 0; j != nodes_count; j++) {
            err += err + std::fabs(v[j] - v_last[j]);
        }

        if (err < epsilon) {
            return v;
        }
    }

    return v;
}

/**
 * d = 0.15, damping factor
 * max = 100, maximum iterations
 * eps = 1.10⁻9
 */
int main(int argc, char **argv) {

    double d;
    unsigned max;
    double eps;

    if (argc < 4) {
        d = 0.15;
        max = 100;
        eps = 0.000001;
    } else {
        stringstream(argv[1]) >> d;
        stringstream(argv[2]) >> max;
        stringstream(argv[3]) >> eps;
    }


    std::cout << d << std::endl;
    std::cout << max << std::endl;
    std::cout << eps << std::endl;

    
    // File pointer
    std::ifstream fin(TEST_FILEPATH);
  
    std::vector<T> tripletList;
    tripletList.reserve(2000);

    // https://www.geeksforgeeks.org/csv-file-management-using-c/
    // Read the Data from the file
    // as String Vector
    vector<string> row;
    string line, word, temp;
    double maximum = 0.0;
    int i = 0;
    double n1 = 0.0, n2 = 0.0;

    while (fin >> n1 >> n2) {
        maximum = std::max(maximum, n1);
        maximum = std::max(maximum, n2);

        tripletList.push_back(T(n1, n2, 1));
        tripletList.push_back(T(n2, n1, 1));
    }

    cout << "Maximum is " << maximum << endl;

    unsigned nodesCount = maximum + 1;

    // +1 is needed, don't ask me why
    SparseMatrix<double> A(maximum + 1, maximum + 1);

    A.setFromTriplets(tripletList.begin(), tripletList.end());
    //std::cout << A << std::endl;
    fin.close();

    VectorXd v = page_rank_power_method(A, nodesCount, d, max, eps);
}


