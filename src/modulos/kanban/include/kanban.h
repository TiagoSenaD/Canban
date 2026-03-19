#ifndef KANBAN_FUNCTIONS_H
#define KANBAN_FUNCTIONS_H

#include "kanban_structs.h"

Task *locate_task(Kanban *kanban, int id, Task **prev);
void append_task(Kanban *kanban, Task *new_node);
void free_kanban(Kanban *kanban);

void create_task(Kanban *kanban, char *title, char *description, int priority, int id);
void delete_task(Kanban *kanban, int id);
void update_task(Kanban *kanban, int id, char *title, char *description, int priority, int status);
void list_tasks(Kanban *kanban);
void save_tasks(Kanban *kanban, char *filename);
void load_tasks(Kanban *kanban, char *filename);

#endif