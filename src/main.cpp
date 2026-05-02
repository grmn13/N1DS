#include <iostream>
#include <pcap/pcap.h>
#include <unordered_set>

#include "parser.hpp"
#include "packet_handler.hpp"
#include "net_manager.hpp"

#define INF_PCAP_LOOP -1

int main(int argc, char* argv[]){

	//command line args
	ArgParser clargs(argc, argv);
	if(clargs.flush_err()){

		return 1;
	}

	NetManager nm(clargs);
	nm.init();

	//black listed ip addresses
	std::unordered_set<uint32_t> blacklist;

	int validate_bl = parse_blacklist(clargs.flags.blist_name.second, blacklist);

	if(validate_bl == 1){

		return 1;
	}
	//pcap_loop(nm.session, INF_PCAP_LOOP .... )
	//i need to write the callback func and the txt parser to pass both things to pcap_loop();

	return 0;
}
