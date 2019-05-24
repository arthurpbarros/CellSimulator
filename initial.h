#include <iostream>
void print_inital_msg(){
	std::cout << ">>> Running simulation up to " << get_maxgen() << " generations, or until extinction/stability is reached, whichever comes first.\n";
	std::cout << ">>> Processing data, please wait...\n";
}