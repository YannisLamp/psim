#include <iostream>

#include "process.h"
#include "dl_node.h"
#include "sem_queue.h"

using namespace std;

SemQueue::SemQueue() : firstnode_ptr(nullptr), lastnode_ptr(nullptr),
 					   using_crit_ptr(nullptr) {
}

SemQueue::~SemQueue() {
    cout << "Deleting Semaphore queue" << endl;
	if (firstnode_ptr != nullptr) {
		cerr << "Processes left in semaphore queue" << endl;
		del_all_nodes(firstnode_ptr);
	}
}

// Private recursive function for the SemQueue destructor
void SemQueue::del_all_nodes(DlNode* node_ptr) {
	DlNode* next_node_ptr = node_ptr->get_nextnode();
	if (next_node_ptr != nullptr)
		del_all_nodes(next_node_ptr);
	delete node_ptr;
}

void SemQueue::push(DlNode* inputnode_ptr) {
	// Inputnode does not point to a next node
	// If queue is empty
	if (firstnode_ptr == nullptr) {
		firstnode_ptr = inputnode_ptr;
		lastnode_ptr = inputnode_ptr;
	}
	// Else normally
	else {
		lastnode_ptr->set_nextnode(inputnode_ptr);
		lastnode_ptr = inputnode_ptr;
	}
}

DlNode* SemQueue::pop() {
	// If queue is empty
	if (firstnode_ptr == nullptr) {
		cerr << "Semaphore queue empty, cannot pop" << endl;
		return nullptr;
	}
	// Else normally
	else {
		DlNode* output_ptr = firstnode_ptr;
		firstnode_ptr = output_ptr->get_nextnode();
		// Output node* should not point anywhere
		output_ptr->set_nextnode(nullptr);
		return output_ptr;
	}
}
