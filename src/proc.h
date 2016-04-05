#ifndef PROC_H
#define PROC_H
#include "main.h"
#include "conn.h"
#include "tool.h"
using namespace std;
class proc {
public:
    proc();
    proc(const proc& orig);
    virtual ~proc();
    
    pid_t pid;
    string cmd;
    vector<conn> conns;
    
    ulong getNetwork();
    
    bool operator == (const proc& p); 
    bool operator != (const proc& p);
    bool operator < (const proc& p);
    bool operator <= (const proc& p);
    bool operator > (const proc& p);
    bool operator >= (const proc& p);
    
private:

};

#endif /* PROC_H */

