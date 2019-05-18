#ifndef LIFE_H
#define LIFE_H
#include "cell.h"
#include "history.h"
using list = std::vector<Cell>;
class Life{
private:
	size_t m,n;
	size_t max_gen;
public:
	list alives;
	size_t **cells;
	//Construtor da classe Life, com dimensões verticais e horizontais
	Life(size_t _m,size_t _n);
	//Destrutor da classe Life
	~Life();
	//Adiciona célula viva a Geração atual.
	void add(Cell &c);
	//Atualiza ...
	void update();
	//Imprime na saída padrão a matriz com células vivas e mortas.
	void print();
	//Verifica se a célula é válida, ou seja, é viva e está dentro dos limites da matriz;
	bool valid(Cell &c);
	//Verifica se a simulação terminou
	bool gameOver(History &h);
	//Verifica se a geração é extinta
	bool is_extinct();
	//Verifica se a geração é estável
	bool is_stable(History &h);
};
#endif