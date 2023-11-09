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
    printf("5. Alterar Tarefa\n");
    printf("6. Filtrar Tarefas por Prioridade\n");
    printf("7. Filtrar Tarefas por Estado\n");
    printf("8. Sair\n");
    printf("Escolha uma opção (1/2/3/4/5/6/7/8): ");
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

  // Ler tarefas do arquivo
    while (fread(&taskList[numTasks], sizeof(struct Task), 1, file) == 1)
    {
      numTasks++;
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
                printf("Tarefas:\n\n");
                for (int i = 0; i < numTasks; i++) {
                    printf("Tarefa %d:\n", i + 1);
                    printf("Prioridade: %d\n", taskList[i].priority);
                    printf("Descrição: %s\n", taskList[i].description);
                    printf("Categoria: %s\n", taskList[i].category);
                    printf("Status: %s\n", taskList[i].status == NAO_INICIADO ? "NÃO INICIADO\n" : 
                                                taskList[i].status == EM_ANDAMENTO ? "EM ANDAMENTO\n" : "COMPLETO\n");
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
            // Código para deletar tarefa
        } else if (choice == 5) {
            if (numTasks == 0) {
                printf("A lista de tarefas está vazia.\n");
            } else {
                printf("Digite o número da tarefa a ser alterada (1-%d): ", numTasks);
                int taskNumber;
                scanf("%d", &taskNumber);

                if (taskNumber >= 1 && taskNumber <= numTasks) {
                    int fieldChoice;
                    printf("Escolha o campo a ser alterado:\n");
                    printf("1. Prioridade\n");
                    printf("2. Descrição\n");
                    printf("3. Categoria\n");
                    printf("4. Estado\n");
                    printf("Escolha uma opção (1/2/3/4): ");
                    scanf("%d", &fieldChoice);

                    if (fieldChoice >= 1 && fieldChoice <= 4) {
                        struct Task *task = &taskList[taskNumber - 1];

                        switch (fieldChoice) {
                            case 1:
                                // Alterar prioridade
                                printf("Nova prioridade (0-10): ");
                                scanf("%d", &task->priority);
                                break;
                            case 2:
                                // Alterar descrição
                                printf("Nova descrição (até 300 caracteres): ");
                                scanf(" %[^\n]", task->description);
                                break;
                            case 3:
                                // Alterar categoria
                                printf("Nova categoria (até 100 caracteres): ");
                                scanf(" %[^\n]", task->category);
                                break;
                            case 4:
                                // Alterar estado
                                printf("Novo estado (0 - NÃO INICIADO, 1 - EM ANDAMENTO, 2 - COMPLETO): ");
                                int newStatus;
                                scanf("%d", &newStatus);

                                if (newStatus >= NAO_INICIADO && newStatus <= COMPLETO) {
                                    task->status = newStatus;
                                } else {
                                    printf("Estado de tarefa inválido.\n");
                                }
                                break;
                            default:
                                printf("Opção inválida. Tente novamente.\n");
                        }

                        printf("Tarefa alterada com sucesso.\n");

                        // Atualizar o arquivo com as tarefas alteradas
                        fseek(file, 0, SEEK_SET);
                        for (int i = 0; i < numTasks; i++) {
                            fwrite(&taskList[i], sizeof(struct Task), 1, file);
                        }
                    } else {
                        printf("Opção de campo inválida. Tente novamente.\n");
                    }
                } else {
                    printf("Número de tarefa inválido.\n");
                }
            }
        } else if (choice == 6) {
            // Filtrar tarefas por prioridade
            printf("Filtrar Tarefas por Prioridade (0-10): ");
            int filterPriority;
            scanf("%d", &filterPriority);

            printf("Tarefas com Prioridade %d:\n", filterPriority);
            for (int i = 0; i < numTasks; i++) {
                if (taskList[i].priority == filterPriority) {
                    printf("Tarefa %d:\n", i + 1);
                    printf("Prioridade: %d\n", taskList[i].priority);
                    printf("Descrição: %s\n", taskList[i].description);
                    printf("Categoria: %s\n", taskList[i].category);
                    printf("Status: %s\n", taskList[i].status == NAO_INICIADO ? "NÃO INICIADO\n" : 
                                                taskList[i].status == EM_ANDAMENTO ? "EM ANDAMENTO\n" : "COMPLETO\n");
                }
            }
        } else if (choice == 7) {
            // Filtrar tarefas por estado
            printf("Filtrar Tarefas por Estado (0 - NÃO INICIADO, 1 - EM ANDAMENTO, 2 - COMPLETO): ");
            int filterStatus;
            scanf("%d", &filterStatus);

            printf("Tarefas com Estado %s:\n", filterStatus == NAO_INICIADO ? "NÃO INICIADO\n" : 
                                                filterStatus == EM_ANDAMENTO ? "EM ANDAMENTO\n" : "COMPLETO\n");
            for (int i = 0; i < numTasks; i++) {
                if (taskList[i].status == filterStatus) {
                    printf("Tarefa %d:\n", i + 1);
                    printf("Prioridade: %d\n", taskList[i].priority);
                    printf("Descrição: %s\n", taskList[i].description);
                    printf("Categoria: %s\n", taskList[i].category);
                    printf("Status: %s\n", taskList[i].status == NAO_INICIADO ? "NÃO INICIADO\n" : 
                                                taskList[i].status == EM_ANDAMENTO ? "EM ANDAMENTO\n" : "COMPLETO\n");
                }
            }
        } else if (choice == 8) {
            // Fechar o arquivo e sair
            fclose(file);
            break;
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}