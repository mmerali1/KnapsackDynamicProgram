FLAGS = -Wall -std=c++11 -g 

all:  dfs data

dfs: DFSprog.o
	g++ $(FLAGS) DFSprog.o -o dfs

data: data.o
	g++ $(FLAGS) data.o -o data

data.o: randNum.cpp
	g++ $(FLAGS) -c randNum.cpp -o data.o

DFSprog.o: DFSprog.cpp
	g++ $(FLAGS) -c DFSprog.cpp -o DFSprog.o

clean:
	rm -f *.o dfs data
