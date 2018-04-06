#include <iostream>
#include <string>
#include <ctime>
#include <math.h>

#include "exp_rand.h"
#include "process.h"
#include "dl_node.h"
#include "process_queue.h"
#include "priority_queue.h"
#include "sem_queue.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Checking parameter number
    if (argc < 7) {
        // Show wanted parameters for program execution
        cerr << "Usage: " << argv[0]
        << endl << "Average number of successive process arrivals,"
        << endl << "Average process lifespan,"
        << endl << "Average duration of critical section usage,"
        << endl << "Maximum simulator process number,"
        << endl << "Probability of entering a critical section per time slot (k),"
        << endl << "Semaphore number (S)" << endl;
        return 1;
    }
    // Seed rand with time of execution
    srand(time(NULL));

    // Program arguments (stoi and stod are used)
    const double succ_arr_avg = stod(argv[1]);
    const double proc_life_avg = stod(argv[2]);
    const double crit_usg_avg = stod(argv[3]);

    const int max_procnum = stoi(argv[4]);
    const double crit_chance = stod(argv[5]);
    const int sem_num = stoi(argv[6]);

    // succ_arr_avg, proc_life_avg, crit_usg_avg should be above zero (exp_rand outputs
    // positive numbers) and sem_num should be above zero
    if (succ_arr_avg == 0.0 || proc_life_avg == 0.0 || crit_usg_avg == 0.0 || sem_num == 0) {
        cerr << "Averages and the semaphore number should all be above zero" << endl;
        return 1;
    }

	cout << "Project 3 Operating Systems" << endl << endl;
	cout << "Starting simulation" << endl;
    // Create program Objects
    PriorityQueue priority_queue;
    SemQueue* sem_queues = new SemQueue[sem_num];

    int curr_timeslot = 0;
    // There should be a process with pid 0
    int curr_procnum = -1;
    int next_proc_arrival = 0;
    // Main simulation loop
    do {
        // Create new process and insert it into the priority queue
        if (next_proc_arrival == 0 && curr_procnum < max_procnum - 1) {
            curr_procnum++;
            int proc_life = exp_rand(proc_life_avg);
            // Process life should not be zero
            while (proc_life == 0) {
                proc_life = exp_rand(proc_life_avg);
            }
            Process* proc = new Process(curr_procnum, proc_life, curr_timeslot);
            priority_queue.insert_process(proc);
            next_proc_arrival = round(exp_rand(succ_arr_avg));
            // Minimum next time for a process arrival is the next timeslot
            while (next_proc_arrival == 0) {
                next_proc_arrival = exp_rand(succ_arr_avg);
            }
        }
        bool executed = false;
        // If there is a process in the priority queue
        if (!priority_queue.is_empty()) {
            priority_queue.find_next_node();
            int using_semnum = priority_queue.get_currnode()->get_process()->get_using_semnum();
            // If the process is not using a critical section
            if (using_semnum == -1) {
                // There is a chance that it wants to, so
                // Generate a random double between 0 and 100
                double rand_perc = 100 * ( (double)rand() / (double)RAND_MAX );
                // If it wants to,
                if (crit_chance >= rand_perc) {
                    int chosen_semnum = rand() % sem_num;
                    priority_queue.get_currnode()->get_process()->set_using_semnum(chosen_semnum);
                    int crit_usg = exp_rand(crit_usg_avg);
                    // crit_usg should be lower than the remaining life of the process
                    while (crit_usg == 0 || crit_usg > priority_queue.get_currnode()->get_process()->get_rem_life()) {
                        crit_usg = exp_rand(crit_usg_avg);
                    }
                    priority_queue.get_currnode()->get_process()->set_rem_crit_usg(crit_usg);
                    // Let semaphore ups and downs take 0 timeslots
                    int down_success = sem_queues[chosen_semnum].down(&priority_queue, curr_timeslot);
                    if (down_success) {
                        priority_queue.get_currnode()->get_process()->execute(curr_timeslot);
                        executed = true;
                        // Check if it wants to up
                		if (priority_queue.get_currnode()->get_process()->get_rem_crit_usg() == 0) {
                    		int using_semnum = priority_queue.get_currnode()->get_process()->get_using_semnum();
                    		priority_queue.get_currnode()->get_process()->set_using_semnum(-1);
                    		priority_queue.get_currnode()->get_process()->set_rem_crit_usg(-1);
							sem_queues[using_semnum].up(&priority_queue, curr_timeslot);
                		}
                		else{
                			// Check only if its remaining life is zero
                			if (priority_queue.get_currnode()->get_process()->get_rem_life() == 0) {
                				Process* del_proc = priority_queue.extract_process();
           	    				priority_queue.update_data(del_proc->get_priority(), del_proc->get_tot_waited());
                				delete del_proc;
							}
						}
                    }
                }
                // Else execute normally
                else {
                    priority_queue.get_currnode()->get_process()->execute(curr_timeslot);
                    executed = true;
                    // Check if its remaining life is zero
                    if (priority_queue.get_currnode()->get_process()->get_rem_life() == 0) {
                    	Process* del_proc = priority_queue.extract_process();
           	        	priority_queue.update_data(del_proc->get_priority(), del_proc->get_tot_waited());
                    	delete del_proc;
					}
                }
            }
            // If a process has downed a semaphore and is in the priority queue,
            // then it has access to a critical section
            else {
            	priority_queue.get_currnode()->get_process()->execute(curr_timeslot);
            	executed = true;
                // Check if it wants to up
                if (priority_queue.get_currnode()->get_process()->get_rem_crit_usg() == 0) {
                    int using_semnum = priority_queue.get_currnode()->get_process()->get_using_semnum();
                    priority_queue.get_currnode()->get_process()->set_using_semnum(-1);
                    priority_queue.get_currnode()->get_process()->set_rem_crit_usg(-1);
					sem_queues[using_semnum].up(&priority_queue, curr_timeslot);
                }
                else {
                // Check if its remaining life is zero
                	if (priority_queue.get_currnode()->get_process()->get_rem_life() == 0) {
                		Process* del_proc = priority_queue.extract_process();
           	    		priority_queue.update_data(del_proc->get_priority(), del_proc->get_tot_waited());
                		delete del_proc;
					}
				}
            }
        }
        // If there are no processes assume that time just passes, so executed == true
        else
        	executed = true;

		// Update data stored in the semaphore queues about processes being blocked
		// by processes with lower priority
		for (int i = 0; i < sem_num; i++)
			sem_queues[i].update_data();

		// If a process was executed (the timeslot has passed)
        if (executed) {
            next_proc_arrival -= 1;
            curr_timeslot++;
        }
    // There is a process with pid 0 so < (process count == max_procnum - 1)
    } while (curr_procnum < max_procnum - 1 || (!priority_queue.is_empty()));

	cout << "Ending simulation" << endl << endl;
	priority_queue.print_data();
	int total_pinversion = 0;
	cout << endl << "Priority inversion time data (blocked by lower priority processes)" << endl << endl;
	for (int i = 0; i < sem_num; i++) {
		cout << "In semaphore " << i << ": " << sem_queues[i].get_blocked_by_lower() << endl;
		total_pinversion += sem_queues[i].get_blocked_by_lower();
	}
	cout << "Total priority inversion time: " <<  total_pinversion << endl;


	// Delete semaphores (mutexes)
	delete[] sem_queues;

    return 0;
}
