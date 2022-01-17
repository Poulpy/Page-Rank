all:
	mkdir -p bin
	g++ src/page_rank.hpp src/chart.cpp -o bin/a.out -Wall -g -fopenmp -O2

clean:
	rm -rf bin
