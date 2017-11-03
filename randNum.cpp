#include <stdlib.h>
#include <stdio.h>  
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


/*
Generate random data sets that can be used for 0/1 knapsack problems
@param filename (string) name of file being written to
@param numItems (int) number of items in data set
@param maxW (int) upper weight bound
@param maxP (int) upper profit bound
@param minW (int) lower weight bound
@param minP (int) lower profit bound
*/
void generateRand(string filename, int numItems,int maxW, int maxP, int minW, int minP){
	//used for weight and profit of item	
	int weight,profit;
	srand(time(NULL));
	ofstream myfile;
	myfile.open(filename);
	myfile<<numItems<<","<<maxW<<endl;
	for (int i=0;i<numItems;i++){
	  weight= rand() % (maxW - (minW-1)) + minW;
	  profit= rand() % (maxP - (minP-1)) + minP;
	  myfile<<weight<<","<<profit<<endl;
	}
}

int main(){
	generateRand("t1.txt", 5,20,50,1,1);
	generateRand("t2.txt", 10,40,50,1,1);
	generateRand("t3.txt", 15,60,50,1,1);
	generateRand("t4.txt", 20,80,50,1,1);
	generateRand("t5.txt", 25,100,50,1,1);	
	generateRand("t7.txt", 30,120,50,1,1);
	return 0;
}
