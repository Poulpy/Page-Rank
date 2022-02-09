all:
	mkdir -p bin
	g++ src/wreivtof.cpp -o bin/wreivtof -Wall -g -O2
	g++ src/wrprettof.cpp -o bin/wrprettof -Wall -g -O2

clean:
	rm -rf bin
