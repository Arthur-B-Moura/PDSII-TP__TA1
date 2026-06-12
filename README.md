<div>
  <img style="100%" src="https://capsule-render.vercel.app/api?type=waving&height=100&section=header&reversal=false&fontSize=70&fontColor=FFFFFF&fontAlign=50&fontAlignY=50&stroke=-&descSize=20&descAlign=50&descAlignY=50&theme=cobalt"  />
</div>

###
<h1 align="center">Repositório para TP de PDSII - 2026/1</h1>

<h3>Integrantes do grupo:</h3>

- Arthur Bertolini Moura
- Bernardo de Sousa Vieira
- Heitor Augusto Oliveira Costa de Amorim


<h3>Descrição do tema:</h3>

O sistema apresentado conta com a implementação de um mecanismo _pathfinder_ para navegação, inspirado por _Google Maps_. Com esse fim, o projeto inclui uma seção responsável por gerir os mapas providos, traduzindo-os para um formato inteligível pelo algoritmo _patfinder_ A*, implementado na segunda seção. O programa, então, retorna uma série de instruções, contruindo um caminho do ponto demarcado como "início" até o "fim".

---

<h2>Seções da Documentação:</h2>

Além desta página, o projeto inclui as seguintes seções de documentação:

- [Vídeo da Execução do Projeto](https://www.youtube.com/watch?v=XTVSJ3BJGlI)
- [Documentação Automática feita com Doxygen](https://arthur-b-moura.github.io/PDSII-TP__TA1/index.html)
- [Detalhamento de Classes e User Stories](./about/CLASS_INFO.md)
- [Descrição do Desenvolvimento do Projeto](./about/DESENVOLVIMENTO.md)
- [Detalhamento e Execução dos Scripts de Teste](./about/TESTES.md)
- [Instruções para Inclusão de Outros Mapas](./about/INSERCAO_DE_MAPAS.md)

---

## Estrutura do repositório

```
.
├── Doxyfile
├── Makefile
├── README.md
├── about
│   ├── CLASS_INFO.md
│   ├── CartoesCRC
│   │   ├── Grafo.png
│   │   ├── Map.png
│   │   ├── MapGenerator.png
│   │   ├── MapNode.png
│   │   └── Pathfinder.png
│   ├── DESENVOLVIMENTO.md
│   ├── INSERCAO_DE_MAPAS.md
│   ├── Imagens
│   │   ├── CicloDev.png
│   │   └── FluxoDesenvovilmento.png
│   └── TESTES.md
├── build
├── html
│   └── extra_style_sheet.css
├── include
│   ├── grafo.h
│   ├── map.h
│   ├── map_generator.h
│   ├── map_node.h
│   └── pathfinder.h
├── maps
│   ├── map.osm
│   ├── map.osm:Zone.Identifier
│   ├── map_liberdade.osm
│   └── map_liberdade.osm:Zone.Identifier
├── src
│   ├── grafo.cpp
│   ├── main.cpp
│   ├── map.cpp
│   ├── map_generator.cpp
│   ├── map_node.cpp
│   └── pathfinder.cpp
└── test
    ├── test_grafo.cpp
    ├── test_map.cpp
    ├── test_map_generator.cpp
    ├── test_map_node.cpp
    └── test_pathfinder.cpp
```

## Utilização básica

A seguinte seção direciona os passos e requerimentos necessários para a execução da solução apresentada no projeto.

### Sistema operacional

A execução dos scripts descrita considera uma máquina rodando `Ubuntu-22.04` . Pode ser esta por meio de um *boot* específico, ou a partir de máquina virtual, como *wsl*.

### Dependências externas

Para compilar e executar o projeto, além dos arquivos nele implementado, é necessário que tenha instalado, em sua máquina, os seguintes itens:

- Ferramentas de compilação (g++, make)
- Biblioteca libxml++

A seguir, seguem as instruções para verificar tais instalações e, caso necessário, realizá-las.

#### Ferramentas de compilação (g++, make):

Ambas essas ferramentas podem ser instaladas pelo terminal, a partir do *build-essentials:*

```bash
sudo apt update && sudo apt install build-essentials
```

Para verificar suas instalações, basta executar o seguinte comando:

```bash
g++ --version
```

> OBS: o projeto foi compilado em sua produção com `g++ 11.4.0` . O uso de outras versões do compilador pode acarretar em comportamento não esperado.
> 

#### Biblioteca libxml++

Essa biblioteca é responsável pela leitura dos arquivos de mapa em xml (por exemplo, os arquivos .osm). Sua instalação pode, também, ser feita por linha de comando:

```bash
sudo apt update && sudo apt install libxml++2.6-dev
```

Para verificar sua instalação, basta executar o seguinte comando, que exibe os parâmetros da versão:

```bash
pkg-config libxml++-2.6 --modversion
```

> OBS: Note que o projeto utiliza a versão 2.6 dessa biblioteca. **É necessário que instale exatamente esta versão**, uma vez que versões superiores ou inferiores podem contar com diversas diferenças, inclusive impedindo a compilação.
> 

### Download e compilação

Para utilizar os arquivos do projeto, navegue a um repositório de sua escolha e execute o seguinte comando para clonar projeto diretamente de seu repositório do GitHub:

```bash
git clone https://github.com/Arthur-B-Moura/PDSII-TP__TA1.git
```

Em seguida, basta navegar até o *root* do projeto…

```bash
cd PDSII-TP__TA1
```

… e realizar a compilação a partir do *make*:

```bash
make 
```

Isso irá gerar um executável `main.exe`, que conta com todas as funcionalidades do projeto.

Alternativamente, o usuário pode rodar diretamente o comando a seguir, que irá, além de compilar o projeto, executá-lo.

```bash
make run
```

---

## Execução

Caso tenha compilado o projeto a partir do comando `make` padrão, basta executá-lo a partir da root de seu diretório para rodar o programa:

```bash
./main.exe
```

Ao executar o programa, será apresentado um menu com as opções de execução e geração de rota. Interaja com o menu a partir de input do teclado diretamente no terminal. O input de opções inválidas não será considerado.

O projeto inclui, de forma padrão, dois arquivos de mapa, ambos presentes no diretório `maps/`:

- `map_liberdade.osm` --> região aproximadamente dos bairros Liberdade, Indaiá e Jaraguá de Belo Horizonte
- `map.osm` --> inclui a maior parte da região Pampulha, UFMG, parte do Centro, Ouro Preto, Liberdade, Jaraguá, etc. É um mapa de grande escala, e sua execução será lenta

Caso deseje navegar por outras localidades, siga as instruções da [seção sobre inserção de mapas](./about/INSERCAO_DE_MAPAS.md).

## Tratamento de exceções

Optou-se por utilizar exceções-padrão `std` nos diversos pontos do projeto. No geral, o tratamento de excessões ocorreu de forma a não permitir que valores incorretos fossem inseridos (isto é, com um loop que seria apenas terminado uma vez que o input correto fosse inserido). A exceção principal disto está no em erros de parsing do arquivo-mapa. Nesse caso, uma mesagem de erro é imprimida ao `std::cerr`, e um objeto-mapa vazio é retornado, efetivamente forçando o usuário a selecionar outro arquivo.
