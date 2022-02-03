# Page rank

Simple implementation of the page rank algorithm, more specifically the power
method. The matrix implementation is done by [@douglasrizzo](https://github.com/douglasrizzo/matrix).

## Compilation

```
make

./bin/a.out <input_file> <output_file>
```

## Execute for a given damping

```
./bin/result resources/p2p-Gnutella08.txt resources/p2p-Gnutella08.85.txt 0.85
```

## Plot of execution time

```
./bin/a.out resources/p2p-Gnutella08.txt resources/p2p-Gnutella08.result.txt
gnuplot -c scripts/chart.gp resources/p2p-Gnutella08.result.txt > resources/p2p-Gnutella08.png
```

# TODO


