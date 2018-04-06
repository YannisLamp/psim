#ifndef PROCESS
#define PROCESS

class Process {
private:
    int pid;
    int priority;
    int rem_life;
    // If using_semnum is -1, then it is not using a critical section
    int using_semnum;
    int rem_crit_usg;
    int tot_waited;
    int waiting_since;
public:
    Process(int, int, int);
    ~Process();

    int get_pid();
    int get_priority();
    int get_rem_life();
    int get_using_semnum();
    int get_rem_crit_usg();
    int get_tot_waited();

    void set_using_semnum(int);
    void set_rem_crit_usg(int);
    void set_waiting_since(int);
    void calc_total_waited(int);
    void execute(int);
};

#endif
