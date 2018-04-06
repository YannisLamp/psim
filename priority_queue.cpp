#include <iostream>

#include "process.h"
#include "dl_node.h"
#include "process_queue.h"
#include "priority_queue.h"


using namespace std;

PriorityQueue::PriorityQueue() : from_queue(-1) {
    cout << "Creating Priority queue" << endl;
}

PriorityQueue::~PriorityQueue() {
    cout << "Deleting Priority queue" << endl;
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
    DlNode* output_ptr = proc_queues[proc_queue_dest].extract_node_wnum(pid);
    if (output_ptr
}

Process* PriorityQueue::extract_process() {
    DlNode* temp_ptr = proc_queues[from_queue].extract_currnode();
    Process* out_process = temp_ptr->get_process();
    delete temp_ptr;
    from_queue = -1;
    return out_process;
}

void PriorityQueue::find_next_node() {
    int i = 0, found = 0;
    DlNode* temp_node = nullptr;
    while (!found && i < 7) {
        proc_queues[i].find_next_node();
        temp_node = proc_queues[i].get_currnode();
        if (temp_node != nullptr) {
            from_queue = i;
            found = 1;
        }
        i++;
    }
    if (!found) {
        from_queue = -1;
    }
}
