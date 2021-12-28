#include <iostream>
#include <sstream>
#include <fstream>

#include <Eigen/SparseCore>

#define TEST_FILEPATH "../resources/email-Eu-core.txt"

using Eigen::SparseMatrix;
using namespace std;

typedef Eigen::Triplet<int> T;

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
    int maximum = 0;
    int i = 0;
    int n1 = 0, n2 = 0;

    while (fin >> n1 >> n2) {
        maximum = std::max(maximum, n1);
        maximum = std::max(maximum, n2);

        tripletList.push_back(T(n1, n2, 1));
        tripletList.push_back(T(n2, n1, 1));
    }

    cout << "Maximum is " << maximum << endl;

    SparseMatrix<unsigned> A(maximum + 1, maximum + 1);

    A.setFromTriplets(tripletList.begin(), tripletList.end());
    //std::cout << A << std::endl;
    fin.close();
}

