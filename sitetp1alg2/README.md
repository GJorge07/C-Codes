# tp1-alg2

O Pronto Socorro "Heap or Quick" é muito importante na sua comunidade, atendendo todo tipo de emergência médica. Quando chega ao Pronto Socorro, o paciente é imediatamente encaminhado para a Enfermeira Chefe da Recepção. Ela é uma senhora muito experimente e imediatamente determina a prioridade do paciente e faz seu cadastramento na Fila de Prioridades.

Programe uma Fila de Prioridades para a Enfermeira Chefe, implementando o Tipo Abstrato de Dados Heap. Cada paciente tem cadastrado nome e prioridade. As operações que devem ser disponibilizadas incluem: InicHeap, InsereHeap, RemoveHeap, Heapfy, ChecaHeap, ImprimeHeap, HeapSort (entre outras que forem necessárias). O sistema deve permitir que a Enfermeira Chefe cadastre os pacientes que chegam à UPA, que chame o próximo que vai ser atendido (removendo do Heap, RemoveHeap), que imprima todos na sala de espera, que ordene todos os pacientes de acordo com sua prioridade. Além disso, a Enfermeira Chefe costuma passear pela sala de espera monitorando os pacientes e pode atualizar a prioridade de algum paciente que piorou ou melhorou (AlteraHeap). A qualquer momento deve ser possível imprimir o Heap.

O Heap deve ser implementado em vetor, exatamente como foi visto em sala de aula. Quando executar as funções Heapfy e HeapSort deve ser reportado o número de comparações e trocas de elemento de posição que foram executadas. No Relatório descreva todas as operações implementadas. Explique sua implementação das operações, em particular as operações RemoveHeap e AlteraHeap. Faça uma interface caprichada (menu de opções) para a Enfermeira Chefe usar seu sistema.

Implemente também os algoritmos de ordenação QuickSort e SelectSort. Implemente o QuickSort usando como pivô o elemento que é a mediana entre o primeiro, meio e último elementos do (sub-)vetor. Faça uma opção no menu para gerar um vetor de números aleatórios com 1024 elementos e mostre a comparação do HeapSort com o QuickSort e o SelectSort. Qual foi melhor na prática? Para cada algoritmo mostre o número de comparações e trocas de elemento de lugar.

Deve ser construída uma página Web, que contém em documentos HTML, os seguintes itens:
1. Relatório de como foi feito o trabalho e quais foram os resultados obtidos. Use desenhos, diagramas, figuras, todos os recursos que permitam ao professor compreender como a dupla estruturou o trabalho e quais resultados obteve.
2. Listagem do programa em C; por favor acrescente a terminação ".txt" aos programas fonte na versão disponibilizada na Web, por exemplo: HeapAndQuick.c.txt
3. Log dos testes executados: mostre explicitamente diversos casos 
testados, lembre-se à a partir desta listagem de testes que o professor vai medir até que ponto o trabalho está funcionando.
