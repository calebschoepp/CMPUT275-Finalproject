CC=g++
CFLAGS=-c -Wall -std=c++11 -g

test_algo_backtracking: algo_backtracking.o test_algo_backtracking.o
	$(CC) algo_backtracking.o test_algo_backtracking.o -o test_algo_backtracking

algo_backtracking.o: algo_backtracking.cpp algo_backtracking.h
	$(CC) algo_backtracking.cpp $(CFLAGS) -o algo_backtracking.o

test_algo_backtracking.o: test_algo_backtracking.cpp algo_backtracking.h
	$(CC) test_algo_backtracking.cpp $(CFLAGS) -o test_algo_backtracking.o

clean:
	rm -f algo_backtracking.o test_algo_backtracking.o test_algo_backtracking