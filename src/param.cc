#include "param.h"
using namespace std;

param::param()
{
    valueFlag = 0;
    formatFlag = 0;
    intervalFlag = 0;
    countFlag = 0;
    devFlag = 0;
    topnFlag = 0;

    cmd = "";    
    fmt = "";
    dev = "";
    topn = 0;
    count = 0;
    interval = 0;
}
param::param(const param& orig)
{ 
    this->valueFlag = orig.valueFlag;
    this->formatFlag = orig.formatFlag;
    this->intervalFlag = orig.intervalFlag;
    this->countFlag = orig.countFlag;
    this->devFlag = orig.devFlag;
    this->topnFlag = orig.topnFlag;

    this->fmt      = orig.fmt;
    this->dev      = orig.dev;
    this->interval = orig.interval;
    this->cmd      = orig.cmd;
    this->count    = orig.count;
    this->topn     = orig.topn;
}


void inline param::setParamFlag(int flag)
{
    this->formatFlag   = flag & LSNET_PARAM_FORMAT_FLAG;
    this->intervalFlag = flag & LSNET_PARAM_INTERV_FLAG;
    this->countFlag    = flag & LSNET_PARAM_COUNT_FLAG;
    this->devFlag      = flag & LSNET_PARAM_DEV_FLAG;
    this->topnFlag     = flag & LSNET_PARAM_TOPN_FLAG;
}

/*
 *  
 * */
char* param::getParamName(char* pArg)
{
    if(pArg[0] == '-')
    {
        pArg ++;
    }
    switch(*pArg)
    {
        case 'f': 
            setParamFlag(LSNET_PARAM_FORMAT_FLAG);
            break;
        case 'i': 
            setParamFlag(LSNET_PARAM_INTERV_FLAG);
            break;
        case 'c': 
            setParamFlag(LSNET_PARAM_COUNT_FLAG);
            break;
        case 'd': 
            setParamFlag(LSNET_PARAM_DEV_FLAG);
            break;
        case 't': 
            setParamFlag(LSNET_PARAM_TOPN_FLAG);
            break;
        default:
            cout << "invalid parameter: " << *pArg << endl;
            printUsage();
            exit(1);
    }
    pArg++;
    return pArg;
}

void param::setFormat(char* value)
{
    printer pnt;
    if(value == NULL || strlen(value) == 0)
    {
        cout << "format string is null." << endl;
        printUsage();
        exit(1);
    }
    for(int i=0; i<strlen(value); i++)
    {
        if(value[i] != LSNET_PRINT_PID &&
           value[i] != LSNET_PRINT_CMDLINE &&   
           value[i] != LSNET_PRINT_BYTE &&   
           value[i] != LSNET_PRINT_KBYTE &&   
           value[i] != LSNET_PRINT_MBYTE &&   
           value[i] != LSNET_PRINT_BPS &&   
           value[i] != LSNET_PRINT_BPS &&   
           value[i] != LSNET_PRINT_KPS &&   
           value[i] != LSNET_PRINT_MPS 
        )
        {
            cout << "invalid format flag " << value[i] << endl;
            printUsage();
            exit(1);
        }
    }
    fmt = value;
}

void param::setInterval(char* value)
{
    tool t;
    if(t.isIntStr(value))
    {
        interval = t.intToInt(value);
    }
    else
    {
        cout << "invalid interval: " << value << endl;
        printUsage();
        exit(1);
    }
}
void param::setCount(char* value)
{
    tool t;
    if(t.isIntStr(value))
    {
        count = t.intToInt(value);
    }
    else
    {
        cout << "invalid count: " << value << endl;
        printUsage();
        exit(1);
    }
}
void param::setTopn(char* value)
{
    tool t;
    if(t.isIntStr(value))
    {
        topn = t.intToInt(value);
    }
    else
    {
        cout << "invalid topn: " << value << endl;
        printUsage();
        exit(1);
    }
}
void param::setDev(char* value)
{
    if(value == NULL || strlen(value) == 0)
    {
        cout << "dev name is null." << endl;
        printUsage();
        exit(1);
    }
    dev = value;
}

void param::parseValue(char* value)
{
    if(value == NULL || strlen(value) == 0)
    {
        return;
    }
    else if(formatFlag)
    {
        setFormat(value);
    }
    else if(intervalFlag)
    {
        setInterval(value);
    }
    else if(countFlag)
    {
        setCount(value);
    }
    else if(devFlag)
    {
        setDev(value);
    }
    else if(topnFlag)
    {
        setTopn(value);
    }
}

char* param::parseParam(char* pArg)
{
    if(pArg[0] == '-') // a arg name
    {
        valueFlag = 0;
        pArg = getParamName(pArg);
        valueFlag = 1;
        if(strlen(pArg) > 0)
        {
            parseValue(pArg);
        }
        
    }
    else
    { // a arg value
        if(valueFlag)
        {
            parseValue(pArg);
            valueFlag = 0;
        }
        else
        {
            printUsage();
            exit(1);
        }
    }
    return pArg;
}

/*
 *  analyze command line args
 * */
int param::init(int argc, char** argv)
{
    cmd = *argv;
    argv++;
    for(int i=1; i<argc; i++)
    {
        parseParam(*(argv++));
    }
    
    return 0;           
}

int param::printUsage()
{
    cout << endl;
    cout << "Usage: " << endl;
    cout << "    " << cmd << " -i interval -c count -t topn -f format -d dev" << endl;
    cout << endl;
    cout << "    interval:" << endl;
    cout << "        Seconds between two reports." << endl;
    cout << "        It may take long time if no packat occur." << endl;
    cout << "        " << endl;
    cout << "    count:" << endl;
    cout << "        Number of reports to be generate." << endl;
    cout << "        " << endl;
    cout << "    topn:" << endl;
    cout << "        Display top n processes." << endl;
    cout << "        " << endl;
    cout << "    dev:" << endl;
    cout << "        Ethernet interface name. like 'eth0', 'enp0s8'" << endl;
    cout << "        " << endl;
    cout << "    format:" << endl;
    cout << "        Control columns of output." << endl;
    cout << "        p: process id" << endl;
    cout << "        c: command line" << endl;
    cout << "        b: total bytes in interval" << endl;
    cout << "        k: kb in interval" << endl;
    cout << "        m: mb in interval" << endl;
    cout << "        B: bytes/sec" << endl;
    cout << "        K: kb/sec" << endl;
    cout << "        M: mb/sec" << endl;
    cout << "        " << endl;
    cout << "    EXAMPLE:" << endl;
    cout << "        " << cmd << " -d eth0 -i 5 -c 10 -t 10 -f pcmM" << endl;
    cout << "        " << cmd << " -deth0 -i5 -c10 -t10 -fpcbB" << endl;
    cout << "        " << endl;
    return 0;
}

int param::checkParam()
{
    if(
        fmt.empty() ||
        interval <= 0 ||
        count <= 0 ||
        dev.empty() ||
        topn <= 0
    )
    return 0;
    else
    return 1;
}
























