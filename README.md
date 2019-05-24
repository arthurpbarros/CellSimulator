# CellSimulator
Simulador para representar um comportamento celular.

## Compilação e Execução
sh run.sh

## Tratamento
O programa trata erros de entrada, isto é, valores inválidos para as flags existentes e o próprio tratamento das flags

## Arquivo de Configuração
Um arquivo de configuração válido possui os seguintes campos:
h w
b
s1 s2
c
cc........
.cc.......
..........
........c.
.......c.c
c.......c.
.cc.......
.c........
..........
..........

Onde:
h: número de linhas da matriz de células
w: número de colunas da matriz de células
b: número de células necessárias para uma célula morta tornar-se viva
s1: número de 
s2: número de
c: caracter que representa a célula viva na matriz, por exemplo o '$'. As células com qualquer outro caracter são consideradas mortas. OBS: Não é preciso indicar todas as mortas.

## Limitações
O programa possui uma classe main pouco modularizada, isto é, possui muitos métodos.
As opções específicas para gravação de gerações em arquivo ou imagens estão inativos.

## Autores
Lucas Costa
Arthur Pinheiro
