#include "tool.h"

tool::tool() {
}

tool::tool(const tool& orig) {
}

tool::~tool() {
}

vector<string> tool::split(string s, string part)
{
    vector<string> ret;
    int slen = s.length();
    int plen = part.length();
    int i = 0;
    int j = 0;
    int cnt = 0;
    do{
        if(s.substr(i, plen) == part)
        {
            if(cnt > 0)
            {
                ret.push_back(s.substr(j, cnt));
                cnt = 0;
                j = i + plen;
            }
            else
            {
                j = i+plen;
            }
            i += plen;
        }
        else
        {
            cnt++;
            i++;
        }
    } while(i < slen);
    if(cnt > 0)
    {
        ret.push_back(s.substr(j, cnt));
    }
    
    
    return ret;
}

int tool::hexToInt(string hex)
{
    return (int)strtol(hex.c_str(), NULL, 16);
}

int tool::intToInt(string in)
{
    return (int)strtol(in.c_str(), NULL, 10);
}

int tool::isIntStr(string str)
{
    int len = str.length();
    for(int i=0; i<len; i++)
    {
        if(str[i] < 48 || str[i] > 57) return 0;
    }
    return 1;
}


string tool::strIp(int ip)
{
    struct in_addr addr;
    addr.s_addr = ip;
    return inet_ntoa(addr);
}

string tool::itoa(int n)
{
    char buf[20];
    memset(buf, '\0', 20);
    sprintf(buf, "%d", n);
    string ret = buf;
    return ret;
}

string tool::ltoa(long n)
{
    char buf[20];
    memset(buf, '\0', 20);
    sprintf(buf, "%d", n);
    string ret = buf;
    return ret;
}

int tool::min(int a, int b)
{
    if(a < b) return a;
    return b;
}

vector<string> tool::readDir(string dirName, int hf)
{
    vector<string> fileNames;
    DIR* dir = NULL;
    struct dirent* drt;


    if((dir = opendir(dirName.c_str())) == NULL) 
    {
        //cout << strerror(errno) << endl;
        return fileNames;
    }
    while((drt = readdir(dir)) != NULL)
    {
        if(strcmp(".", drt->d_name)==0 || strcmp("..", drt->d_name)==0)
            continue;
        if(drt->d_name[0] == '.' && hf != 1)
            continue;
        fileNames.push_back(string(drt->d_name));
    }
    closedir(dir);
}

pid_t tool::findProcBySocketInode(string socketInode)
{
    string strInode;
    strInode.append("[").append(socketInode).append("]");
    string procDir = "/proc";
    
    string fdDir;
    
    string dirName;
    vector<string> dirNames = this->readDir(procDir, 0);
    
    vector<string> fds;
    string fd;
    char buf[100];
    string link;
    int idx;
    
    

    for(vector<string>::iterator i = dirNames.begin(); i!=dirNames.end(); i++)
    {
        dirName = *i;
        if(!this->isIntStr(dirName))
        {
            continue;
        }


        fdDir = procDir + "/" + dirName + "/fd/"; 
        fds = readDir(fdDir, 0);
        for(vector<string>::iterator i = fds.begin(); i!=fds.end(); i++)
        {
            fd = *i;
            memset(buf, '\0', 100);
            readlink( ((string)(fdDir + "/" + fd)).c_str(), buf, 100);
            link = buf;
            idx = link.find(strInode, 0);
            if(idx > 0)
            {
                return this->intToInt(dirName);
            }
        }
    }
    
    return 0;
}


