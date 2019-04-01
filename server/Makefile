CC = g++
CFLAGS = -c -Wall -std=c++11 -g -O2
OBJS = algo_backtracking.o test_algo_backtracking.o algo_human_heuristic.o
LFLAGS = -std=c++11
EXECUTABLES = test_algo_backtracking test_algo_human_heuristic

all: $(EXECUTABLES)

test_algo_human_heuristic: algo_human_heuristic.o test_algo_human_heuristic.o
	$(CC) algo_human_heuristic.o test_algo_human_heuristic.o $(LFLAGS) -o test_algo_human_heuristic

algo_human_heuristic.o: algo_human_heuristic.cpp algo_human_heuristic.h
	$(CC) algo_human_heuristic.cpp $(CFLAGS) -o algo_human_heuristic.o

test_algo_human_heuristic.o: test_algo_human_heuristic.cpp algo_human_heuristic.h
	$(CC) test_algo_human_heuristic.cpp $(CFLAGS) -o test_algo_human_heuristic.o

test_algo_backtracking: algo_backtracking.o test_algo_backtracking.o
	$(CC) algo_backtracking.o test_algo_backtracking.o $(LFLAGS) -o test_algo_backtracking

algo_backtracking.o: algo_backtracking.cpp algo_backtracking.h
	$(CC) algo_backtracking.cpp $(CFLAGS) -o algo_backtracking.o

test_algo_backtracking.o: test_algo_backtracking.cpp algo_backtracking.h
	$(CC) test_algo_backtracking.cpp $(CFLAGS) -o test_algo_backtracking.o

test_algo_dancing_links: algo_dancing_links.o test_algo_dancing_links.o
	$(CC) algo_dancing_links.o test_algo_dancing_links.o $(LFLAGS) -o test_algo_dancing_links

algo_dancing_links.o: algo_dancing_links.cpp algo_dancing_links.h
	$(CC) algo_dancing_links.cpp $(CFLAGS) -o algo_dancing_links.o

test_algo_dancing_links.o: test_algo_dancing_links.cpp algo_dancing_links.h
	$(CC) test_algo_dancing_links.cpp $(CFLAGS) -o test_algo_dancing_links.o

clean:
	rm -f $(OBJS) $(EXECUTABLES)
