# Names: Robert Mah, Caleb Schoepp
# ID: 1532565, 1534577
# CCID: rjmah1, cwschoep
# CMPUT 275 , Winter 2019
# Arduino Sudoku Solver

CC = g++
CFLAGS = -c -Wall -std=c++11 -g -O2
OBJS = algo_backtracking.o test_algo_backtracking.o algo_human_heuristic.o test_algo_human_heuristic.o server.o consts_and_types.o serialport.o algo_dancing_links.o test_algo_dancing_links.o algo_improved_human_heuristic.o test_algo_improved_human_heuristic.o
LFLAGS = -std=c++11
EXECUTABLES = test_algo_backtracking test_algo_human_heuristic server test_algo_dancing_links test_algo_improved_human_heuristic

all: $(EXECUTABLES)

server: algo_human_heuristic.o algo_backtracking.o algo_dancing_links.o algo_improved_human_heuristic.o server.o serialport.o
	$(CC) algo_human_heuristic.o algo_backtracking.o algo_dancing_links.o algo_improved_human_heuristic.o server.o serialport.o $(LFLAGS) -o server

server.o: server.cpp serialport.o
	$(CC) server.cpp $(CFLAGS) -o server.o

consts_and_types.o: consts_and_types.h
	$(CC) consts_and_types.h $(CFLAGS) -o consts_and_types.o

test_algo_human_heuristic: algo_human_heuristic.o test_algo_human_heuristic.o
	$(CC) algo_human_heuristic.o test_algo_human_heuristic.o $(LFLAGS) -o test_algo_human_heuristic

algo_human_heuristic.o: algo_human_heuristic.cpp algo_human_heuristic.h consts_and_types.h
	$(CC) algo_human_heuristic.cpp $(CFLAGS) -o algo_human_heuristic.o

test_algo_human_heuristic.o: test_algo_human_heuristic.cpp algo_human_heuristic.h
	$(CC) test_algo_human_heuristic.cpp $(CFLAGS) -o test_algo_human_heuristic.o

test_algo_improved_human_heuristic: algo_improved_human_heuristic.o test_algo_improved_human_heuristic.o
	$(CC) algo_improved_human_heuristic.o test_algo_improved_human_heuristic.o algo_backtracking.o $(LFLAGS) -o test_algo_improved_human_heuristic

algo_improved_human_heuristic.o: algo_improved_human_heuristic.cpp algo_improved_human_heuristic.h consts_and_types.h algo_backtracking.h
	$(CC) algo_improved_human_heuristic.cpp $(CFLAGS) -o algo_improved_human_heuristic.o

test_algo_improved_human_heuristic.o: test_algo_improved_human_heuristic.cpp algo_improved_human_heuristic.h
	$(CC) test_algo_improved_human_heuristic.cpp $(CFLAGS) -o test_algo_improved_human_heuristic.o

test_algo_backtracking: algo_backtracking.o test_algo_backtracking.o
	$(CC) algo_backtracking.o test_algo_backtracking.o $(LFLAGS) -o test_algo_backtracking

algo_backtracking.o: algo_backtracking.cpp algo_backtracking.h consts_and_types.h
	$(CC) algo_backtracking.cpp $(CFLAGS) -o algo_backtracking.o

test_algo_backtracking.o: test_algo_backtracking.cpp algo_backtracking.h
	$(CC) test_algo_backtracking.cpp $(CFLAGS) -o test_algo_backtracking.o

test_algo_dancing_links: algo_dancing_links.o test_algo_dancing_links.o
	$(CC) algo_dancing_links.o test_algo_dancing_links.o $(LFLAGS) -o test_algo_dancing_links

algo_dancing_links.o: algo_dancing_links.cpp algo_dancing_links.h
	$(CC) algo_dancing_links.cpp $(CFLAGS) -o algo_dancing_links.o

test_algo_dancing_links.o: test_algo_dancing_links.cpp algo_dancing_links.h
	$(CC) test_algo_dancing_links.cpp $(CFLAGS) -o test_algo_dancing_links.o

serialport.o: serialport.h serialport.cpp
	$(CC) serialport.cpp $(CFLAGS) -o serialport.o

clean:
	rm -f $(OBJS) $(EXECUTABLES)
