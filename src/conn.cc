#include "conn.h"

conn::conn() {
    lIp = "";
    rIp = "";
    lPort = 0;
    rPort = 0;
    sockInode = "";
    network = 0;
}

conn::conn(const conn& orig) {
    this->lIp = orig.lIp;
    this->lPort = orig.lPort;
    this->network = orig.network;
    this->rIp = orig.rIp;
    this->rPort = orig.rPort;
    this->sockInode = orig.sockInode;
}

conn::~conn() {
}

