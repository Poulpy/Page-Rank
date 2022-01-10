all:
	mkdir -p bin
	g++ src/main.cpp -o bin/a.out -Wall -g -fopenmp

clean:
	rm -f bin
