#ifndef STREAM
#define STREAM
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "cell.h"
///Struct para armazenar informações da geração inicial
struct input
{
    size_t h,w; //!< Dimensões horizontais e vericais
    std::vector<Cell> alives; //!< Vector de células vivas
    size_t born,s1,s2; //! Útil para regras 
};
///Retorna struct com informações da geração inicial
input readFile(const std::string file){
	input inp;
	std::ifstream ifs (file,std::ifstream::in);
	if(!ifs.is_open()){
		std::cerr << "Não foi possível abrir o arquivo\n";
		return inp;
	}
	size_t x,y,born,s1,s2;
	char c_alive;

	std::string aux;
	
	ifs >> x >> y >> born >> s1 >> s2 >> c_alive;
	inp.h = x; inp.w = y;
	inp.born = born; inp.s1 = s1; inp.s2 = s2;
	std::getline(ifs,aux);

	size_t line = 0,i;
	while(!ifs.eof() && line < x){
		std::getline(ifs,aux);
		aux = aux.substr(0,y);
		for(i = 0; i < y;i++){
			if(aux[i] == c_alive){
				inp.alives.push_back(Cell(line,i));
			}
		}
		line++;
	}
	return inp;
}
#endif