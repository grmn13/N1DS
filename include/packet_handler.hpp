#include <pcap.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <unordered_set>
#include <fstream>
#include <sstream>

#include "parser.hpp"

struct Context{

	std::vector<ip_r>* blacklist_ptr;
	std::ofstream* logf;
	std::string interface;
	int link_type;
	int header_offset;
};

void pck_handler(u_char* args, const struct pcap_pkthdr* pkthdr, const u_char* packet);

