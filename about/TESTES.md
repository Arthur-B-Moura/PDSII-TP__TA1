# Testes das classes implementadas

Como parte do processo de desenvolvimento, tomou-se pela montagem de scripts específicos exclusivos para testar a implementação de cada uma das classes e métodos, utilizando o framework catch2. Essa seção irá abordar estes scripts, detalhando como executá-los e exemplificando algumas de suas aplicações.

## Estrutura de arquivos

```
test/
├── test_grafo.cpp
├── test_map.cpp
├── test_map_generator.cpp
├── test_map_node.cpp
└── test_pathfinder.cpp
```

## Dependências

Além das dependências essencias do projeto, a compilação dos scripts de teste demanda o framework catch2. Para instalá-lo basta executar o comando a seguir.

```bash
sudo apt update && sudo apt install catch2
```

## Compilação 

As instruções de compilação dos arquivos de teste estão inclusas no `Makefile`, e seguem estrutura padrão `test_[nome_da_classe]`. Há um script de teste para cada classe implementada, com exceção da classe `map` que, por circunstâncias do processo de desenvolvimento, acabou por fugir do padrão, e não foi testada dessa forma.

Assim, os comandos para compilação dos testes são:

- `make test_map_node` --> MapNode
- `make test_grafo` --> Grafo
- `make test_map_generator` --> MapGenerator
- `make test_pathfinder` --> PathFinder

Todas estas instruções resultam na criação de um arquivo executável `diagnosis.exe`. Sua execução efetuará os testes descritos no script equivalente.

## Execução

É recomendado que a execução do diagnóstico tenha sua saída direcionada a um arquivo de texto, uma vez que, em caso de falha, o _output_ pode extender-se razoavelmente. Um exemplo de forma de execução é:

```bash
./diagnosis.exe >> exit.txt
```

## Exemplos de saída

A execução esperada de um script de teste, isso, em que todos os casos de teste (TEST_CASES) são sucedidos, segue a seguinte forma:

```
===============================================================================
All tests passed (4 assertions in 2 test cases)
```

Caso algum erro ocorra, este será apontado no output de forma como:

```
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
diagnosis.exe is a Catch v2.13.8 host application.
Run with -? for options

-------------------------------------------------------------------------------
Mostrando falha em teste
-------------------------------------------------------------------------------
test/test_map_node.cpp:14
...............................................................................

test/test_map_node.cpp:15: FAILED:
  REQUIRE( 0==1 )
with expansion:
  0 == 1

===============================================================================
test cases: 3 | 2 passed | 1 failed
assertions: 5 | 4 passed | 1 failed
```