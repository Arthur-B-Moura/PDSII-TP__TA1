# Inserção de arquivos de mapas adicionais

Uma vez clonado o repositório do projeto, o usuário já contará com dois arquivos de mapa por padrão:

- `map_liberdade.osm` --> região aproximadamente dos bairros Liberdade, Indaiá e Jaraguá de Belo Horizonte
- `map.osm` --> inclui a maior parte da região Pampulha, UFMG, parte do Centro, Ouro Preto, Liberdade, Jaraguá, etc. É um mapa de grande escala, e sua execução será lenta

Contudo, é possível adicionar outras localidades para navegar. Essa seção irá descrever como realizar esse processo.

## Entendendo o arquivo .osm

Nessa aplicação atual do projeto, aceita-se apenas arquivos-mapa do tipo `.osm`. Implementações futuras aceitarão, também, outros tipos de arquivo, incluindo arquivos de tipo próprio gerado específicamente para o projeto. Atualmente, esse não é o caso.

Arquivos osm são `xml` que descrevem ruas, estruturas e cruzamentos presentes em um certo intervalo de coordenadas geográficas. Eles são gerados como parte do um projeto Open Source e aberto à colaboração: _Open Street Map_. Esse projeto funciona de forma similar à wikipedia, permitindo que usuários externos realizem alterações sobre seu banco de dados, inserindo ou modificando itens relevantes com o intuito de melhorar o mapa.

O projeto de Google Maps desenvolvido para o TP realiza o parsing de arquivos osm, retirando de sua extensa estrutura apenas os ítens relevantes para o objeto de tipo Mapa utilizado. 

## Gerando um .osm

Para gerar um arquivo de mapa, é necessário acessar o [website do projeto OSM](https://www.openstreetmap.org).

Em seguida, deverá navegar até a região de interesse. Note que os arquivos gerados são grandes, de forma que regiões extensas ocasionarão em resultados de execução lenta. Regiões muito extensas (ex: caso tente mapear Belo Horizonte inteira) sequer poderão ser geradas pelo projeto OSM.

Uma vez posicionada a visualização do mapa sobre a região de interesse, deve selecionar a opção "Export" da interface, até que seja efetuado o download automático de um arquivo `.osm`. É recomendado que altere o nome padrão deste arquivo para evitar sobrescrita, mas não é obrigatório.

## Utilizando o arquivo

Para navegar na área mapeada pelo arquivo gerado, basta movê-lo para o diretório `./maps` do repositório deste projeto. Tenha conhecimento do nome com que ele foi salvo para poder se referenciar a ele durante a execução do código.

> OBS: Note que não é obrigatório mover o arquivo para o diretório `./maps`, apenas recomendado, uma vez que o programa utiliza de path com referência ao diretório de execução do main.exe para acessar o arquivo de mapa.