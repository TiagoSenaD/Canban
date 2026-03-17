#include <stdio.h>
#include <stdlib.h>
#include "modulos/kanban/include/kanban.h"

int main() {

    Kanban *kanban = (Kanban*) malloc(sizeof(Kanban));
    kanban->tasks = NULL;

    char title[255];
    char description[255];
    int priority = 0;
    int status = 0;

    
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
        scanf("%d", &opcao);
        printf("\n");
        switch (opcao) {
            case 1:
                printf("Digite o titulo: ");
                scanf("%s", title);
                printf("Digite a descricao: ");
                scanf("%s", description);
                printf("1 - Alta\n2 - Media\n3 - Baixa\nEscolha a prioridade: ");
                scanf("%d", &priority);
                if (priority > 3 || priority < 1) {
                    printf("Prioridade invalida!\n");
                    break;
                }
                create_task(kanban, title, description, priority);
                break;
            case 2:
                list_tasks(kanban);
                break;
            case 3:
                printf("Qual tesk sera deletada?");
                scanf("%s", title);
                if (locate_task(kanban, title, NULL) == NULL) {
                    printf("Tarefa nao encontrada!\n");
                    break;
                }
                delete_task(kanban, title);
                break;
            case 4:
                printf("Qual tesk sera atualizada?");
                scanf("%s", title);
                printf("Digite o novo titulo: ");
                scanf("%s", title);
                printf("Digite a nova descricao: ");
                scanf("%s", description);
                printf("1 - Alta\n2 - Media\n3 - Baixa\nEscolha a nova prioridade: ");
                scanf("%d", &priority);
                if (priority > 3 || priority < 1) {
                    printf("Prioridade invalida!\n");
                    break;
                }
                if (locate_task(kanban, title, NULL) == NULL) {
                    printf("Tarefa nao encontrada!\n");
                    break;
                }
                update_task(kanban, title, description, priority, status);
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