/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * Inspiration for usage of vector of vectors...
 * http://www.cplusplus.com/forum/articles/7459/
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
#include "Disjoint_sets.h"


#include <vector>

using namespace std;


class Weighted_graph {
	private:
		static const double INF;
		double** graph; // stupid name, see weights variable below
		const int num_nodes;
		int num_edges;
		

		// Do not implement these functions!
		// By making these private and not implementing them, any attempt
		// to make copies or assignments will result in errors
		Weighted_graph( Weighted_graph const & );
		Weighted_graph &operator=( Weighted_graph );

		vector<vector<double> > weights;
		

	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		std::pair<double, int> minimum_spanning_tree() const;
	
		std::pair<int, int> get_min_edge(bool **);
	
		bool insert_edge( int, int, double );
		bool erase_edge( int, int );
		void clear_edges();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

/*
Weighted_graph ( int n = 50 ) - Constructs a weighted undirected graph with n vertices
(by default 50). Assume that initially there are no connections in the graph 
(edges will be inserted with the “insert” method).
Throw an illegal_argument exception if the argument is less than 0.
*/

Weighted_graph::Weighted_graph(const int n ): num_nodes(n){
	
	if (n < 0){
		throw illegal_argument();
	}
	
	//num_nodes = n;
	num_edges = 0;
	
	
	weights.resize(num_nodes);
  	for (int i = 0; i < num_nodes; ++i){
    	weights[i].resize(num_nodes);
    }
    
  
	for (int i = 0; i < num_nodes; i ++){
		for (int j = 0; j < num_nodes; j++){
			weights[i][j] = INF;
		}
	}
	
	
}

Weighted_graph::~Weighted_graph() {
	
	
}

/*
Returns the degree of the vertex n. Throw an illegal_argument
exception if the argument does not correspond to an existing vertex. 
*/

int Weighted_graph::degree(int u) const {
	
	if (u < 0 || u > (num_nodes - 1)){
		throw new illegal_argument();
	}
	
	int deg = 0;
	
	for (int i = 0; i < num_nodes; i ++){
		if (weights[u][i] != INF){
			deg++;	
		}
 	}
 
	return deg;

}

/*
Returns the number of edges in the graph
*/

int Weighted_graph::edge_count() const {
	
	return num_edges;
}

/*
If i equals j and are in the graph, return false. Otherwise,
either add a new edge from vertex i to vertex j or, if the edge already exists, update the weight and
return true. Recall that the graph is undirected. If i or j are outside the range of [0..n-1] or if the
weight w is less than or equal to zero, throw an illegal_argument exception.
*/

bool Weighted_graph::insert_edge( int i, int j, double d ) {
	
	if (i < 0 || j < 0 || i > (num_nodes -1) || j > (num_nodes -1) || d <= 0){
		throw illegal_argument();
	}
	
	if ( i == j ){
		return false;
	}
	
		
	weights[i][j] = d;
	weights[j][i] = d; // just to be safe, we're going to have to do both lol, for now
	
	num_edges++;
	return true;
}


/*
If an edge between nodes i and j exists, remove the edge. In this
case or if i equals j return true. Otherwise, if no edge exists, return false. If i or j are outside the
range of [0..n-1], throw an illegal_argument exception.
*/

bool Weighted_graph::erase_edge(int i, int j) {

	if (i < 0 || j < 0 || i > (num_nodes -1) || j > (num_nodes -1)){
		throw illegal_argument();
	}
	
	if ( i == j ){
		return false;
	}
	
	if (weights[i][j] == INF){
	 	return false;	
	}else{		
		weights[i][j] = INF;
		weights[j][i] = INF;	
		
		num_edges--;
		
		return true;
	}

}

/*
Removes all the edges from the graph.
*/

void Weighted_graph::clear_edges() {
	
	for (int i = 0; i < num_nodes; i ++){
		for (int j = 0; j < num_nodes; j++){
			weights[i][j] = INF;
		}
	}
	
	num_edges = 0;
	return;
}

// I need an adjacency matrix that represents the tree somewhere...
// this function is called from the MST()
// might need to pass the adjacency matrix in by reference lol
// im going to simulate a priority queue with a vector matrix lol
// tree is a copy of weights, at first

/*


*/
// passing in the array wasnt working for some reason, so i made it a member variable..

std::pair<int, int> Weighted_graph::get_min_edge(bool ** edgesInTree){
	
	int u = 0;
	int v = 0;
	double currentMinWeight = INF;
	for (int i = 0; i < num_nodes; i++){
		for (int j = 0; j < num_nodes; j++){ // the minus i is just for efficiency if need be
			if (!edgesInTree[i][j] && weights[i][j] < currentMinWeight){				
				u = i;
				v = j;
			}
		}
	
	}
	
	edgesInTree[u][v] = true;
	edgesInTree[v][u] = true;
	return std::pair<int, int>(u,v);
}

/*
Uses Kruskal’s algorithm to find the
minimum spanning tree. It returns the weight of the minimum spanning tree and the number of
edges that were tested for adding into the minimum spanning tree.

Assumptions: the graph is fully connected...
*/

std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {
	
	double total_weight = 0;
	int edges_tested = 0;
	
	// i have to sort the edges some how fuck...? or extract the edges lol, might need a heap
	Disjoint_set S(num_nodes); 
	
	
	bool **q = new bool[num_nodes][num_nodes];
	
	
	while (S.num_sets() != 1){ 
	
		int u = 0;
		int v = 0;
		std::pair<int, int>(u, v) = get_min_edge(q);
		
		if (S.find_set(u) != S.find_set(v)){
			S.union_sets(u,v);
			total_weight += weights[u][v];
			edges_tested++;
		}
	}
				
	return std::pair<double, int>( edges_tested, total_weight );
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	

	return out;
}


#endif
