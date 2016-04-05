#ifndef CONN_H
#define CONN_H
#include "main.h"
#include "tool.h"


using namespace std;
class conn {
public:
    conn();
    conn(const conn& orig);
    virtual ~conn();
    
    string lIp;
    string rIp;
    uint lPort;
    uint rPort;
    string sockInode;
    ulong network;
private:

};

#endif /* CONN_H */

