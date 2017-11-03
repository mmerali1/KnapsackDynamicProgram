#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cstring>
#include <chrono>
#include <ctime>

using namespace std;
using namespace std::chrono;

//Data Structures
//Used to create and hold values of each Node in the graph
struct Node{
	int weight;
	int profit;
	int totProfit;
	int totWeight;
	int color; //0= white 1=gray 2= black
	int level;
	Node *left;
	Node *right;
	Node *parent;
	//Constructor to create Node
	Node(int w, int p, Node *par, int l){
		weight=w;
		profit=p;
		parent=par;
		color=0;
		level=l;
	}

};
//Used to hold each Items profit value and weight value
struct Item{
	int item_profit;
	int item_weight;

};

//Function signatures
int knapsack_backtrack(Node *root, Item *item, int maxW, int maxP, int n);
bool is_promising(Node *node, int maxW, int maxP, int n, Item *items);
float get_bound(int i, Item *items, int cap, Node node);
int findBest(Item ItemA[], int n, int maxW, Node* p, int maxP);
void sort_item_array(Item &item, int &numItems);
float pw_ratio(Item &item);


/*Depth First Search with Backtracking
Function determines the optimal solution to a 0/1 backtracking problem given a data set. It uses depth first search and recursively creates the tree. 
@param root (Node *) the initial node of the tree
@param item (Item *) set of all items for the given data set sorted in price / weight order
@param maxW (int) is the capacity that the knapsack can hold
@param maxP (int) is the maxmimum profit of the knapsack
@param n (int) is the number of items in the data set
*/
int knapsack_backtrack(Node *root, Item *item, int maxW, int maxP, int n){
	if ((root->weight <= maxW) && (root->profit > maxP)){
		maxP = root->profit;
	}
	if (is_promising(root, maxW, maxP, n, item)){
		//Creates left subtree
		root->left = new Node(root->weight + item[root->level+1].item_weight,
					root->profit + item[root->level+1].item_profit,
					 root, root->level+1);
		//Recursive call for left subtree
		maxP=max(maxP,knapsack_backtrack(root->left, item, maxW, maxP, n));
		//Free memory back to heap
		free(root->left);
		
		//Creates right subtree
		root->right = new Node(root->weight, root->profit, root, root->level+1);
		//Recursive call for right subtree
		maxP=max(maxP,knapsack_backtrack(root->right, item, maxW, maxP, n));
		//Free memory back to heap		
		free(root->right);
	}
	return maxP;
}

/*Sort Item Array
Takes in an unsorted Item array by reference and sorts it using insertion sort algorithm. 
@param items (Item *) is unsorted item array
@param numItems (int) is the number of items in the array
*/
void sort_item_array(Item *items, int &numItems){
	for (int i=1; i<numItems; i++){
		Item key = items[i];	//Key holds the first item to be compared
		int k = i-1;			//k holds the index of the second item being compared
		while(k>=0 && (pw_ratio(items[k]) < pw_ratio(key))){
			items[k+1] = items[k];
			k--;
		}
		items[k+1] = key;	
	}
}

/*Calculate P/W ratio of item and returns it. Helper function for the sort
@param item (Item) is a single item with price and weight values
*/
float pw_ratio(Item &item){
	return (((float)item.item_profit)/((float)item.item_weight));
}

/* Checks if node is promising. Returns true if so, else returns false
@param node (Node *) is the node from the tree
@param maxW (int) is the capacity that the knapsack can hold
@param maxP (int) is the maxmimum profit of the knapsack
@param n (int) is the number of items in the data set
@param item (Item *) set of all items for the given data set sorted in price / weight order
*/
bool is_promising(Node *node, int maxW, int maxP, int n, Item *items){
	if (node->weight >= maxW){
		return false;
	}
	//Calls bound function and saves it to float variable
	float bound = get_bound(n, items, maxW, *node); 
	return (bound > maxP);
}

/*Function that calculates bound for Backtracking
@param i (int) the number of items in the data set
@param items (Items *) is a pointer to the items array which have the profit and weight ratio
@param cap (int) is the capacity of the knapsack
@param node (Node) is the node that the bound is found for

*/
float get_bound(int i, Item *items, int cap, Node node){	//
	int a=0, b=0;	//a and b are used as indexes for the items array	
	int sumW = 0;	//Sum of the weight of the current items
	int bound = 0;	//bound of the input node
	if (node.weight >= cap){
		bound = 0;
	}
	else{
		bound = node.profit;
		a = node.level +1;
		sumW = node.weight;
		while((a < i) && ((sumW + items[a].item_weight) <= cap)){
			sumW += items[a].item_weight;
			bound += items[a].item_profit;
			a++;
		}
		b=a;
		if (b<i){
			bound += ((cap-sumW)*(items[b].item_profit/items[b].item_weight));
		}
	}
	return bound;
}

/* Depth First Search Brute Force Algorithm. Creates the entire knapsack tree and checks each node for the optimal solution to the problem. Returns optimal maximum profit for knapsack
@param ItemA (Item *) set of all items for the given data set sorted in price / weight order
@param n (int) is the number of items in the data set
@param maxW (int) is the capacity that the knapsack can hold
@param p (Node *) the initial node of the tree
@param maxP (int) is the maxmimum profit of the knapsack
*/
int findBest(Item ItemA[], int n, int maxW, Node* p, int maxP){
	int maxP2;
	if((p->color == 0) && (p->level<=n)){
		p->color=1;
		if (p->weight<=maxW && p->profit>maxP){
			maxP=p->profit;
			//cout << maxP endl;
			
		}
		if(p->level<n){
			
			Node *p2=new Node(p->weight + ItemA[p->level].item_weight,p->profit + ItemA[p->level].item_profit, p, p->level+1);
			//p->left=p2;
			maxP2=findBest(ItemA,n,maxW,p2,maxP);
			if(maxP2>maxP) maxP=maxP2;
			free(p2);
		}
		else{
			p->color=2;
		}
	}
	if(p->color==1 && p->right == NULL){
		
		p->color=2;
		Node *p2=new Node(p->weight,p->profit, p, p->level+1);
		//p->right=p2;
		maxP2=findBest(ItemA,n,maxW,p2,maxP);
		if(maxP2>maxP) maxP=maxP2;
		free(p2);
	}
	if(p->color==2) return maxP;
			
}

int main(int argc,char* argv[]){
	//Parsing file for data set of Items (weight, profit), number of items, and knapsack capacity
	string input=argv[1];
	string in;
	int n,c,w,pro,count;
	ifstream myfile;
	myfile.open(input.c_str());
	getline(myfile,in);
	int pos=in.find(",");
	n=atoi(in.substr(0,pos).c_str());
	in.erase(0,pos+1);
	c=atoi(in.c_str());
	Item ItemA[n];
	count=0;
	while(getline(myfile,in)){
		pos=in.find(",");
		w=atoi(in.substr(0,pos).c_str());
		in.erase(0,pos+1);
		pro=atoi(in.c_str());
		ItemA[count].item_profit=pro;
		ItemA[count].item_weight=w;
		count++;
	}
	
	//sort array in profit over weight ratio
	sort_item_array(ItemA, n);
	
	//Depth First Search Using Bruteforce algorithm with timing
	//Creates root
	Node *p=new Node(0,0,NULL,0);
	//sets up timing variables	
	time_point<system_clock> start, end;
	start = system_clock::now();
	int opt_profit_brute = findBest(ItemA, n,c,p,0);
	end = system_clock::now();
	duration<double> elapsed_seconds = end-start;
	//Prints out optimal solution and runtime of algorithm
	cout << "Bruteforce Algorithm" << endl;
	cout << "Profit: " << opt_profit_brute << endl;
	cout<< "elapsed time: " << elapsed_seconds.count()<<endl;

	//Depth First Search Using Backtracking algorithm with timing
	//Creates root
	Node *bt_root = new Node(0,0,NULL,-1);
	//sets up timing variables
	start = system_clock::now();
	//function call
	int opt_profit_bt = knapsack_backtrack(bt_root, ItemA, c, 0, n);
	end = system_clock::now();
	elapsed_seconds = end-start;
	//prints out optimal solution and runtime	
	cout << "Backtracking Algorithm" << endl;
	cout << "Profit: " << opt_profit_bt << endl;	
	cout << "Time: " << elapsed_seconds.count() << endl;
	return 0;
 
}
