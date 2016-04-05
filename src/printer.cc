#include "printer.h"


printer::printer() {
    pidStr = "Process ID";
    cmdStr = "Command line";
    byteStr  = "Bytes";
    kByteStr = "KBytes";
    mByteStr = "MBytes";
    
    bpsStr  = "Bytes/s";
    kpsStr = "KBytes/s";
    mpsStr = "MBytes/s";
    fmt = "";
    interval = 0;
}


printer::printer(const printer& orig) {
}

printer::~printer() {
}

int printer::init(string format, int itv)
{
    fmt = format;
    interval = itv;
}
string printer::checkFmt()
{
    for(int i=0; i<fmt.length(); i++)
    {
        if(fmt[i] != LSNET_PRINT_PID &&
                fmt[i] != LSNET_PRINT_CMDLINE &&
                fmt[i] != LSNET_PRINT_BYTE &&
                fmt[i] != LSNET_PRINT_KBYTE &&
                fmt[i] != LSNET_PRINT_MBYTE &&
                fmt[i] != LSNET_PRINT_BPS &&
                fmt[i] != LSNET_PRINT_KPS &&
                fmt[i] != LSNET_PRINT_MPS
                )
        {
            string ret = "invalid format flag '";
            ret += fmt[i];
            ret += "'.";
            return ret;
        }
    }
    
    return "";
}

/*
 *  table header base on format string (this->fmt)
 * */
string printer::makeHeader()
{
    string header;
    
    // display a column for each char in fmt
    for(int i=0; i<fmt.length(); i++)
    {
        switch(fmt[i])
        {
            case LSNET_PRINT_PID:
                header.append(pidStr);
                for(int n=0; n<LSNET_PRINT_PID_LEN-pidStr.length(); n++) header.append(" ");
                break;
            case LSNET_PRINT_CMDLINE:
                header.append(cmdStr);
                for(int n=0; n<LSNET_PRINT_CMDLINE_LEN-cmdStr.length(); n++) header.append(" ");
                break;
            case LSNET_PRINT_BYTE:
                header.append(byteStr);
                for(int n=0; n<LSNET_PRINT_BYTE_LEN-byteStr.length(); n++) header.append(" ");
                break;
            case LSNET_PRINT_KBYTE:
                header.append(kByteStr);
                for(int n=0; n<LSNET_PRINT_KBYTE_LEN-kByteStr.length(); n++) header.append(" ");
                break;
            case LSNET_PRINT_MBYTE:
                header.append(mByteStr);
                for(int n=0; n<LSNET_PRINT_MBYTE_LEN-mByteStr.length(); n++) header.append(" ");
                break;
            case LSNET_PRINT_BPS:
                header.append(bpsStr);
                for(int n=0; n<LSNET_PRINT_BPS-bpsStr.length(); n++) header.append(" ");
                break;
            case LSNET_PRINT_KPS:
                header.append(kpsStr);
                for(int n=0; n<LSNET_PRINT_KPS-kpsStr.length(); n++) header.append(" ");
                break;
            case LSNET_PRINT_MPS:
                header.append(mpsStr);
                for(int n=0; n<LSNET_PRINT_MPS-mpsStr.length(); n++) header.append(" ");
                break;
            default:
                return header;
        }
    }
    return header;
}


/*
 *  print a process info
 *  "interval" is to calculate workload xxx/sec
 * */
string printer::makeLine(proc p, int interval)
{
    string line;
    tool t;
    string tmp;
    
    for(int i=0; i<fmt.length(); i++)
    {
        switch(fmt[i])
        {
            case LSNET_PRINT_PID:
                tmp = t.itoa(p.pid);
                line.append(tmp);
                for(int n=0; n<LSNET_PRINT_PID_LEN-tmp.length(); n++) line.append(" ");
                break;
            case LSNET_PRINT_CMDLINE:
                tmp = p.cmd;
                if(tmp.length() > LSNET_PRINT_CMDLINE_LEN)
                {
                    tmp = tmp.substr(0, LSNET_PRINT_CMDLINE_LEN-1);
                }
                line.append(tmp);
                for(int n=0; n<LSNET_PRINT_CMDLINE_LEN-tmp.length(); n++) line.append(" ");
                break;
            case LSNET_PRINT_BYTE:
                tmp = t.ltoa(p.getNetwork());
                line.append(tmp);
                for(int n=0; n<LSNET_PRINT_BYTE_LEN-tmp.length(); n++) line.append(" ");
                break;
            case LSNET_PRINT_KBYTE:
                tmp = t.ltoa(p.getNetwork()/1024);
                line.append(tmp);
                for(int n=0; n<LSNET_PRINT_KBYTE_LEN-tmp.length(); n++) line.append(" ");
                break;
            case LSNET_PRINT_MBYTE:
                tmp = t.ltoa(p.getNetwork()/1024/1024);
                line.append(tmp);
                for(int n=0; n<LSNET_PRINT_MBYTE_LEN-tmp.length(); n++) line.append(" ");
                break;
            case LSNET_PRINT_BPS:
                tmp = t.ltoa(p.getNetwork()/interval);
                line.append(tmp);
                for(int n=0; n<LSNET_PRINT_BPS-tmp.length(); n++) line.append(" ");
                break;
            case LSNET_PRINT_KPS:
                tmp = t.ltoa(p.getNetwork()/1024/interval);
                line.append(tmp);
                for(int n=0; n<LSNET_PRINT_KPS-tmp.length(); n++) line.append(" ");
                break;
            case LSNET_PRINT_MPS:
                tmp = t.ltoa(p.getNetwork()/1024/1024/interval);
                line.append(tmp);
                for(int n=0; n<LSNET_PRINT_MPS-tmp.length(); n++) line.append(" ");
                break;
            default:
                return line;
        }
    }
    return line;
}

vector<string> printer::print(list<proc> ps, int topn, int sort)
{
    vector<string> out;
    string err = checkFmt();
    if(!err.empty())
    {
        out.push_back(err);
        return out;
    }
    
    if(sort != 0) ps.sort();
    if(sort <  0) ps.reverse();
    
    out.push_back(makeHeader());
    int n = 1;
    for(list<proc>::iterator i=ps.begin(); i!=ps.end(); i++)
    {
        out.push_back(makeLine(*i, interval));
        if(n++ == topn)
        {
            return out;
        }
    }
    
    return out;
}




