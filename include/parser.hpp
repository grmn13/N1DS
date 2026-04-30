#pragma once
#include <string>
#include <cstring>
#include <unordered_set>
#include <fstream>
#include <vector>
#include <stack>
#include <utility>
#include <arpa/inet.h>

#define FLAG_IF "-i"

class TxtParser{


};

class ArgParser{

	public:

	struct {

		std::pair<bool, std::string> interface;
	} flags;

	std::stack<std::string> errors;

	ArgParser(int argc, char* argv[]);

	//checks if the flag comes with an argument
	int verifyFlag(int _idx, int _arc, std::string errmesg);

};
