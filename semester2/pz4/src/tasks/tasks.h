#ifndef TASKS_H_INCLUDED
#define TASKS_H_INCLUDED

void task1();

void (*tasks[])() = {
    task1,
};

#endif