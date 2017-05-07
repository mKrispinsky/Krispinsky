// $NAME <mak191@zips.uakron.edu>

#include "machine.hpp"

#include <iostream>
#include <fstream>


int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cerr << "error: vm input-file";
		return 1;
	}

	std::ifstream ifs(argv[1]);
	Machine vm(ifs);
	vm.run();
}
