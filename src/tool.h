#ifndef TOOL_H
#define TOOL_H
#include "main.h"
using namespace std;
class tool {
public:
    tool();
    tool(const tool& orig);
    virtual ~tool();
    
    string itoa(int n);
    string ltoa(long n);
    int min(int a, int b);
    vector<string> split(string s, string part);
    int hexToInt(string hex);
    int intToInt(string in);
    int isIntStr(string str);
    
    /*
     return filenames exclude . and ..
     set hf = 1   including hidden file
     */
    vector<string> readDir(string dirName, int hf);
    string strIp(int ip);
    
    pid_t findProcBySocketInode(string socketInode);
    
private:

};

#endif /* TOOL_H */

