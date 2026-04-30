#include "parser.hpp"

int ArgParser::verifyFlag(int _idx, int _argc, std::string errmesg){

	if(_idx + 1 >= _argc){

		errors.push(errmesg);
		return 1;
	}

	return 0;
}

ArgParser::ArgParser(int argc, char* argv[]){

	int idx = 1;

	while(idx < argc){

		//interface
		if(strcmp(argv[idx], FLAG_IF) == 0){
		
			if(verifyFlag(idx, argc, "option -i requires an argument: \'-i <interface>\'") == 0){

				flags.interface.first = true;
				flags.interface.second = argv[++idx];
			}
		}

		idx += 1;
	}

	if(!errors.empty()){
		return;
	}

	if(!flags.interface.first){

		errors.push("you need to specify an interface: \'-i <interface>\'");
	}

}
