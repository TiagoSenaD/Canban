#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/kanban.h"
#include "include/kanban_structs.h"

void append_task(Kanban *kanban, Task *new_node) {
    if (kanban->tasks == NULL) {
        kanban->tasks = new_node;
    } else {
        Task *last = kanban->tasks;
        while (last->next != NULL) last = last->next;
        last->next = new_node;
    }
}

Task *locate_task(Kanban *kanban, int id, Task **last_node) {
    Task *current = kanban->tasks;
    Task *prev = NULL;

    while (current != NULL) {
        if (current->id == id) {
            if (last_node != NULL) {
                *last_node = prev;
            }
            return current;
        }
        prev = current; 
        current = current->next;
    }

    if (last_node != NULL) *last_node = NULL;
    return NULL;
}

void create_task(Kanban *kanban, char *title, char *description, int priority, int id) {
    Task *new_task = (Task*) malloc(sizeof(Task));
    if (new_task == NULL) return;

    new_task->title = strdup(title); 
    new_task->description = strdup(description);
    new_task->priority = (enum Priority)priority;
    new_task->status = TODO;
    new_task->id = id;
    new_task->next = NULL;

    append_task(kanban, new_task);
}

void list_tasks(Kanban *kanban) {
    Task *current = kanban->tasks;
    while (current != NULL) {
        printf("ID: %d\n", current->id);
        printf("Titulo: %s\n", current->title);
        printf("Descricao: %s\n", current->description);
        printf("Prioridade: %d\n", current->priority);
        printf("Status: %d\n", current->status);
        current = current->next;
    }
}

void delete_task(Kanban *kanban, int id) {
    Task *prev = NULL;
    Task *target = locate_task(kanban, id, &prev);

    if (target == NULL) {
        printf("Tarefa nao encontrada.\n");
        return;
    }

    if (prev == NULL) {
        kanban->tasks = target->next;
    } else {
        prev->next = target->next;
    }

    free(target->title);
    free(target->description);
    free(target);
    
    printf("Tarefa removida!\n");
}

void update_task(Kanban *kanban, int id, char *title, char *description, int priority, int status) {
    Task *task = locate_task(kanban, id, NULL);
    
    if (task == NULL) return;
    
    free(task->title);
    free(task->description);
    
    task->title = strdup(title);
    task->description = strdup(description);
    task->priority = (enum Priority)priority;
    task->status = (enum Status)status;

    printf("Tarefa atualizada!\n");
    printf("Titulo: %s\n", task->title);
    printf("Descricao: %s\n", task->description);
    printf("Prioridade: %d\n", task->priority);
    printf("Status: %d\n", task->status);


}

void save_tasks(Kanban *kanban, char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) return;

    Task *curr = kanban->tasks;
    while (curr) {
        int t_len = strlen(curr->title) + 1;
        int d_len = strlen(curr->description) + 1;

        fwrite(&t_len, sizeof(int), 1, file);
        fwrite(curr->title, sizeof(char), t_len, file);
        fwrite(&d_len, sizeof(int), 1, file);
        fwrite(curr->description, sizeof(char), d_len, file);
        fwrite(&curr->priority, sizeof(enum Priority), 1, file);
        fwrite(&curr->status, sizeof(enum Status), 1, file);

        curr = curr->next;
    }
    fclose(file);
}

void load_tasks(Kanban *kanban, char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return;

    int t_len, d_len;
    while (fread(&t_len, sizeof(int), 1, file) == 1) {
        Task *new_node = malloc(sizeof(Task));
        
        new_node->title = malloc(t_len);
        fread(new_node->title, sizeof(char), t_len, file);

        fread(&d_len, sizeof(int), 1, file);
        new_node->description = malloc(d_len);
        fread(new_node->description, sizeof(char), d_len, file);

        fread(&new_node->priority, sizeof(enum Priority), 1, file);
        fread(&new_node->status, sizeof(enum Status), 1, file);
        new_node->next = NULL;

        append_task(kanban, new_node);
    }
    fclose(file);
}

void free_kanban(Kanban *kanban) {
    Task *current = kanban->tasks;
    Task *next;

    while (current != NULL) {
        next = current->next;

        free(current->title);
        free(current->description);

        free(current);

        current = next;
    }
    
    kanban->tasks = NULL;
}