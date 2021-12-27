#include <iostream>
#include <Eigen/SparseCore>

using Eigen::SparseMatrix;
typedef Eigen::Triplet<double> T;

int main() {
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

