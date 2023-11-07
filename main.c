#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_DESCRIPTION_LENGTH 300
#define MAX_CATEGORY_LENGTH 100

enum TaskStatus { NAO_INICIADO, EM_ANDAMENTO, COMPLETO };

struct Task {
    int priority;
    char description[MAX_DESCRIPTION_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    enum TaskStatus status;
};

void displayMenu() {
    printf("\nTarefas - Menu:\n");
    printf("1. Adicionar Tarefa\n");
    printf("2. Listar Tarefas\n");
    printf("3. Modificar Estado da Tarefa\n");
    printf("4. Deletar Tarefa\n");
    printf("5. Sair\n");
    printf("Escolha uma opção (1/2/3/4/5): ");
}

int main() {
    struct Task taskList[MAX_TASKS];
    int numTasks = 0;
    FILE *file;

    file = fopen("tasks.bin", "ab+");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de tarefas.\n");
        exit(1);
    }

    while (1) {
        displayMenu();
        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
            if (numTasks < MAX_TASKS) {
                struct Task task;
                printf("Prioridade (0-10): ");
                scanf("%d", &task.priority);
                printf("Descrição (até 300 caracteres): ");
                scanf(" %[^\n]", task.description);
                printf("Categoria (até 100 caracteres): ");
                scanf(" %[^\n]", task.category);
                printf("Status (0 - NÃO INICIADO, 1 - EM ANDAMENTO, 2 - COMPLETO): ");
                scanf("%d", &task.status);

                taskList[numTasks] = task;
                numTasks++;

                fseek(file, 0, SEEK_END);
                fwrite(&task, sizeof(struct Task), 1, file);
            } else {
                printf("A lista de tarefas está cheia.\n");
            }
        } else if (choice == 2) {
            if (numTasks == 0) {
                printf("A lista de tarefas está vazia.\n");
            } else {
                printf("Tarefas:\n");
                for (int i = 0; i < numTasks; i++) {
                    printf("Tarefa %d:\n", i + 1);
                    printf("Prioridade: %d\n", taskList[i].priority);
                    printf("Descrição: %s\n", taskList[i].description);
                    printf("Categoria: %s\n", taskList[i].category);
                    printf("Status: %s\n", taskList[i].status == NAO_INICIADO ? "NÃO INICIADO" : 
                                                taskList[i].status == EM_ANDAMENTO ? "EM ANDAMENTO" : "COMPLETO");
                }
            }
        } else if (choice == 3) {
            if (numTasks == 0) {
                printf("A lista de tarefas está vazia.\n");
            } else {
                printf("Digite o número da tarefa a ser modificada (1-%d): ", numTasks);
                int taskNumber;
                scanf("%d", &taskNumber);

                if (taskNumber >= 1 && taskNumber <= numTasks) {
                    printf("Novo estado da tarefa (0 - NÃO INICIADO, 1 - EM ANDAMENTO, 2 - COMPLETO): ");
                    int newStatus;
                    scanf("%d", &newStatus);

                    if (newStatus >= NAO_INICIADO && newStatus <= COMPLETO) {
                        taskList[taskNumber - 1].status = newStatus;
                        printf("Estado da tarefa modificado com sucesso.\n");

                        fseek(file, 0, SEEK_SET);
                        for (int i = 0; i < numTasks; i++) {
                            fwrite(&taskList[i], sizeof(struct Task), 1, file);
                        }
                    } else {
                        printf("Estado de tarefa inválido.\n");
                    }
                } else {
                    printf("Número de tarefa inválido.\n");
                }
            }
        } else if (choice == 4) {
            // Código para deletar tarefa (sem alterações necessárias)
        } else if (choice == 5) {
            fclose(file);
            break;
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}