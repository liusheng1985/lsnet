#ifndef PRINTER_H
#define PRINTER_H
#include "main.h"
#include "tool.h"
#include "proc.h"
#include "conn.h"

using namespace std;


#define LSNET_PRINT_PID_LEN            15
#define LSNET_PRINT_CMDLINE_LEN        30
#define LSNET_PRINT_BYTE_LEN           20
#define LSNET_PRINT_KBYTE_LEN          20
#define LSNET_PRINT_MBYTE_LEN          20
#define LSNET_PRINT_BYTE_PER_SEC_LEN   20
#define LSNET_PRINT_KBYTE_PER_PSEC_LEN 20
#define LSNET_PRINT_MBYTE_PER_PSEC_LEN 20
 

#define LSNET_PRINT_PID            'p'
#define LSNET_PRINT_CMDLINE        'c'
#define LSNET_PRINT_BYTE           'b'
#define LSNET_PRINT_KBYTE          'k'
#define LSNET_PRINT_MBYTE          'm'
#define LSNET_PRINT_BPS            'B'
#define LSNET_PRINT_KPS            'K'
#define LSNET_PRINT_MPS            'M'




class printer {
public:
    
    string fmt;
    int interval;
    
    // table headers
    string pidStr;
    string cmdStr;
    string byteStr;
    string kByteStr;
    string mByteStr;
    string bpsStr;
    string kpsStr;
    string mpsStr;
    
    
    printer();
    printer(const printer& orig);
    virtual ~printer();
    
    /*
     set attributes first
    * */
    int init(string format, int itv);
    /*
     topn       print top n processes
 
     sort = 0   do not sort
     sort < 0   sort desc
     sort > 0   sort asc
     */
    vector<string> print(list<proc> procs, int topn, int sort);
    
private:
    string makeHeader();
    string checkFmt();
    string makeLine(proc p, int interval);
};

#endif /* PRINTER_H */

