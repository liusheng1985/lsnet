#ifndef ANALYZER_H
#define ANALYZER_H
#include "main.h"
#include "file.h"
#include "proc.h"
#include "cap.h"
#include "tool.h"

using namespace std;

class analyzer {
public:
    analyzer();
    analyzer(const analyzer& orig);
    virtual ~analyzer();
    
    vector<conn> conns;
    list<proc> procs;
    
    int beginSnap(string dev, int interval);
    list<proc> analyze();
    
private:
    int getCurrConns(string fileName);
    int getProcs();
    int addConnToPorc(conn c);
    int addPackToProc(pack pk);
    int doCap(string dev, int interval);
};

#endif /* ANALYZER_H */

