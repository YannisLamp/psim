#ifndef PRIORITYQUEUE
#define PRIORITYQUEUE

#include "process.h"
#include "dl_node.h"
#include "process_queue.h"

class PriorityQueue {
private:
	// First node of the queue
	ProcessQueue proc_queues[7];
	// The queue number where the current node is
	int from_queue;
public:
	PriorityQueue();
	~PriorityQueue();

	// Makes a new DlNode and insets it before
	// the current node, at the end of the queue
	void insert_process(Process*);
	void insert_node_norm(DlNode*);
	void insert_node_wprio(DlNode*, int);
	void update_data(int, int);

	DlNode* get_currnode();
	DlNode* extract_currnode();
	DlNode* extract_node_wprio(int, int);
	// Extracts process, deleting current node
	Process* extract_process();

	void find_next_node();
	bool is_empty();
	
	void print_data();
};

#endif
