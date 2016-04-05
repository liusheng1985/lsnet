#include "proc.h"

proc::proc() {
}

proc::proc(const proc& orig) {
    this->cmd = orig.cmd;
    this->pid = orig.pid;
    this->conns = orig.conns;
}

proc::~proc() {
}


bool proc::operator == (const proc& p)
{
    ulong sum = 0;
    vector<conn> cs = p.conns;
    for(vector<conn>::iterator i=cs.begin(); i!=cs.end(); i++)
    {
        sum += i->network;
    }
    return this->getNetwork() == sum;
}
bool proc::operator != (const proc& p)
{
    ulong sum = 0;
    vector<conn> cs = p.conns;
    for(vector<conn>::iterator i=cs.begin(); i!=cs.end(); i++)
    {
        sum += i->network;
    }
    return this->getNetwork() != sum;
}
bool proc::operator < (const proc& p)
{
    ulong sum = 0;
    vector<conn> cs = p.conns;
    for(vector<conn>::iterator i=cs.begin(); i!=cs.end(); i++)
    {
        sum += i->network;
    }
    return this->getNetwork() < sum;
}
bool proc::operator <= (const proc& p)
{
    ulong sum = 0;
    vector<conn> cs = p.conns;
    for(vector<conn>::iterator i=cs.begin(); i!=cs.end(); i++)
    {
        sum += i->network;
    }
    return this->getNetwork() <= sum;
}
bool proc::operator > (const proc& p)
{
    ulong sum = 0;
    vector<conn> cs = p.conns;
    for(vector<conn>::iterator i=cs.begin(); i!=cs.end(); i++)
    {
        sum += i->network;
    }
    return this->getNetwork() > sum;
}
bool proc::operator >= (const proc& p)
{
    ulong sum = 0;
    vector<conn> cs = p.conns;
    for(vector<conn>::iterator i=cs.begin(); i!=cs.end(); i++)
    {
        sum += i->network;
    }
    return this->getNetwork() >= sum;
}

ulong proc::getNetwork()
{
    ulong sum = 0;
    for(vector<conn>::iterator it = conns.begin(); it != conns.end(); it++)
    {
        sum += it->network;
    }
    return sum;
}


