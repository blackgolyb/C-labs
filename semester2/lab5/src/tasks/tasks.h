#ifndef TASKS_H_INCLUDED
#define TASKS_H_INCLUDED

void task1();
void task2();
void task3();
void task4();
void task5();

void (*tasks[])() = {
    task1,
    task2,
    task3,
    task4,
    task5,
};

#endif