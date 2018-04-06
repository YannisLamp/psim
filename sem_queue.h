#ifndef SEMQUEUE
#define SEMQUEUE

#include "dl_node.h"
#include "process.h"

// MONO PAIRNEI NODES, DEN DIMIOURGEI OUTE
// KATASTREFEI
class SemQueue {
private:
	// First node of the queue
	DlNode* firstnode_ptr;
	// Last node of the queue
	DlNode* lastnode_ptr;
	// Node not in the queue, containing the process
	// that is currently using the critical section
	DlNode* using_crit_ptr;

	// For safety
	void del_all_nodes(DlNode*);
	// Used by up() and down()
	// Only control the normal queue they do not
	// change the value of using_crit_ptr
	//void push(DlNode*);
	//DlNode* pop();
public:
	SemQueue();
	~SemQueue();

	void push(DlNode*);
	DlNode* pop();

	void up();
	void down();
};

#endif
