

#include "exception.h"
#include "Disjoint_sets.h"
#include "Weighted_graph.h"

#include <iostream>


using namespace std;


int main(){
	
	int n = 3;
	
	const int test = n;
	
	int * array = new int[test];
	
	Weighted_graph G1(10);
	
	Weighted_graph G2(0);
	
	try{
		Weighted_graph G3(-2);
	}catch(illegal_argument e){
		cout <<  "Exception caught" << endl;
	}
	
	cout << "Degree count for node 0 should yield 0: " << G1.degree(0) << endl;	
	cout << "Edge count should yield 0: " << G1.edge_count() << endl;
	
	// test edge insert
	cout << "(1,1, 1) should yield false " << G1.insert_edge(1,1, 1) << endl;
	
	try{
		G1.insert_edge(-2,-2, 1);
	}catch (illegal_argument e){
		cout << "G1.insert(-2,-2, 1) exception caught " << endl;	
	}
	
	try{
		G1.insert_edge(0,1, -1);
	}catch (illegal_argument e){
		cout << "G1.insert(0,1, -1) exception caught " << endl;	
	}
	
	cout << "G1.insert_edge(0,1,1) should yield true "  << G1.insert_edge(0,1,1) << endl;
	
	
		
	// test degrees
	cout << "G1.degree(0) should yield 1: " << G1.degree(0) << endl;
	
	// test edge_count
	
	cout << "G1.edge_count should yield 1: " << G1.edge_count() << endl; 
	
	// test edge erase
	
	cout << "G1.erase_edge(0,0) should yield false " << G1.erase_edge(0,0) << endl;
	
	try{
		G1.erase_edge(-1, -1);
	}catch (illegal_argument e){
		cout << "G1.erase_edge(-1,-1) exception caught " << endl;	
	}
	
	cout << "G1.erase_edge(1,0) should yield true " << G1.erase_edge(1,0) << endl;
	
		
	cout << "G1.edge_count should yield 0: " << G1.edge_count() << endl; 

	
	cout << "G1.insert_edge(0,1,1) should yield true: "  << G1.insert_edge(0,1,1) << endl;

	G1.clear_edges();
	
	cout << "After G1.clear_edges(), edge count should be 0: "  << G1.edge_count() << endl; 
	
	
	// Test disjoint sets
	Disjoint_set S(4);
	cout << "Find set rep for node 0 should be 0: " << S.find_set(0) << endl;
	
	cout << "Number of sets should be 4: " << S.num_sets() << endl;
	
	cout << "After unioning 0 and 1" << endl;
	S.union_sets(0,1);
	
	cout << "Find set rep for node 1 should be 0: " << S.find_set(1) << endl;
		
	cout << "Number of sets should be 3: " << S.num_sets() << endl;
	
	cout << "Unioning two nodes in the same set 0, 1 " << endl;
	S.union_sets(0,1);
	cout << "Number of sets should be 3: " << S.num_sets() << endl;
	cout << "Node 1 should be in set repped by node 0: " << S.find_set(1) << endl;
		
	cout << "After unioning 0 and 2" << endl;
	S.union_sets(0,2);
	cout << "Number of sets should be 2 " << S.num_sets() << endl;
	cout << "Node 2 should be in set repped by node 0: " << S.find_set(2) << endl;
	cout << "Node 3 should be in set repped by node 3: " << S.find_set(3) << endl;
		
	cout << "After unioning 0 and 3" << endl;
	S.union_sets(0,3);
	cout << "Number of sets should be 1: " << S.num_sets() << endl;
	cout << "Node 3 should be in set repped by node 0: " << S.find_set(3) << endl;
	
	
	Weighted_graph G3(6);
	
	G3.insert_edge(0,1,4);
	G3.insert_edge(1,2,1);
	G3.insert_edge(2,3,2);
	G3.insert_edge(3,4,3);
	G3.insert_edge(1,4,8);
	G3.insert_edge(4,5,2);
	
	pair<int, int> p = G3.minimum_spanning_tree();
	cout << "Min weight : " << p.first << endl;
	cout << "Edges test : " << p.second << endl;
	
	
	
	
}

