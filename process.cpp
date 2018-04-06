#include <iostream>

#include "process.h"

using namespace std;

Process::Process(int p_num, int life, int curr_timeslot)
                : pid(p_num), rem_life(life), using_semnum(-1),
                  rem_crit_usg(0), tot_waited(0), waiting_since(curr_timeslot) {
    priority = (rand() % 7) + 1;
    //cout << "Process Number: " << pid << " was created";
	//cout << " with priority " << priority << endl;
}

Process::~Process() {
    //cout << "Deleting Process " << pid << endl;
}

int Process::get_pid() {
    return pid;
}

int Process::get_priority() {
    return priority;
}

int Process::get_using_semnum() {
    return using_semnum;
}

int Process::get_rem_life() {
    return rem_life;
}

int Process::get_rem_crit_usg() {
    return rem_crit_usg;
}

int Process::get_tot_waited() {
	return tot_waited;
}

void Process::set_using_semnum(int input_semnum) {
    using_semnum = input_semnum;
}


void Process::set_rem_crit_usg(int crit_usg) {
    rem_crit_usg = crit_usg;
}

void Process::set_waiting_since(int curr_timeslot) {
    waiting_since = curr_timeslot;
}

void Process::calc_total_waited(int curr_timeslot) {
    tot_waited += curr_timeslot - waiting_since;
}

void Process::execute(int curr_timeslot) {
    // If the process is not using a critical section decrement remaining life
    if (using_semnum == -1)
        rem_life -= 1;
    // Else also decrement remaining critical section usage
    else {
        rem_life -= 1;
        rem_crit_usg -= 1;
    }
    // Update total waited timeslots for this process
    calc_total_waited(curr_timeslot);
    // It will start waiting from the next timeslot
    waiting_since = curr_timeslot + 1;
}
