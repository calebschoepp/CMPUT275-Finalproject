CC=g++
CFLAGS=-c -Wall -std=c++11

test_algo_dfs: algo_dfs.o test_algo_dfs.o
	$(CC) algo_dfs.o test_algo_dfs.o -o test_algo_dfs

algo_dfs.o: algo_dfs.cpp algo_dfs.h
	$(CC) algo_dfs.cpp $(CFLAGS) -o algo_dfs.o

test_algo_dfs.o: test_algo_dfs.cpp algo_dfs.h
	$(CC) test_algo_dfs.cpp $(CFLAGS) -o test_algo_dfs.o

clean:
	rm -f algo_dfs.o test_algo_dfs.o test_algo_dfs