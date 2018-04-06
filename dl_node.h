#ifndef DLNODE
#define DLNODE

#include "process.h"

class DlNode {
private:
	Process* process_ptr;
	DlNode* nextnode_ptr;
    DlNode* prevnode_ptr;
public:
	DlNode(Process*);
	~DlNode();

	void set_nextnode(DlNode*);
    void set_prevnode(DlNode*);

	Process* get_process();
	DlNode* get_nextnode();
    DlNode* get_prevnode();
};

#endif
