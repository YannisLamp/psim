#ifndef PROCESS
#define PROCESS

class Process {
private:
    int pid;
    int priority;
    int using_crit;
    int life
public:
    Process(int);
    ~Process();

    int get_pid();
    int get_priority();
    int get_using_crit();

    void set_using_crit(int);
};


#endif
