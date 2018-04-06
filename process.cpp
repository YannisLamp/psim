#include <iostream>
#include "process.h"

using namespace std;

Process::Process(int p_num) : pid(p_num), using_crit(-1) {
    priority = (rand() % 7) + 1;
    cout << "Process Number: " << pid << " was created";
	cout << " with priority " << priority << endl;
}

Process::~Process() {
    cout << "Deleting Process " << pid << endl;
}

int Process::get_pid() {
    return pid;
}

int Process::get_priority() {
    return priority;
}

int Process::get_using_crit() {
    return using_crit;
}

void Process::set_using_crit(int input_crit) {
    using_crit = input_crit;
}
