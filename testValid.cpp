#include "valid.h"
#include <iostream>
int main(int argc,char ** argv){
	valid_arguments(argc,argv);
	using std::cout;
	cout << get_maxgen() << "\n";
	cout << is_valid() << "\n";
	return EXIT_SUCCESS;
}