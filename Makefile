all:
	mkdir -p bin
	g++ src/main2.cpp -o bin/a.out -Wall -g -fopenmp

clean:
	rm -rf bin
