#include "net_manager.hpp"

NetManager::NetManager(const ArgParser &_clargs){

	session = nullptr;

	if(_clargs.flags.interface.first)
		input.if_target = _clargs.flags.interface.second;

}

NetManager::~NetManager(){

	if(session != nullptr)
		pcap_close(session);
}

int NetManager::init(){

	pcap_if_t* alldevs;
	if(pcap_findalldevs(&alldevs, errbuf) == PCAP_ERROR){

		std::cerr << "ERROR: " << errbuf << std::endl;
		std::cerr << "exiting..." << std::endl;

		return 1;
	}

	pcap_if_t* dev = alldevs;

	bool if_exists = false;

	//check if inputted ifce matches a real ifce
	while(dev != nullptr && !if_exists){

		if(dev->name == input.if_target)
			if_exists = true;

		dev = dev->next;
	}

	if(!if_exists){

		std::cerr << "ERR: selected interface does not exists" << std::endl;
	}

	session = pcap_open_live(input.if_target.c_str(), 65535, 1, 1000, errbuf);

	if(session == nullptr){
		
		std::cerr << "ERR: " << errbuf << std::endl;
	}

	return 0;
}
