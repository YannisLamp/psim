#include <iostream>

#include "process.h"
#include "dl_node.h"

using namespace std;

DlNode::DlNode(Process* input_ptr) : process_ptr(input_ptr), nextnode_ptr(nullptr), 
									 prevnode_ptr(nullptr) {
	//cout << "Creating DlNode" << endl;
};

DlNode::~DlNode() {
	//cout << "Deleting DlNode" << endl;
};

void DlNode::set_nextnode(DlNode* input_ptr) {
	nextnode_ptr = input_ptr;
}

void DlNode::set_prevnode(DlNode* input_ptr) {
	prevnode_ptr = input_ptr;
}

Process* DlNode::get_process() {
	return process_ptr;
}

DlNode* DlNode::get_nextnode() {
	return nextnode_ptr;
}

DlNode* DlNode::get_prevnode() {
	return prevnode_ptr;
}
