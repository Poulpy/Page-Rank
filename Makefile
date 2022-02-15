all:
	mkdir -p bin
	g++ src/wreivtof.cpp -o bin/wreivtof -Wall -g -O2 -Wno-unknown-pragmas
	g++ src/wrprettof.cpp -o bin/wrprettof -Wall -g -O2 -Wno-unknown-pragmas
	g++ src/wrprettof.cpp -o bin/ompwrprettof -Wall -g -O2 -fopenmp

clean:
	rm -rf bin
