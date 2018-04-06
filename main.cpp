#include <iostream>
#include <string>
//#include <fstream>
//#include <cstdlib>
#include <ctime>
#include "exp_rand.h"
#include "process.h"
#include "dl_node.h"
#include "process_queue.h"
#include "priority_queue.h"
#include "sem_queue.h"

using namespace std;

int main(int argc, char* argv[]) {
    // Checking parameter number
    if (argc < 6) {
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
    // Program arguments
    double succ_arr_avg = stod(argv[1]);
    double proc_life_avg = stod(argv[2]);
    double crit_usg_avg = stod(argv[3]);

    const int max_proc_num = stoi(argv[4]);
    const double crit_chance = stod(argv[5]);
    const int sem_num = stoi(argv[6]);

    // Create program Objects


    int created_proc = 0;
    do {
        if ()








    } while (created_proc_num <= max_proc_num || );
    /*Process p1(1);
    Process p2(2);
    Process p3(3);
    Process p4(4);
    Process p5(5);
    Process p6(6);
    Process p7(7);
    Process p8(8);
    Process p9(9);
    Process p10(10);
    Process p11(11);
    Process p12(12);

    DlNode n1(&p1);
    DlNode n2(&p2);
    DlNode n3(&p3);
    DlNode n4(&p4);

    SemQueue sq;
    sq.push(&n1);
    sq.push(&n2);
    cout << sq.pop()->get_process()->get_pid() << endl;
    cout << sq.pop()->get_process()->get_pid() << endl;
    sq.push(&n3);
    cout << sq.pop()->get_process()->get_pid() << endl;
    sq.push(&n1);
    cout << sq.pop()->get_process()->get_pid() << endl;
    cout << sq.pop()->get_process()->get_pid() << endl;
*/
    /*PriorityQueue pq;
    pq.insert_process(&p1);
    pq.insert_process(&p2);
    pq.insert_process(&p3);
    pq.insert_process(&p4);
    pq.insert_process(&p5);
    pq.insert_process(&p6);
    pq.insert_process(&p7);
    pq.insert_process(&p8);
    pq.insert_process(&p9);
    pq.insert_process(&p10);
    pq.insert_process(&p11);
    pq.insert_process(&p12);

    pq.find_next_node();

    for(int i=0;i<10;i++) {
        cout << pq.get_currnode()->get_process()->get_pid() << endl;
        pq.find_next_node();
    }

    for(int i=0;i<12;i++) {
        cout << pq.extract_process()->get_pid() << endl;
        pq.find_next_node();
    }*/

    //for()


}
