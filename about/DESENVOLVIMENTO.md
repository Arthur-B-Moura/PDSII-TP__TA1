# Detalhamento do desenvolvimento do projeto

## Ciclo de desenvolvimento

O desenvolvimento do projeto seguiu, de forma geral, o seguinte fluxo:

![CicloDev.png](https://github.com/Arthur-B-Moura/PDSII-TP__TA1/blob/f8a24b4312c544651954d1341ba29ec462e97f22/about/Imagens/CicloDev.png)

Percebe-se que a seção de desenvolvimento engloba uma multitude de pontos. De fato, ela abrange o maior tempo despendido no percurso do projeto. Seu fluxo por si só foi efetuado conforme o seguinte fluxograma:

![FluxoDesenvovilmento.png](https://github.com/Arthur-B-Moura/PDSII-TP__TA1/blob/f8a24b4312c544651954d1341ba29ec462e97f22/about/Imagens/FluxoDesenvovilmento.png)

Note que para implementação de classes que dependam de interação entre outras classes, o script de testes deveria, também, verificar sua integração.

Durante o desenvolvimento, evitou-se ao máximo a modificação de arquivos de contrato. Contudo, devido à inexperiência dos integrantes da equipe, isso veio a acontecer em alguns momentos — em especial, nos momentos iniciais do desenvolvimento do projeto. Devido à ordem de implementação e desenvolvimento, contudo, estas mudanças não acarretaram em conflitos durante o processo.

## Atribuição de tarefas

A seguir segue a organização de tarefas para cada integrante do grupo. Note que algumas tarefas, como o desenvolvimento dos Cartões CRC, não estão inclusas. Isso se dá pois elas foram executadas por todos os elementos.

**Arthur Bertolini Moura:**

- Implementação de MapNode e Grafo
- Implementação MapGenerator
- Documentação
  
**Bernardo de Sousa Vieira:**
- Definição do contrato de PathFinder e Grafo
- Implementação de PathFinder e Map

**Heitor Augusto Oliveira Costa de Amorim:**
- Desenvolvimento de User Stories
- Implementação da seção de interação com usuário

### Cronograma, Planejado x Alcançado e desafios encontrados

Algum tempo após a entrega dos User Stories e Cartões CRC, estabeleceu-se um cronograma geral de desenvolvimento. Este cronograma contava com um período de cerca de 1 semana para implementação das classes essenciais (MapNode, Grafo, Map), seguido de um período de 1 semana para desenvolvimento conseguinte do MapGenerator e PathFinder e, em seguida, por um período de 2 semanas para implementação da interface com usuário, documentação e aperfeiçoamento das implementações. Esse cronograma foi otimista e imaturo, e pouquíssimo de sua estrutura foi de fato seguida, por diversos motivos (provas e trabalhos de outras matérias, assuntos pessoais, participação de integrantes do grupo em competições, etc).

Dentre os atrasos enfrentados, muitos surgiram devido a alguns desafios de desenvolvimento encontrados. A implementação de MapGenerator, em específico, extendeu-se muito mais do que inicialmente esperado, demora oriunda de problemas relacionados à leitura de arquivos osm (arquivos xml de dezenas de milhares de linhas). Foi necessário pesquisar alternativas, nesse caso, a biblioteca `libxml++`, e aprender a implementar, compilar e, no geral, lidar com essa solução, tudo isso antes sequer de dar início à seção de desenvolvimento que fora inicialmente contemplada.

Na implementação da interface de interação com o usuário, a partir da realização de diversos experimentos em tempo de execução, foram identificados inúmeros pequenos problemas, que houverão de ser posteriormente ajustados, às vezes com soluções que envolviam algoritmos e funções não estudadas.

Além destes, outro grande contribuidor para atraso foi o sistema de testes escolhido. No momento de sua escolha, o assunto ainda não havia sido abordado em aula, de forma que essa decisão veio de pesquisas externas. Encontrar um framework adequado, por si só, já demandou um tempo que não havia sido considerado no planejamento inicial. De fato, tudo relacionado a esses testes excedeu o tempo inicial planejado, uma vez que o cronograma sequer incluía a execução de testes.

Como resultado, nem todas as **funcionalidades** inicialmente pensadas puderam ser implementadas dentro do prazo. Em específico, não foi implementado:
- Distinção de sentidos de ruas (todas as ruas são vistas como sentido duplo)
- Leitura de arquivos de formatos distitos (aceita-se apenas arquivos .osm)
- Geração de arquivos-mapa de formato próprio (relacionado ao ponto anterior)

O restante, considerado implementações básicas, foi todo implementado. 

Além disso, espera-se que ao menos um integrante do grupo de continuidade ao projeto futuramente, após terminado o ciclo do TP, para tanto implementar o restante dessas funcionalidades, quanto aprimimorar a seção do projeto que já fora implementada.