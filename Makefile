all:
	mkdir -p bin
	g++ -I /usr/local/include/eigen3/ src/main.cpp -o bin/a.out

clean:
	rm -f bin
