#include <iostream>

#include "process.h"
#include "dl_node.h"
#include "sem_queue.h"
#include "priority_queue.h"

using namespace std;

SemQueue::SemQueue() : firstnode_ptr(nullptr), lastnode_ptr(nullptr),
 					   using_crit_pid(-1), highest_prio(-1),
					   normal_prio(-1), blocked_by_lower(0) {
	//cout << "Creating Semaphore queue" << endl;
}

SemQueue::~SemQueue() {
    //cout << "Deleting Semaphore queue" << endl;
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

int SemQueue::get_blocked_by_lower() {
	return blocked_by_lower;
}

void SemQueue::update_data() {
	if (using_crit_pid != -1) {
		DlNode* search_node = firstnode_ptr;
		while (search_node != nullptr) {
			if (search_node->get_process()->get_priority() > normal_prio)
				blocked_by_lower++;
			DlNode* temp = search_node;
			search_node = temp->get_nextnode();
		}
	}		
}

// The process that will want to down the semaphore will always be
// the input priority queue's current process
// Return 1 if no other process was acessing the critical section,
// otherwise return 0 and remove current process from the priority queue
int SemQueue::down(PriorityQueue* priority_queue, int curr_timeslot) {
    DlNode* curr_down = priority_queue->get_currnode();
    int curr_prio = curr_down->get_process()->get_priority();
    // Ff no other process is acessing the critical section
    if (using_crit_pid == -1) {
        using_crit_pid = curr_down->get_process()->get_pid();
        normal_prio = curr_prio;
        highest_prio = curr_prio;
        return 1;
    }
    else {
        curr_down = priority_queue->extract_currnode();
        curr_down->get_process()->calc_total_waited(curr_timeslot);
        push(curr_down);
        // If its priority is higher than the previous highest
        if (curr_prio > highest_prio) {
            // Change priority
            DlNode* temp_using = priority_queue->extract_node_wprio(using_crit_pid, highest_prio);
            priority_queue->insert_node_wprio(temp_using, curr_prio);
            highest_prio = curr_prio;
        }
        return 0;
    }
}

// Normally return 1, return 0 in case current process in the priority queue
// is not the one that currently has access to the critical section
int SemQueue::up(PriorityQueue* priority_queue, int curr_timeslot) {
    Process* upped_proc = priority_queue->get_currnode()->get_process();
    int upped_pid = upped_proc->get_pid();
    // If no other process is acessing the critical section
    if (using_crit_pid == -1 || using_crit_pid != upped_pid)
        return 0;
    else {
    	// Only if process needs to die after the up 
		if (upped_proc->get_rem_life() == 0) {
            Process* del_proc = priority_queue->extract_process();
           	priority_queue->update_data(del_proc->get_priority(), del_proc->get_tot_waited());
            delete del_proc;
            upped_proc = nullptr;
		}
        else if (normal_prio != highest_prio) {
			// Return it to its normal priority
			DlNode* temp_using = priority_queue->extract_currnode();
            priority_queue->insert_node_norm(temp_using);
		}
		// Else no need to move process
		else {
			// Find new highest priority
			int new_highest = -1;
			DlNode* search_node = firstnode_ptr;
			while (search_node != nullptr) {
				int curr_prio = search_node->get_process()->get_priority();
				if (new_highest < curr_prio)
					new_highest = curr_prio;
				DlNode* temp = search_node;
				search_node = temp->get_nextnode();
			}
			highest_prio = new_highest;
		}
		// Take care of the next process accessing the critical section
		if (firstnode_ptr != nullptr) {
			DlNode* curr_using = pop();
			using_crit_pid = curr_using->get_process()->get_pid();
			normal_prio = curr_using->get_process()->get_priority();
			curr_using->get_process()->set_waiting_since(curr_timeslot);
			priority_queue->insert_node_wprio(curr_using, highest_prio);
		}
		else
			using_crit_pid = -1;
			
		return 1;
    }


}
