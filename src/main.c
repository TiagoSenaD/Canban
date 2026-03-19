#include <stdio.h>
#include <stdlib.h>
#include "modulos/kanban/include/kanban.h"
#include "modulos/helpers/include/helpers.h"

int id = 1;

int main() {

    Kanban *kanban = (Kanban*) malloc(sizeof(Kanban));
    kanban->tasks = NULL;

    char title[255];
    char description[255];
    int priority = 0;
    int status = 0;
    int id_to_use = 0;

    
    while (1) {
        printf("\n --- Menu ---\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Listar tarefas\n");
        printf("3 - Deletar tarefa\n");
        printf("4 - Atualizar tarefa\n");
        printf("5 - Salvar tarefas\n");
        printf("6 - Carregar tarefas\n");
        printf("7 - Sair\n");
        printf("Digite sua opcao: ");
        int opcao;
        scan_int(&opcao);
        printf("\n");
        switch (opcao) {
            case 1:
                printf("Digite o titulo: ");
                fgets(title, sizeof(title), stdin);
                printf("Digite a descricao: ");
                fgets(description, sizeof(description), stdin);
                printf("1 - Alta\n2 - Media\n3 - Baixa\nEscolha a prioridade: ");
                scan_int(&priority);
                if (priority > 3 || priority < 1) {
                    printf("Prioridade invalida!\n");
                    break;
                }
                create_task(kanban, title, description, priority, id);
                id++;
                break;
            case 2:
                list_tasks(kanban);
                break;
            case 3:
                printf("Qual tesk sera deletada?");
                scan_int(&id_to_use);
                if (locate_task(kanban, id_to_use, NULL) == NULL) {
                    printf("Tarefa nao encontrada!\n");
                    break;
                }
                delete_task(kanban, id_to_use);
                break;
            case 4:
                printf("Qual tesk sera atualizada?");
                scan_int(&id_to_use);
                if (locate_task(kanban, id_to_use, NULL) == NULL) {
                    printf("Tarefa nao encontrada!\n");
                    break;
                }
                printf("Digite o novo titulo: ");
                fgets(title, sizeof(title), stdin);
                printf("Digite a nova descricao: ");
                fgets(description, sizeof(description), stdin);
                printf("1 - Alta\n2 - Media\n3 - Baixa\nEscolha a nova prioridade: ");
                scan_int(&priority);
                if (priority > 3 || priority < 1) {
                    printf("Prioridade invalida!\n");
                    break;
                }

                update_task(kanban, id_to_use, title, description, priority, status);
                break;
            case 5:
                save_tasks(kanban, "tasks.bin");
                break;
            case 6:
                load_tasks(kanban, "tasks.bin");
                break;
            case 7:
                free_kanban(kanban);
                return 0;
            default:
                printf("Opcao invalida!\n");
                break;
        }

    }
    return 0;
}