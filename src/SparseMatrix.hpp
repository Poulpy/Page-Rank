#ifndef SPARSE_MATRIX_HPP
#define SPARSE_MATRIX_HPP

#include<tuple>
#include <bits/stdc++.h>

using namespace std;

class SparseMatrix {

    public:
        size_t len;
        vector<tuple<size_t, size_t, double>> tuples;

        SparseMatrix(size_t length, vector<tuple<size_t, size_t, double>> non_nulls) {
            len = length;
            tuples = non_nulls;
        }

        SparseMatrix to_transition_matrix() {
            return SparseMatrix(len, tuples);
        }

        string to_string() {
            stringstream str_strm;
            
            for (size_t i = 0; i != tuples.size(); i++) {
                str_strm << "(" << get<0>(tuples[i]) << ", " << get<1>(tuples[i]) << ", " << get<2>(tuples[i])
                         << ")" << endl;
            }

            return str_strm.str();

        }
};

#endif
