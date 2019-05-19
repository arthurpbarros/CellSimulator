#include "../include/history.h"
void History::add(list &gen){
	backup.push_back(gen);
}
bool History::find(list &gen){
	size_t equal;
	for(list el: backup){
		if(el.size() == gen.size()){
			equal = 0;
			for(Cell a : el){
				for(Cell b : gen){
					if(a == b){
						equal++;
					}
				}
			}
			if(equal == el.size()){
				return true;
			}
		}
	}
	return false;
}