#ifndef PROCESSQUEUE
#define PROCESSQUEUE

#include "process.h"
#include "dl_node.h"

class ProcessQueue {
private:
	// First node of the queue
	DlNode* firstnode_ptr;
	// Current node of the queue (Process to use current time slot)
	DlNode* currnode_ptr;
	// Node after the current node in the queue
	DlNode* afternode_ptr;

	// Simulation Data
	int total_proc;
	int timeslots_waited;

	void del_all_nodes(DlNode*);
public:
	ProcessQueue();
	~ProcessQueue();

	// Inserts the input Node before
	// the current node, at the end of the queue
	void insert_node(DlNode*);

	DlNode* get_currnode();
	DlNode* get_firstnode();
	DlNode* extract_currnode();
	DlNode* extract_node_wpid(int);

	void update_data(int);
	int get_total_proc();
	int get_timeslots_waited();
	void find_next_node();
};

#endif
