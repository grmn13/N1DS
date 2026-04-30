#include <iostream>
#include <pcap/pcap.h>

#include "parser.hpp"
#include "packet_handler.hpp"
#include "net_manager.hpp"

#define INF_PCAP_LOOP -1

int main(int argc, char* argv[]){

	//command line args
	ArgParser clargs(argc, argv);

	if(!clargs.errors.empty()){

		while(!clargs.errors.empty()){

			std::cerr << clargs.errors.top() << std::endl;
			clargs.errors.pop();
		}

		return 1;
	}

	NetManager nm(clargs);
	nm.init();

	//pcap_loop(nm.session, INF_PCAP_LOOP .... )
	//i need to write the callback func and the txt parser to pass both things to pcap_loop();

	return 0;
}
