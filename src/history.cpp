#include "../include/history.h"
void History::add(list gen){
	backup.push_back(gen);
}
bool History::find(list &gen){
	size_t i,j;
	size_t equal;
	for(i = 0; i < backup.size();i++){
		list el = backup.at(i);
		if(el.size() == gen.size()){
			equal = 0;
			for(j = 0; j < el.size();j++){
				if(el.at(j)==gen.at(j)){ 
					equal++;
				}
			}
			if(equal == el.size()){
				return true;
			}
		}
	}
	return false;
}