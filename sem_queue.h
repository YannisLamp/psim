#ifndef SEMQUEUE
#define SEMQUEUE

#include "dl_node.h"
#include "process.h"
#include "priority_queue.h"

// Only gets nodes (DlNodes that it uses as normal nodes)
// that were constructed in the priority queue
// (No DlNodes are constructed or destructed here)
class SemQueue {
private:
	// First node of the queue
	DlNode* firstnode_ptr;
	// Last node of the queue
	DlNode* lastnode_ptr;
	// Node not in the queue, containing the process
	// that is currently using the critical section
	int using_crit_pid;
	int normal_prio;
	int highest_prio;

	int blocked_by_lower;
	// For safety
	void del_all_nodes(DlNode*);
	// Used by up() and down()
	// Only control the normal queue they do not
	// change the value of using_crit_ptr
	void push(DlNode*);
	DlNode* pop();
public:
	SemQueue();
	~SemQueue();

	int get_blocked_by_lower();
	void update_data();
	
	int down(PriorityQueue*, int);
	int up(PriorityQueue*, int);
};

#endif
