#include <iostream>

#include "process.h"
#include "dl_node.h"
#include "process_queue.h"
#include "priority_queue.h"


using namespace std;

PriorityQueue::PriorityQueue() : from_queue(-1) {
    //cout << "Creating Priority queue" << endl;
}

PriorityQueue::~PriorityQueue() {
    //cout << "Deleting Priority queue" << endl;
}

void PriorityQueue::insert_process(Process* inputproc_ptr) {
    DlNode* inputnode_ptr = new DlNode(inputproc_ptr);
    int proc_queue_dest = inputproc_ptr->get_priority() - 1;
    proc_queues[proc_queue_dest].insert_node(inputnode_ptr);
}

void PriorityQueue::insert_node_norm(DlNode* inputnode_ptr) {
	int proc_queue_dest = inputnode_ptr->get_process()->get_priority() - 1;
    proc_queues[proc_queue_dest].insert_node(inputnode_ptr);
}

void PriorityQueue::insert_node_wprio(DlNode* inputnode_ptr, int priority) {
	int proc_queue_dest = priority - 1;
    proc_queues[proc_queue_dest].insert_node(inputnode_ptr);
}

void PriorityQueue::update_data(int priority, int waited) {
	proc_queues[priority - 1].update_data(waited);
}

DlNode* PriorityQueue::get_currnode() {
    if (from_queue != -1)
        return proc_queues[from_queue].get_currnode();
    else
        return nullptr;
}

DlNode* PriorityQueue::extract_currnode() {
    if (from_queue != -1) {
        DlNode* temp_node = proc_queues[from_queue].extract_currnode();
        from_queue = -1;
        return temp_node;
    }
    else
        return nullptr;
}

DlNode* PriorityQueue::extract_node_wprio(int pid, int priority) {
    int proc_queue_dest = priority - 1;
    return proc_queues[proc_queue_dest].extract_node_wpid(pid);
}

Process* PriorityQueue::extract_process() {
    DlNode* temp_ptr = proc_queues[from_queue].extract_currnode();
    Process* out_process = temp_ptr->get_process();
    delete temp_ptr;
    from_queue = -1;
    return out_process;
}

void PriorityQueue::find_next_node() {
    int i = 0;
    bool found = false;
    while (!found && i < 7) {
        proc_queues[i].find_next_node();
        if (proc_queues[i].get_currnode() != nullptr) {
            from_queue = i;
            found = true;
        }
        i++;
    }
    if (!found) {
        from_queue = -1;
    }
}

bool PriorityQueue::is_empty() {
    for (int i = 0; i < 7; i++) {
        if (proc_queues[i].get_firstnode() != nullptr)
            return false;
    }
    return true;
}

// Print statistics
void PriorityQueue::print_data() {
	for (int i = 0; i < 7; i++) {
		cout << "Average waiting time for processes with priority " << i + 1 << ": ";
		cout << (float)proc_queues[i].get_timeslots_waited() / (float)proc_queues[i].get_total_proc() << endl;
	}
}
