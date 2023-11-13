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

Obs.: ------ até aqui CLion estava funcionando normalmente. ------ 

Lista de funções que não foram adicionadas na segunda etapa:
• 7° Funçao: Exportar tarefas por prioridade
Nesta função, o programa gera um arquivo texto, apresentando apenas as tarefas escolhidas pelo usuário, respeitando a seguinte sequência:
  · Prioridade;
  · Categoria;
  · Estado;
  · Descrição.
Caso a sequência não seja obedecida, então o programa deverá gerar uma mensagem de erro.
• 8° Funçao: Exportar tarefas por categoria
Idem ao anterior, inclusive no formato do arquivo exportado, contudo as tarefas devem estar ordenadas por prioridade.
• 9° Funçao: Exportar tarefas por prioridade e categoria
É a junção dos filtros anteriores, mas mantendo o formato do arquivo que deve ser exportado.
• 10° Função: Armazenamento do estado da tarefa
Nesta função, deve ser realizado alterações nas funções anteriores para aceitar o armazenamento do estado da tarefa.
Extra: Além destas, você deve alterar as funções que já foram implementadas para aceitar o armazenamento do estado da tarefa, ou seja, deve ser possível realizar alterações no estado, como "Não Iniciado", "Em Andamento" ou "Completo".

Tecnologias utilizadas:
• Arquivos Binários em C
• Biblioteca Padrão de C
• Compilador C
• Enumerações em C
• Linguagem de Programação C

Inicialização:
O programa pode/deve ser inicializado normalmente através de um compilador que suporte a linguagem C. Entretanto, caso ocorra alguma falha, você pode acessar https://replit.com/@AgathaMello/FEI-projeto3

Implementações futuras:
As implementações futuras para este projeto envolvem conseguir finalizar a inserção das tarefas faltantes no item "Lista de funções que não foram adicionadas na segunda etapa".