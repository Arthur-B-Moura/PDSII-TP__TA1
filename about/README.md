<h1>User Stories</h1>

- Como usuário, eu quero pesquisar um destino, para que eu possa encontrar o lugar para onde quero ir.
- Como usuário, eu quero selecionar um ponto de partida e um destino, para que eu possa traçar uma rota.
- Como usuário, eu quero seguir instruções de navegação passo a passo, para que eu não me perca durante a viagem.
- Como usuário, eu quero informar ao sistema quais passos da rota foram dados, para que o sistema possa saber onde estou.
- Como usuário, eu quero cancelar ou recalcular uma rota, para que eu possa adaptar minha viagem caso meu destino mude.
- Como usuário, eu quero que o sistema estime o tempo de viagem, para que eu possa planejar melhor meu trajeto.
- Como usuário, eu quero salvar locais favoritos, para que eu possa acessá-los rapidamente no futuro.

---

<h1>Detalhamento de Classes</h1>

<h3>Grafo</h3>

Implementação da estrutura de dados "grafo".

<p align="center">
  <img src="https://github.com/Arthur-B-Moura/PDSII-TP__TA1/blob/9b767d382a8a3b55caa72e6e2d94a4398e6e9577/about/CartoesCRC/Grafo.png" width="500" alt="Cartão CRC Grafo">
</p>

<h3>Map Node</h3>

Essa classe é responsável por gerir os nós das "intersecções", isso é, dos cruzamentos, que compõe o grafo e o layout da cidade. Ela inclui estimativas de latitude e longitude que podem ser utilizadas para calcular distância em termos globais, além de auxiliar numa possível representação gráfica modular do mapa.

<p align="center">
  <img src="https://github.com/Arthur-B-Moura/PDSII-TP__TA1/blob/d54c3540843b85705aaa9d81f4ee12d210abb227/about/CartoesCRC/MapNode.png" width="500" alt="Cartão CRC MapNode">
</p>


<h3>Map</h3>

Representação de fato do mapa trabalhado. Herdeira de Grafo, uma vez que utiliza todas as suas funcionalidades para permitir realização de operações lógicas de navegação, mas trás adições específicas à implementação de um mapa (no sentido cartográfico) no programa.

<p align="center">
  <img src="https://github.com/Arthur-B-Moura/PDSII-TP__TA1/blob/d54c3540843b85705aaa9d81f4ee12d210abb227/about/CartoesCRC/Map.png" width="500" alt="Cartão CRC Map">
</p>

<h3>Map Generator</h3>

Essa classe é responsável por converter descrições de mapa de arquivos .csv ou .json em objetos Mapa que possam ser interpretados pelo programa. Sua implementação permite que templates de mapa sejam armazenados em arquivos de texto, possibilitando, inclusive, o compartilhamento de arquivos-mapa entre usuários.

<p align="center">
  <img src="https://github.com/Arthur-B-Moura/PDSII-TP__TA1/blob/777f2d99d7b54cfd4cace646398eaf81ac1bf6d1/about/CartoesCRC/MapGenerator.png" width="500" alt="Cartão CRC Map Generator">
</p>

<h3>Pathfinder</h3>

Implementação do algoritmo pathfinder A* dentro do contexto de grafo desenvolvido. O algoritmo irá navegar de um ponto origem a um ponto destino, e deverá ser capaz de retornar uma lista de nós intermediários que constituam o caminho traçado. 

<p align="center">
  <img src="https://github.com/Arthur-B-Moura/PDSII-TP__TA1/blob/9b767d382a8a3b55caa72e6e2d94a4398e6e9577/about/CartoesCRC/Pathfinder.png" width="500" alt="Cartão CRC Pathfinder">
</p>
