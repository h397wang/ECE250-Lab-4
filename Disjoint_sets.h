
#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#ifndef nullptr
#define nullptr 0
#endif


#include <limits>
#include "Exception.h"

using namespace std;

struct ll_entry; // represents each element of the linked list
struct set_info; // keeps track of the information (pointers to head and tail and the size of the set) of each set
//could we delete the above two lines?


struct ll_entry{ 
	int content; // refers to the node enumeration
	set_info* ptr_to_info; // ptr to the info entry of the corresponding set
	ll_entry* next;
	
};

struct set_info { 
	ll_entry* head;
	ll_entry* tail;
	int size;
};

class Disjoint_set {

private:
	
	// An array of pointers that keeps a pointer to each node entry in the linked lists
	ll_entry** nodes;
	
	/*
	An array of pointers that keeps the information for each sets. This information
	includes the pointers to head and tail of the set as well as an integer that keeps the size of the set.
	*/
	set_info** sets; 
	
	// A variable that saves the current number of sets.
	int set_counter; 
	
	// A variable that saves the initial number of sets.
	int initial_num_sets;
	
public:
	Disjoint_set(int);
	~Disjoint_set();
	int find_set(int) const;
	int num_sets() const;
	void union_sets(int, int);
};


/*
Constructs a disjoint sets data structures with n sets each containing one element
(therefore the total number of elements in n).
*/

Disjoint_set::Disjoint_set(int n) : nodes(new ll_entry*[n]), 
	sets (new set_info*[n]), set_counter(n), initial_num_sets(n) {
	// initialize the sets	
	
	for (int i = 0; i < n; i++){
		nodes[i] = new ll_entry();
		nodes[i]->content = i;
		nodes[i]->next = nullptr;

		sets[i] = new set_info();
		sets[i]->size = 1;
		
		// instantiate the set_info first
		nodes[i]->ptr_to_info = sets[i];
		
		sets[i]->head = nodes[i];
		sets[i]->tail = nodes[i];
	}
	
	
}

Disjoint_set::~Disjoint_set() {
	
	for (int i = 0; i < initial_num_sets; i++){
		delete nodes[i];
		delete sets[i];	
	}
	
	delete [] nodes;
	delete [] sets;
	
}

/*
Returns the representative of the set that the input belongs to
*/

int Disjoint_set::find_set(int item) const{

	return nodes[item]->ptr_to_info->head->content;
}

int Disjoint_set::num_sets() const {
	return set_counter;
}

/*
Unites the dynamic sets that contain
node_index1 and node_index2
*/

void Disjoint_set::union_sets(int node_index1, int node_index2) {
	
	if (node_index1 < 0 || node_index1 > (initial_num_sets -1) 
		|| node_index2 < 0 || node_index2 > (initial_num_sets -1)){
			throw illegal_argument(); // not specified, pray it doesnt happen
	}
		
	if (node_index1 == node_index2){
		return;
	}
	
	set_info* si1 = nodes[node_index1]->ptr_to_info;
	set_info* si2 = nodes[node_index2]->ptr_to_info;

	// check if they're in the same set
	if (si1->head->content == si2->head->content){
		return;	
	}


	// ni1: the index of the larger set, ni2: the index of the smaller index
	int ni1 = si1->size >= si2->size ? node_index1 : node_index2; 
	int ni2 = si1->size < si2->size ? node_index1 : node_index2;


	// iterate through the shorter list and modify the pointers
	set_info * larger = nodes[ni1]->ptr_to_info;
	set_info * smaller = nodes[ni2]->ptr_to_info;
	ll_entry * currentNode = smaller->head;

 	do{ 
		// only thing to modify is the ptr_to_info...
		currentNode->ptr_to_info = larger;
		currentNode = currentNode->next;
	} while (currentNode == smaller->tail);
	
	larger->tail->next = smaller->head; // link the two lists
	larger->tail = smaller->tail; // set tail as required
	larger->size = larger->size + smaller->size; // update size 
	
	set_counter --; 
	// delete the set_info entry that no longer exists
	delete smaller;
	
	
}


#endif
