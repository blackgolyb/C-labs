#ifndef TASK_MANAGER_H_INCLUDED
#define TASK_MANAGER_H_INCLUDED

struct Task
{
    void (*task_function)();
    int id;
    char *title;
};

struct TaskList
{
    struct Task *tasks;
    int count;
};

void register_task(struct TaskList *task_list, void (*task_function)(), int id, char *title);

void run_tusk(struct TaskList *task_list, int task_number);

void run_task_manager(struct TaskList *task_list);

#endif // TASK_MANAGER_H_INCLUDED
