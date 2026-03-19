#ifndef KANBAN_STRUCTS_H
#define KANBAN_STRUCTS_H



enum Status {
    TODO,
    IN_PROGRESS,
    DONE
};

enum Priority {
    LOW,
    MEDIUM,
    HIGH
};


typedef struct Task {
    int id;
    char *title;
    char *description;
    enum Priority priority;
    enum Status status;
    struct Task *next;
} Task;

typedef struct Kanban {
    Task *tasks;
} Kanban;


#endif