Program written by Mehdi Merali and Corey Cook
	Contributions -Mehdi Merali wrote the backtracking algorithm
		      -Corey Cook wrote the bruteforce algorithm



HOW TO COMPILE PROGRAM
1-Navigate to correct directory with source code, test files, and makefile
2-Enter "make" into terminal
3- Use shell scripts to run data sets for Random data, Small tree data, and Full tree data
	Random data		./runRandData.sh
	Small tree data		./runSmallSata.sh
	Full tree data		./runFullData.sh
4- For correctness tests run:
	./dfs correct1.txt or ./dfs correct2.txt
5- For any other data set: ./dfs <TEXT FILE WITH KNAPSACK DATA>
6- To clean: make clean

DATA STRUCTURES
-Node is a struct which holds information on each node of the tree. It keeps track of depth, profit, weight, children pointers, and parent pointers. Used to create the graph for the problem
-Item is a struct that holds the profit and weight of each item. It is used to pass through arrays of items while only using one array pointer. 

ANALYSIS
sort function runs in O(n^2)
Backtracking algorithm runs in O(2^n) worst case
Bruteforce algorithm runs in O(2^n) always

CLASSES USED
	iostream - used for printing data
	fstream - used for parsing data files
	string - used for certain function max()
	chrono - used to time algorithms


INFORMATION ON DATA SET FILES
	Layout
		line 0: 		number of items, capacity
		line 1 thru end:	item weight, item profit
	
	Types of Data Sets
		Random -files with data sets from 5 items to 30 items in increments of 5
		Full Tree -files with data sets from 5 items to 30 items in increments of 5
		Small Tree -files with data sets from 5 items to 30 items in increments of 5
		Correctness -2 data sets that test this

