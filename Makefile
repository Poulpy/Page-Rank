all:
	mkdir -p bin
	g++ src/wreivtof.cpp -o bin/wreivtof -Wall -g -O2
	g++ src/test_sparse_matrix.cpp -o bin/sparse -Wall -g -O2

clean:
	rm -rf bin
