#include "cap.h"

cap::cap() {
}

cap::cap(const cap& orig) {
}

cap::~cap() {
}


string cap::init(string devStr)
{
    const char* dev = devStr.c_str();
    char errbuf[PCAP_ERRBUF_SIZE];
    string ret = "ok";
    if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1)
    {
        ret = errbuf;
        return ret;
    }
    
    time_t tim; 
    tim = time(NULL);
    
    if((handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf)) == NULL)
    {
        ret = errbuf;
        return ret;
    }
    
    capDev = dev;
    
    return ret;
}


int cap::addr_ntoa(int i_addr, char* str_addr)
{
    if(str_addr == NULL)
    {
        return -1;
    }
    struct in_addr addr;
    addr.s_addr = i_addr;
    char* tmp = inet_ntoa(addr);
    strcpy(str_addr, tmp);
    return 0;
}

pack cap::getPack()
{
    pcap_pkthdr header;
    const u_char* packet;
    pack p;

    packet = pcap_next(handle, &header);

    if(packet == NULL)
    {
        return p;
    }
    p = this->got_packet(&header, packet);
    return p;
}

pack cap::got_packet(const struct pcap_pkthdr* header, const u_char* packet)
{
    const struct sniff_ethernet *ethernet;
    const struct sniff_ip *ip;
    const struct sniff_tcp *tcp;
    
    ethernet = (struct sniff_ethernet*)(packet);
    
    u_int size_ip;
    u_int size_tcp;
    pack p;
    ip = (struct sniff_ip*)(packet + SIZE_ETHERNET);
    if((size_ip = IP_HL(ip)*4) < 20) return p;
    tcp = (struct sniff_tcp*)(packet + SIZE_ETHERNET + size_ip);
    if((size_tcp = TH_OFF(tcp)*4) < 20) return p;
    
    char ip_src[16];
    char ip_dst[16];
    addr_ntoa(ip->ip_src.s_addr, ip_src);
    addr_ntoa(ip->ip_dst.s_addr, ip_dst);
    int sport = ntohs(tcp->th_sport);
    int dport = ntohs(tcp->th_dport);
    
    p.fromIp = ip_src;
    p.destIp = ip_dst;
    p.fromPort = sport;
    p.destPort = dport;
    p.size = header->len;
    return p;
}

pack::pack()
{
    
}
pack::pack(const pack& orig)
{
    this->destIp = orig.destIp;
    this->destPort = orig.destPort;
    this->fromIp = orig.fromIp;
    this->fromPort = orig.fromPort;
    this->size = orig.size;
}

