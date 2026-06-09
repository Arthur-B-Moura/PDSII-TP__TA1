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

- [Detalhamento de Classes e User Stories](./about/README.md)


---

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
make run
```

Isso irá gerar um executável `pdsii_maps.exe`, que conta com todas as funcionalidades do projeto.
