#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//variáveis responsáveis por criar macros no pré-processador C.
//lembrar que elas são substituídas pelo pré-processador antes da compilação do código, como se fossem substituições de texto.
#define MAX_TAREFAS 100
#define MAX_DESCRICAO 300
#define MAX_CATEGORIA 100

//responsável por representar os possíveis estados de uma tarefa
enum TarefaStatus { NAO_INICIADO, EM_ANDAMENTO, COMPLETO };

//responsável por representar a estrutura existente em uma tarefa
struct Task {
    int prioridade;
    char descricao[MAX_DESCRICAO];
    char categoria[MAX_CATEGORIA];
    enum TarefaStatus status;
};

//responsável pelo menu apresentado ao usuário
void displayMenu() {
    printf("\nTarefas - Menu:\n");
    printf("1. Adicionar Tarefa\n");
    printf("2. Listar Tarefas\n");
    printf("3. Modificar Estado da Tarefa\n");
    printf("4. Deletar Tarefa\n");
    printf("5. Alterar Tarefa\n");
    printf("6. Filtrar Tarefas por Prioridade\n");
    printf("7. Filtrar Tarefas por Estado\n");
    printf("8. Filtrar Tarefas por Categoria (Prioridade Decrescente)\n");
    printf("9. Filtrar Tarefas por Prioridade e Categoria\n");
    printf("10. Sair\n");
    printf("Escolha uma opção (1/2/3/4/5/6/7/8/9/10): ");
}

// Função de comparação para classificar as tarefas por prioridade em ordem decrescente, ou seja, é a responsável por comparar as tarefas e então classificá-las de acordo com o parametro inserido.
      int compareTasks(const void *task1, const void *task2) {
        return ((struct Task *)task2)->prioridade - ((struct Task *)task1)->prioridade;
      }

      int main() {
        struct Task taskList[MAX_TAREFAS];
        int numTasks = 0;
        FILE *file;
        //responsável por fazer o o programa encerre se houver algum problema ao abrir o arquivo de leitura e escrita em modo binário
        file = fopen("tasks.bin", "ab+");
        if (file == NULL) {
            printf("Erro ao abrir o arquivo de tarefas.\n");
            exit(1);
        }

        // responsável por ler tarefas do arquivo
        while (fread(&taskList[numTasks], sizeof(struct Task), 1, file) == 1) {
            numTasks++;
        }

        while (1) {
            displayMenu();
            int choice;
            scanf("%d", &choice);

        if (choice == 1) {
            if (numTasks < MAX_TAREFAS) {
                struct Task task;
                printf("Prioridade (0-10): ");
                scanf("%d", &task.prioridade);
                printf("Descrição (até 300 caracteres): ");
                scanf(" %[^\n]", task.descricao);
                printf("Categoria (até 100 caracteres): ");
                scanf(" %[^\n]", task.categoria);
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
          //Código responsável por listar tarefas
          //Mas, antes de listar, ordena as tarefas por prioridade em ordem decrescente
          qsort(taskList, numTasks, sizeof(struct Task), compareTasks);

          for (int i = 0; i < numTasks; i++) {
              printf("Tarefa %d:\n", i + 1);
              printf("Prioridade: %d\n", taskList[i].prioridade);
              printf("Descrição: %s\n", taskList[i].descricao);
              printf("Categoria: %s\n", taskList[i].categoria);
              printf("Status: %s\n", taskList[i].status == NAO_INICIADO ? "NÃO INICIADO\n" : 
                                          taskList[i].status == EM_ANDAMENTO ? "EM ANDAMENTO\n" : "COMPLETO\n");
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
                        //responsável por atualizar o arquivo binário com as atualizações realizadas
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
          //Função responsável por deletar tarefas.
          if (numTasks == 0) {
              printf("A lista de tarefas está vazia.\n");
          } else {
              printf("Digite o número da tarefa a ser deletada: ");
              int taskNumber;
              scanf("%d", &taskNumber);

              if (taskNumber >= 1 && taskNumber <= numTasks) {
                  //Remove a tarefa do array
                  for (int i = taskNumber - 1; i < numTasks - 1; i++) {
                      taskList[i] = taskList[i + 1];
                  }

                  numTasks--;

                  //Atualiza o arquivo com as tarefas restantes
                  fseek(file, 0, SEEK_SET);
                  for (int i = 0; i < numTasks; i++) {
                      fwrite(&taskList[i], sizeof(struct Task), 1, file);
                  }

                  printf("Tarefa deletada com sucesso.\n");
              } else {
                  printf("Número de tarefa inválido.\n");
              }
          }
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
                                //Altera prioridade
                                printf("Nova prioridade (0-10): ");
                                scanf("%d", &task->prioridade);
                                break;
                            case 2:
                                //Altera descrição
                                printf("Nova descrição (até 300 caracteres): ");
                                scanf(" %[^\n]", task->descricao);
                                break;
                            case 3:
                                //Altera categoria
                                printf("Nova categoria (até 100 caracteres): ");
                                scanf(" %[^\n]", task->categoria);
                                break;
                            case 4:
                                //Altera estado
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

                        //Atualiza o arquivo com as tarefas alteradas
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
            //Filtra tarefas por prioridade
            printf("Filtrar Tarefas por Prioridade (0-10): ");
            int filterprioridade;
            scanf("%d", &filterprioridade);

            printf("Tarefas com Prioridade %d:\n", filterprioridade);
            for (int i = 0; i < numTasks; i++) {
                if (taskList[i].prioridade == filterprioridade) {
                    printf("Tarefa %d:\n", i + 1);
                    printf("Prioridade: %d\n", taskList[i].prioridade);
                    printf("Descrição: %s\n", taskList[i].descricao);
                    printf("Categoria: %s\n", taskList[i].categoria);
                    printf("Status: %s\n", taskList[i].status == NAO_INICIADO ? "NÃO INICIADO\n" : 
                                            taskList[i].status == EM_ANDAMENTO ? "EM ANDAMENTO\n" : "COMPLETO\n");
                }
            }
        } else if (choice == 7) {
            //Filtra tarefas por estado
            printf("Filtrar Tarefas por Estado (0 - NÃO INICIADO, 1 - EM ANDAMENTO, 2 - COMPLETO): ");
            int filterStatus;
            scanf("%d", &filterStatus);

            printf("Tarefas com Estado %s:\n", filterStatus == NAO_INICIADO ? "NÃO INICIADO\n" : 
                                                filterStatus == EM_ANDAMENTO ? "EM ANDAMENTO\n" : "COMPLETO\n");
            for (int i = 0; i < numTasks; i++) {
                if (taskList[i].status == filterStatus) {
                    printf("Tarefa %d:\n", i + 1);
                    printf("Prioridade: %d\n", taskList[i].prioridade);
                    printf("Descrição: %s\n", taskList[i].descricao);
                    printf("Categoria: %s\n", taskList[i].categoria);
                    printf("Status: %s\n", taskList[i].status == NAO_INICIADO ? "NÃO INICIADO\n" : 
                                            taskList[i].status == EM_ANDAMENTO ? "EM ANDAMENTO\n" : "COMPLETO\n");
                }
            }
        } else if (choice == 8) {
            //Filtra tarefas por categoria (maior para menor)
            printf("Filtrar Tarefas por Categoria: ");
            char filterCategoria[MAX_CATEGORIA];
            scanf(" %[^\n]", filterCategoria);

            printf("Tarefas na Categoria \"%s\" com Prioridade Decrescente:\n", filterCategoria);

            //Filtra e ordena as tarefas por categoria e prioridade
            struct Task filteredTasks[MAX_TAREFAS];
            int numFilteredTasks = 0;

            for (int i = 0; i < numTasks; i++) {
                if (strcmp(taskList[i].categoria, filterCategoria) == 0) {
                    filteredTasks[numFilteredTasks] = taskList[i];
                    numFilteredTasks++;
                }
            }

            //Ordena as tarefas filtradas por prioridade (ordem decrescente)
            qsort(filteredTasks, numFilteredTasks, sizeof(struct Task), compareTasks);

            for (int i = 0; i < numFilteredTasks; i++) {
                printf("Tarefa %d:\n", i + 1);
                printf("Prioridade: %d\n", filteredTasks[i].prioridade);
                printf("Descrição: %s\n", filteredTasks[i].descricao);
                printf("Categoria: %s\n", filteredTasks[i].categoria);
                printf("Status: %s\n", filteredTasks[i].status == NAO_INICIADO ? "NÃO INICIADO\n" : 
                                        filteredTasks[i].status == EM_ANDAMENTO ? "EM ANDAMENTO\n" : "COMPLETO\n");
            }
        } else if (choice == 9) {
            //Filtra tarefas por prioridade e categoria
            printf("Filtrar Tarefas por Prioridade (0-10): ");
            int filterprioridade;
            scanf("%d", &filterprioridade);

            printf("Filtrar Tarefas por Categoria: ");
            char filterCategoria[MAX_CATEGORIA];
            scanf(" %[^\n]", filterCategoria);

            printf("Tarefas com Prioridade %d na Categoria \"%s\":\n", filterprioridade, filterCategoria);

            for (int i = 0; i < numTasks; i++) {
                if (taskList[i].prioridade == filterprioridade && strcmp(taskList[i].categoria, filterCategoria) == 0) {
                    printf("Tarefa %d:\n", i + 1);
                    printf("Prioridade: %d\n", taskList[i].prioridade);
                    printf("Descrição: %s\n", taskList[i].descricao);
                    printf("Categoria: %s\n", taskList[i].categoria);
                    printf("Status: %s\n", taskList[i].status == NAO_INICIADO ? "NÃO INICIADO\n" : 
                                            taskList[i].status == EM_ANDAMENTO ? "EM ANDAMENTO\n" : "COMPLETO\n");
                }
            }
        } else if (choice == 10) {
            //Fecha o arquivo e sai do programa.
            fclose(file);
            break;
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}