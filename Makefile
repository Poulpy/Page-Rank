all:
	mkdir -p bin
	g++ src/page_rank.hpp src/chart.cpp -o bin/a.out -Wall -g -fopenmp -O2
	g++ src/page_rank.hpp src/result.cpp -o bin/result -Wall -g -fopenmp -O2

clean:
	rm -rf bin
