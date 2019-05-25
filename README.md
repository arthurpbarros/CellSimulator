# CellSimulator
<p>Simulador para representar um comportamento celular.</p>

## Compilação e Execução
sh run.sh

## Tratamento
<p>O programa trata erros de entrada, isto é, valores inválidos para as flags existentes e o próprio tratamento das flags</p>

## Arquivo de Configuração
<p>Um arquivo de configuração válido possui os seguintes campos:</p>

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
* h: número de linhas da matriz de células
* w: número de colunas da matriz de células
* b: número de células necessárias para uma célula morta tornar-se viva
* s1: número de 
* s2: número de
* c: caracter que representa a célula viva na matriz, por exemplo o '$'. As células com qualquer outro caracter são consideradas * mortas. OBS: Não é preciso indicar todas as mortas.

## Limitações
<p>O programa possui uma classe main pouco modularizada, isto é, possui muitos métodos.</p>
<p>As opções específicas para gravação de gerações em arquivo ou imagens estão inativos.</p>

## Autores
- Lucas Costa
- Arthur Pinheiro

## Link do Repositório
- https://github.com/arthurpbarros/CellSimulator/.git
