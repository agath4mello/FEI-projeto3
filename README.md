# FEI-projeto3

Atividade: Lista de Tarefas - parte 2
Objetivo: Adicionar novas funcionalidades ao código desenvolvido no projeto 1 para o curso de DESENVOLVIMENTO DE ALGORITMOS da FEI - SBC.

Lista de funções adicionadas na segunda etapa:
• 1° Função: Modificação do estado da tarefa
Nesta função é possível efetuar a alteração do estado da tarefa. É apresentado as seguintes opções para escolha: 2 - completo; 1 - em andamento; 0 - não iniciado (ordem ao contrário).
• 2° Função: Modificação dos dados da tarefa
Nesta função, é permitido ao usuário escolher uma tarefa da lista existente (é necessário que tenha informações adicionadas), além do campo em que deseja realizar a mudança.
  *O sistema sobrescreve os dados.
• 3° Função: Filtrar tarefas por prioridade
Nesta função, é apresentada na tela as tarefas que possuem a prioridade escolhida pelo usuário, ou seja, se a prioridade ter o valor = 9, então todas as tarefas com o mesmo peso serão mostradas.
• 4° Função: Filtrar tarefas por estado
A mesma lógica da função anterior. A diferença, neste caso, é que a chave principal da busca do sistema é o estado em que a tarefa se enquadra, ou seja, se o usuário escolher o estado "NÃO INICIADO", por exemplo, todas as tarefas que se adequam a busca serão apresentadas na tela.
• 5° Função: Filtrar tarefas por categoria
Detém a mesma lógica dos dois filtros anteriores (acima), contudo o filtro é realizado por categoria, enquanto que a prioridade é ordenada descrescentemente (maior para menor).
• 6° Funçao: Filtrar tarefas por prioridade e categoria
Detém a mesma lógica dos dois filtros anteriores (acima), contudo o filtro é realizado por categoria e prioridade, onde o programa exibe as tarefas que passam por eles.

------ até aqui CLion estava funcionando normalmente. ------ 

7° funçao - Exportar tarefas por prioridade: seu programa deve gerar um arquivo texto listando apenas as tarefas da prioridade escolhida pelo usuário. Cada tarefa deve estar em uma linha do arquivo na sequência: prioridade, categoria, estado e descrição;
8° funçao - Exportar tarefas por categoria: idem ao anterior, inclusive no formato do arquivo exportado, sendo que as tarefas devem estar ordenadas por prioridade;
9° funçao - Exportar tarefas por prioridade e categoria: junção dos filtros anteriores, mantendo o formato do arquivo que deve ser exportado.

Extra: Além destas, você deve alterar as funções que já foram implementadas para aceitar o armazenamento do estado da tarefa.