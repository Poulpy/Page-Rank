#ifndef SPARSE_MATRIX_HPP
#define SPARSE_MATRIX_HPP

#include<tuple>
#include <bits/stdc++.h>

using namespace std;

class SparseMatrix {

    public:
        size_t len;
        vector<tuple<size_t, size_t, double>> tuples;

        /*
         * Initializes a sparse matrix.
         */
        SparseMatrix(size_t length, vector<tuple<size_t, size_t, double>> non_nulls) {
            len = length;
            tuples = non_nulls;
        }

        /*
         * Returns a copy of the matrix.
         */
        SparseMatrix copy() {
            return SparseMatrix(len, tuples);
        }

        /*
         * Converts the matrix into a transition matrix, and returns the result.
         */
        SparseMatrix to_transition_matrix() {
            SparseMatrix new_matrix = copy();
            vector<int> counts(len, 0);

            // count 1 in each column
            for (size_t i = 0; i != new_matrix.tuples.size(); i++) {
                double val = get<2>(new_matrix.tuples[i]);
                size_t col = get<1>(new_matrix.tuples[i]);

                if (val == 1.0) {
                    counts[col]++;
                }
            }

            // divide each element by the number of ones in the column
            for (size_t i = 0; i != new_matrix.tuples.size(); i++) {
                double val = get<2>(new_matrix.tuples[i]);
                size_t col = get<1>(new_matrix.tuples[i]);

                if (val == 1.0) {
                    get<2>(new_matrix.tuples[i]) = val / (float) counts[col];
                }
            }

            return new_matrix;
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
