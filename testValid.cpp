#include "valid.h"
#include <iostream>
int main(int argc,char ** argv){
	valid_arguments(argc,argv);
	using std::cout;
	using std::endl;
	cout << get_maxgen() << "\n";
	cout << is_valid() << "\n";
	cout << BLUE.channel[2] << "\n";
	return EXIT_SUCCESS;
}