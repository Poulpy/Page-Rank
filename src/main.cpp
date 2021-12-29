#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>

#include <Eigen/SparseCore>

#define TEST_FILEPATH "../resources/email-Eu-core.txt"

using Eigen::SparseMatrix;
using Eigen::VectorXd;
using namespace std;

typedef Eigen::Triplet<int> T;

void page_rank_power_method_process(string graph_filepath,
                                    string output_filepath, double damping,
                                    int max_iterations, double epsilon);

VectorXd page_rank_power_method(SparseMatrix<double> matrix,
                                unsigned nodes_count, double d,
                                int max_iterations, double epsilon);

/**
 * Reads a graph from a file and writes the eigenvector to a file
 */
void page_rank_power_method_process(string graph_filepath,
                                    string output_filepath, double damping,
                                    int max_iterations, double epsilon) {

    std::ifstream file(graph_filepath);
    std::vector<T> triplet_list;
    VectorXd v;
    double maximum = 0.0;
    double n1 = 0.0, n2 = 0.0;
    unsigned nodes_count;

    // that's a random number, could be anything as long as it's big
    triplet_list.reserve(2000);

    while (file >> n1 >> n2) {
        maximum = std::max(maximum, n1);
        maximum = std::max(maximum, n2);

        triplet_list.push_back(T(n1, n2, 1));
        triplet_list.push_back(T(n2, n1, 1));
    }
    file.close();

    nodes_count = maximum + 1;

    // +1 is needed, don't ask me why
    SparseMatrix<double> graph(maximum + 1, maximum + 1);

    graph.setFromTriplets(triplet_list.begin(), triplet_list.end());

    v = page_rank_power_method(graph, nodes_count, damping, max_iterations,
                               epsilon);

    // TODO write to file
    ofstream output_file;
    output_file.open(output_filepath);
    for (auto i = 0; i != v.size(); i++) {
        output_file << v(i) << "\n";
    }
    //std::ostream_iterator<std::string> output_iterator(output_file, "\n");
    //std::copy(v.begin(), v.end(), output_iterator);
    output_file.close();
}

/**
 * Page rank algorithm with the power method
 *
 * matrix: adjacency list of the graph
 * d: damping
 * max_iterations:
 * epsilon:
 */
VectorXd page_rank_power_method(SparseMatrix<double> matrix,
                                unsigned nodes_count, double d,
                                int max_iterations, double epsilon) {

    VectorXd v(nodes_count);
    for (size_t i = 0; i != nodes_count; i++) v[i] = 1.0 / nodes_count;
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

    page_rank_power_method_process(TEST_FILEPATH, "output.txt", d, max, eps);
}


