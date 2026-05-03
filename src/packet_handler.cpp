#include "packet_handler.hpp"
#include <iostream>

int find_ip(const std::vector<ip_r>* _blacklist_ptr, uint32_t addr){

	const auto &blacklist = *_blacklist_ptr;

	for(int i = 0; i < _blacklist_ptr->size(); i++){

		if((addr & blacklist[i].big_e_mask) == blacklist[i].big_e_net_ip){

			return 1;
		}
	}

	return 0;
}

std::string find_proto(int proto){

	switch(proto){

		case 1: return std::format("{:<4}", "ICMP");
		case 6: return std::format("{:<4}", "TCP");
		case 17: return std::format("{:<4}", "UDP");
		case 2: return std::format("{:<4}", "IGMP");
		case 132: return std::format("{:<4}", "SCTP");
		case 47: return std::format("{:<4}", "GRE");
		default: return std::format("{:<4}", "N/A");
	}
}

void pck_handler(u_char* args, const struct pcap_pkthdr* pkthdr, const u_char* packet){

	struct Context* ctx = reinterpret_cast<Context*>(args);
	struct ethhdr* eth = nullptr;

	//if ethernet frame
	if(ctx->link_type == DLT_EN10MB){

		eth = (struct ethhdr*)packet;
	
		//checking for vlan to add propper offset
		if(ntohs(eth->h_proto) == ETH_P_8021Q){

			std::cout << "ARP PACKET" << std::endl;
			ctx->header_offset = 18;
		}
	}

	struct iphdr* ip = (struct iphdr*)(packet + ctx->header_offset);

	std::stringstream log_mesg;

	std::string protocol = find_proto((int)ip->protocol);

	if(find_ip(ctx->blacklist_ptr, ip->saddr)){

		char s_ip_str[INET_ADDRSTRLEN] = {0};
		char d_ip_str[INET_ADDRSTRLEN] = {0};

		//parse it to human readable format
		inet_ntop(AF_INET, &(ip->saddr), s_ip_str, INET_ADDRSTRLEN);
		inet_ntop(AF_INET, &(ip->daddr), d_ip_str, INET_ADDRSTRLEN);

		char src[32];
		char dst[32];

		snprintf(src, sizeof(src), "%-15s", s_ip_str);
		snprintf(dst, sizeof(dst), "%-15s", d_ip_str);

		if(eth != nullptr){

			switch(ntohs(eth->h_proto)){

				case ETH_P_IP:
					log_mesg << "[ALERT] " + Logger::timenow() << " " << ctx->interface << " BLACKLISTED SRC: "
						<< src << " DST: " << dst << " PROTO: " << protocol << "\n";
					break;
				
				case ETH_P_ARP:

					break;

				case ETH_P_8021Q:
					
					break;

			}
		}
		else{
			log_mesg << "[ALERT] " + Logger::timenow() << " " << ctx->interface << " BLACKLISTED SRC: "
				<< src << " DST: " << dst << " PROTO: " << protocol << " TUNNELED\n";

		}
	}
	std::cout << log_mesg.str();
}
