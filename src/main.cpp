#include <iostream>
#include <sstream>

#include <Eigen/SparseCore>

using Eigen::SparseMatrix;
using namespace std;

typedef Eigen::Triplet<double> T;

/**
 * d = 0.15, damping factor
 * max = 100, maximum iterations
 * eps = 1.10⁻9
 */
int main(int argc, char **argv) {

    if (argc < 4) {
        std::cout << "Less than 4 arguments, run with :" << std::endl;
        std::cout << "./a.out <d> <max> <eps>" << std::endl;

        return 0;
    }

    double d;
    unsigned max;
    double eps;

    stringstream(argv[1]) >> d;
    stringstream(argv[2]) >> max;
    stringstream(argv[3]) >> eps;

    std::cout << d << std::endl;
    std::cout << max << std::endl;
    std::cout << eps << std::endl;

    std::vector<T> tripletList;
    tripletList.reserve(4);
    tripletList.push_back(T(0,0, 3.0));
    tripletList.push_back(T(1,0, 2.5));
    tripletList.push_back(T(0,1, -1.0));
    tripletList.push_back(T(1,1, 56.4));

    SparseMatrix<double> A(2, 2);
    A.setFromTriplets(tripletList.begin(), tripletList.end());
    std::cout << A << std::endl;
}

