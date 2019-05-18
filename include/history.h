#ifndef HISTORY_H
#define HISTORY_H
#include "cell.h"
using list = std::vector<Cell>; 
class History{
private:
	std::vector<list> backup;
	size_t max_gen;
public:
	History(size_t max): max_gen{max}{};
	//Guarda uma geração no vector para geração posteriores
	void add(list gen);
	//Busca pela geração no vector
	bool find(list &gen);
};
#endif