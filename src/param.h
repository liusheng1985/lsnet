#include "main.h"
#include "printer.h"
using namespace std;

#define LSNET_PARAM_FORMAT_FLAG  1
#define LSNET_PARAM_INTERV_FLAG  2
#define LSNET_PARAM_COUNT_FLAG   4
#define LSNET_PARAM_TOPN_FLAG    8
#define LSNET_PARAM_DEV_FLAG    16

class param
{
    public:
    param();
    param(const param& orig);

    string cmd;    
    string fmt;
    string dev;
    int topn;
    int count;
    int interval;

    int init(int argc, char** argv);
    int checkParam();
    int printUsage();

    private:

    // parse command parameter
    int valueFlag;
    int formatFlag;
    int intervalFlag;
    int countFlag;
    int devFlag;
    int topnFlag;
    char* getParamName(char* paramName);
    void setParamFlag(int flag);
    void parseValue(char* value);
    char* parseParam(char* param);
    

    void setFormat(char* value);
    void setInterval(char* value);
    void setCount(char* value);
    void setDev(char* value);
    void setTopn(char* value);


};

