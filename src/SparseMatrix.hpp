#ifndef SPARSE_MATRIX_HPP
#define SPARSE_MATRIX_HPP

#include <tuple>
#include <bits/stdc++.h>

using namespace std;

/*
 * Implementation of a sparse matrix, using an array of
 * triplets : (row, column, value). The other values are
 * zeros.
 */
class SparseMatrix {

    public:

        // Dimension of the matrix: row and column.
        size_t len;

        // Tuples of data (row, column, value).
        vector<tuple<size_t, size_t, double>> tuples;

        /*
         * Initializes a sparse matrix.
         *
         * Example:
         *     vector<tuple<size_t, size_t, double>> values = { make_tuple(0, 1, 1.0) };
         *     SparseMatrix matrix = SparseMatrix(2, values);
         */
        SparseMatrix(size_t length, vector<tuple<size_t, size_t, double>> non_nulls) {
            len = length;
            tuples = non_nulls;
        }

        /*
         * Returns a copy of the matrix.
         *
         * Example:
         *     SparseMatrix matrix_copied = matrix.copy();
         */
        SparseMatrix copy() {
            return SparseMatrix(len, tuples);
        }

        /*
         * Converts the matrix into a transition matrix, and returns the result.
         *
         * Complexity: O(2n), with n the size of tuples.
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

        /*
         * Product matrix-vector. Returns the result.
         *
         * Example:
         *     vector<double> result = matrix.dot(v);
         *
         * Complexity: O(n), with n the size of tuples.
         */
        vector<double> dot(vector<double> v) {
            vector<double> rst(v.size(), 0.0);

            #pragma omp parallel for
            for (size_t i = 0; i != tuples.size(); i++) {
                size_t row = get<0>(tuples[i]);
                size_t col = get<1>(tuples[i]);
                double val = get<2>(tuples[i]);

                rst.at(row) += val * v.at(col);
            }

            return rst;
        }

        /*
         * Returns a prettified format of the matrix. For debug purposes.
         *
         * Complexity: O(n), with n the size of tuples.
         */
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
