

#include "analyzer.h"

analyzer::analyzer() {
}

analyzer::analyzer(const analyzer& orig) {
}

analyzer::~analyzer() {
}



int analyzer::getCurrConns(string fileName)
{
    textfile tcpfile = textfile(fileName);
    tcpfile.readInVector();
    vector< vector<string> > rows;
    tcpfile.toRowCols(rows);
    tool t;
    int ilip   = 0;
    int ilport = 0;
    int irip   = 0;
    int irport = 0;
    vector<string> tmp;
    conn c;
    for(vector< vector<string> >::iterator i = rows.begin(); i != rows.end(); i++)
    {
        if(i->at(1) == "local_address") continue;
        tmp = t.split(i->at(1), ":");
        ilip = t.hexToInt(tmp.at(0));
        ilport = t.hexToInt(tmp.at(1));
        tmp = t.split(i->at(2), ":");
        irip = t.hexToInt(tmp.at(0));
        irport = t.hexToInt(tmp.at(1));
        
        c.lIp = t.strIp(ilip);
        c.lPort = ilport;
        c.rIp = t.strIp(irip);
        c.rPort = irport;
        c.network = 0;
        c.sockInode = i->at(9);
        conns.push_back(c);
    }
    
    
    return 0;
}

int analyzer::addConnToPorc(conn c)
{
    proc p;
    pid_t pid = 0;
    string procDir = "/proc/";
    string processDir;
    string cmdFile;
    tool t;
    
    pid = t.findProcBySocketInode(c.sockInode);
    if(pid == 0)
    {
        //cout << "socketInode " << c.sockInode << " pid " << pid << endl;
        //abort();
        return 0;
    }
    processDir = procDir + t.itoa(pid) + "/";
    cmdFile = processDir + "cmdline";
    textfile f(cmdFile);
    f.readInVector();
    p.cmd = f.datav.at(0);
    p.pid = pid;
    
    int exists = 0;
    for(list<proc>::iterator i=procs.begin(); i!=procs.end(); i++)
    {
        if(i->pid == p.pid)
        {
            i->conns.push_back(c);
            exists = 1;
            break;
        }
    }
    if(!exists)
    {
        p.conns.push_back(c);
        procs.push_back(p);
    }
    return 0;
}

int analyzer::addPackToProc(pack pk)
{
    for(list<proc>::iterator i = procs.begin(); i!=procs.end(); i++)
    {
        for(vector<conn>::iterator j = i->conns.begin(); j!=i->conns.end(); j++)
        {
            if(
                (
                    j->lIp == pk.fromIp && 
                    j->lPort == pk.fromPort &&
                    j->rIp == pk.destIp &&
                    j->rPort == pk.destPort
                )
                ||
                (
                    j->rIp == pk.fromIp && 
                    j->rPort == pk.fromPort &&
                    j->lIp == pk.destIp &&
                    j->lPort == pk.destPort
                )
            )
            {
                j->network += pk.size;
                break;
            }
        }
    }
    return 0;
}

int analyzer::getProcs()
{
    
    tool t;
    for(vector<conn>::iterator c=conns.begin(); c!=conns.end(); c++)
    {
        this->addConnToPorc(*c);
    }
    return 0;
}

int analyzer::doCap(string dev, int interval)
{
    time_t tim = 0, tim2 = 0; 
    time(&tim);
    cap pcap;
    pack pk;
    list<pack> pks;
    string errbuf = pcap.init(dev);
    if(errbuf.compare("ok") != 0)
    {
        cout << errbuf << endl;
        exit(1);
    }

    for(int intv = 0; intv <= interval;)
    {
        time(&tim2);
        intv = tim2 - tim;
        if(intv >= interval) 
            break;
        pk = pcap.getPack();
        //this->addPackToProc(pk);
        pks.push_back(pk);
	    time(&tim2);
    }
    //long cnt = 0;
    //long max = 0;
    for(list<pack>::iterator i=pks.begin(); i!=pks.end(); i++)
    {
        this->addPackToProc(*i);
        //max = i->size > max ? i->size : max;
        //cnt++;
        //if(i->fromIp.compare("192.168.1.1") == 0) printf("%d ", i->size);
    }
    //cout << ">>>>>>>>>>>>>> "<< cnt << " " << max << " <<<<<<<<<<<<<<<" << endl;
    return 0;
}

int analyzer::beginSnap(string dev, int interval)
{
    this->conns.clear();
    this->procs.clear();
    this->getCurrConns("/proc/net/tcp");
    this->getCurrConns("/proc/net/udp");
    this->getProcs();
    this->doCap(dev, interval);
    
    return 0;
}



list<proc> analyzer::analyze()
{
    
    
    return procs;
}

