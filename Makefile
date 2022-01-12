all:
	mkdir -p bin
	g++ src/main.cpp -o bin/a.out -Wall -g -fopenmp -O2

clean:
	rm -rf bin
