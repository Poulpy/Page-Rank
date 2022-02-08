all:
	mkdir -p bin
	g++ src/page_rank.hpp src/chart.cpp -o bin/a.out -Wall -g -O2 -fopenmp
	g++ src/page_rank.hpp src/result.cpp -o bin/result -Wall -g -O2 -fopenmp

sparse:
	mkdir -p bin
	g++ src/SparseMatrix.hpp src/test_sparse_matrix.cpp -o bin/sparse -Wall -g -O2

clean:
	rm -rf bin
