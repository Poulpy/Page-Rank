all:
	mkdir -p bin
	g++ src/page_rank.hpp src/chart.cpp -o bin/a.out -Wall -g -O2 -fopenmp
	g++ src/page_rank.hpp src/result.cpp -o bin/result -Wall -g -O2 -fopenmp

clean:
	rm -rf bin
