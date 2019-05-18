#include "../include/life.h"
Life::Life(size_t _m,size_t _n){
	m = _m; n = _n;
	size_t i;
	cells = new size_t*[m];
	for(i = 0;i < m;i++){
		cells[i] = new size_t[n];
	}
}
Life::~Life(){
	size_t i;
	for(i = 0;i < m;i++){
		delete [] cells[i];
	}
}
void Life::print(){
	size_t x,y;
	bool achou;
	for(x = 0; x < m;x++){
		std::cout << "[";
		for(y = 0; y < n;y++){
			achou = false;
			for(auto &a : alives){
				if(a.exists(x,y)){
					achou = true;
					std::cout << "*";
				}
			}
			if(!achou){
				std::cout << " ";
			}
		}
		std::cout << "]\n";
	}
}
void Life::add(Cell &c){
	//Se a célula é viva e é válida, adicione ao vector.
	if(c.getStatus() && valid(c)){
		alives.push_back(c);
	}
}
bool Life::valid(Cell &c){
	return (c.getX() >= 0 && c.getX() < m && c.getY() >= 0 && c.getY() <= n);
}
bool Life::gameOver(History &h){
	return false;
}

bool Life::is_extinct(){
	// size_t i,j;
	
	// size_t alives_will_die = 0;
	// size_t neigh_alive;
	// for(auto &a : alives){
	// 	neigh_alive = 0; alives_will_die = 0;
	// 	for(i = a.getX()-1; i <= a.getX()+1;i++){
	// 		for(j = a.getY()-1; j <= a.getY()+1;j++){
	// 			if(!(i == a.getX() && j == a.getY())){ //Ignora a comparação nas mesmas coordenadas
	// 				if(i >= 0 && i < m && j >= 0 && j < n){
	// 					neigh_alive = (cells[i][j] == 1)? neigh_alive+1 : neigh_alive;
	// 				}
	// 			}
	// 		}
	// 	}
	// 	if(neigh_alive != 2 && neigh_alive != 3){
	// 		alives_will_die++;
	// 	}
	// }

	return false;
}

bool Life::is_stable(History &h){
	return false;
}