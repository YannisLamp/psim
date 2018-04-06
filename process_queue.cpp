#include <iostream>

#include "process.h"
#include "dl_node.h"
#include "process_queue.h"

using namespace std;

ProcessQueue::ProcessQueue() : firstnode_ptr(nullptr), currnode_ptr(nullptr),
							   afternode_ptr(nullptr) {
	cout << "Creating Process Queue" << endl;
}

ProcessQueue::~ProcessQueue() {
    cout << "Deleting Process Queue" << endl;
	if (firstnode_ptr != nullptr)
		del_all_nodes(firstnode_ptr);
}

// Private recursive function for the ProcessQueue destructor
void ProcessQueue::del_all_nodes(DlNode* node_ptr) {
	DlNode* next_node_ptr = node_ptr->get_nextnode();
	if (next_node_ptr != nullptr)
		del_all_nodes(next_node_ptr);
	delete node_ptr;
}

void ProcessQueue::insert_node(DlNode* inputnode_ptr) {
	// If queue is empty
	if (firstnode_ptr == nullptr) {
		firstnode_ptr = inputnode_ptr;
		afternode_ptr = inputnode_ptr;
	}
	// Else normally put input node at the end of the queue (before currentnode)
	else {
		if (currnode_ptr != nullptr) {
			DlNode* old_last_ptr = currnode_ptr->get_prevnode();
			inputnode_ptr->set_nextnode(currnode_ptr);
			// If old_last_ptr is nullptr it doesnt matter
			inputnode_ptr->set_prevnode(old_last_ptr);
			currnode_ptr->set_prevnode(inputnode_ptr);
			// If the previous node is the first one
			if (old_last_ptr == nullptr)
        		firstnode_ptr = inputnode_ptr;
			else
				old_last_ptr->set_nextnode(inputnode_ptr);
		}
		// If currnode_ptr is nullptr then make the same changes to afternode_ptr
		else {
			DlNode* old_last_ptr = afternode_ptr->get_prevnode();
			inputnode_ptr->set_nextnode(afternode_ptr);
			// If old_last_ptr is nullptr it doesnt matter
			inputnode_ptr->set_prevnode(old_last_ptr);
			afternode_ptr->set_prevnode(inputnode_ptr);
			// If the previous node is the first one
			if (old_last_ptr == nullptr)
				firstnode_ptr = inputnode_ptr;
			else
				old_last_ptr->set_nextnode(inputnode_ptr);
		}
	}
}

DlNode* ProcessQueue::get_currnode() {
    return currnode_ptr;
}

// When a node is extracted, then currnode_ptr becomes nullptr
DlNode* ProcessQueue::extract_currnode() {
	// If queue is empty
	if (currnode_ptr == nullptr) {
		cerr << "No current node in process queue, cannot extract" << endl;
		return nullptr;
	}
	// Else normally
	else {
		DlNode* tempnext_ptr = currnode_ptr->get_nextnode();
		DlNode* tempprev_ptr = currnode_ptr->get_prevnode();

		// Fix next and previous pointers
		if(tempnext_ptr != nullptr)
			tempnext_ptr->set_prevnode(tempprev_ptr);
		if(tempprev_ptr != nullptr)
			tempprev_ptr->set_nextnode(tempnext_ptr);
		else
			firstnode_ptr = tempnext_ptr;
		// If its the only node
		if(tempnext_ptr == nullptr && tempprev_ptr == nullptr) {
			firstnode_ptr = nullptr;
			afternode_ptr = nullptr;
		}

		// Temp node for output
		DlNode* output_ptr = currnode_ptr;
		currnode_ptr = nullptr;
		// Output node* should not point anywhere
		output_ptr->set_nextnode(nullptr);
        output_ptr->set_prevnode(nullptr);
		return output_ptr;
	}
}

DlNode* ProcessQueue::extract_node_wnum(int pid) {
	// If queue is empty
	if (firstnode_ptr == nullptr) {
		cerr << "No node in process queue, cannot extract" << endl;
		return nullptr;
	}
	// Else normally
	else {
		DlNode* search_ptr = firstnode_ptr;
		while (search_ptr != nullptr) {
			if (search_ptr->get_process()->get_pid() == pid
		}

		if (search_ptr == nullptr) {
			cerr << "No node in process queue with input pid, cannot extract" << endl;
			return nullptr;
		}




		DlNode* tempnext_ptr = currnode_ptr->get_nextnode();
		DlNode* tempprev_ptr = currnode_ptr->get_prevnode();

		// Fix next and previous pointers
		if (tempnext_ptr != nullptr)
			tempnext_ptr->set_prevnode(tempprev_ptr);
		if (tempprev_ptr != nullptr)
			tempprev_ptr->set_nextnode(tempnext_ptr);
		else
			firstnode_ptr = tempnext_ptr;
		// If its the only node
		if (tempnext_ptr == nullptr && tempprev_ptr == nullptr) {
			firstnode_ptr = nullptr;
			afternode_ptr = nullptr;
		}

		// Temp node for output
		DlNode* output_ptr = currnode_ptr;
		currnode_ptr = nullptr;
		// Output node* should not point anywhere
		output_ptr->set_nextnode(nullptr);
        output_ptr->set_prevnode(nullptr);
		return output_ptr;
	}
}

void ProcessQueue::find_next_node() {
	currnode_ptr = afternode_ptr;
	if (currnode_ptr != nullptr) {
    	DlNode* temp_ptr = currnode_ptr->get_nextnode();
    	if (temp_ptr != nullptr)
        	afternode_ptr = temp_ptr;
    	else
			afternode_ptr = firstnode_ptr;
	}
}
