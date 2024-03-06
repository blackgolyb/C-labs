#ifndef TASKS_H_INCLUDED
#define TASKS_H_INCLUDED

void task1();
void task2_1();
void task2_2();

void (*tasks[])() = {
    task1,
    task2_1,
    task2_2,
};

#endif