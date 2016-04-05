#include "main.h"
#include "analyzer.h"
#include "tool.h"
#include "printer.h"
#include "proc.h"
#include "param.h"
using namespace std;


/*
 *  print timestamp before snapshot in "yyyy-mm-dd hh:mi:ss"
 * */
string getTime()
{
    time_t tl;
    struct tm *p;
    time(&tl);
    p=localtime(&tl);
    
    char t[20];
    memset(t, '\0', 20);
    sprintf(t, "%d-%d-%d ",(1900+p->tm_year), (1+p->tm_mon),p->tm_mday);
    string st = t;
    sprintf(t, "%d:%d:%d", p->tm_hour, p->tm_min, p->tm_sec);
    st.append(t);
    return st;
}



int cap(param p)
{
    tool t;
    analyzer a;

    // do a snapshot
    a.beginSnap(p.dev, p.interval);

    // get process info from snapshot
    list<proc> ps = a.procs;

    // print a report 
    printer pnt;
    pnt.init(p.fmt, p.interval);
    // -1 for order by network usage desc
    vector<string> out = pnt.print(ps, p.topn, -1);
    
    cout << endl << getTime() << ":"<< endl;
    for(vector<string>::iterator i=out.begin(); i!=out.end(); i++)
    {
        cout <<*i<< endl;
    }
    cout << endl << endl;

}


/*
 * 
 */
int main(int argc, char** argv) {

    param pm;

    // analyze parameter
    pm.init(argc, argv);    
    if(!pm.checkParam())
    {
        pm.printUsage();
    }

    for(int i=0; i<pm.count; i++)
    {
        cap(pm);    
    }
    return 0;
}




