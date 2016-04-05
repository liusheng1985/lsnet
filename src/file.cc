#include "file.h"
using namespace std;


textfile::textfile()
{
    this->filesep = '/';
    readInVectorFlag = 0;
    readInListFlag = 0;
}

textfile::textfile(string fullName)
{
    this->filesep = '/';
    this->setFullName(fullName);
    
}

int textfile::setFullName(string fullName)
{
    int len = fullName.length();
    int idx = -1;
    int i = 0;
    do{
        idx = fullName.find(this->filesep, i);
        if(idx >= i && idx >= 0)
        {
            i=idx;
            i++;
        }
        else
        {
            idx = i-1;
            break;
        }
    } while(i<len);
    
    this->path = fullName.substr(0, idx+1);
    this->name = fullName.substr(idx+1, len-idx-1);
    
    
    i = 0;
    idx = this->name.find('.', 0);
    this->type = this->name.substr(idx+1, len-idx-1);
    do{
        idx = this->name.find('.', i);
        if(idx >= i && idx >= 0)
        {
            i=idx;
            i++;
        }
        else
        {
            idx = i-1;
            break;
        }
    } while(i<len);
    this->type2 = this->name.substr(idx+1, len-idx-1);
    
    
    return 0;
}


int textfile::readInVector()
{
    if(this->name.empty()) return -1;
    
    FILE* f;
    if((f = fopen((this->path+this->name).c_str(), "r")) == NULL )
    {
        return errno;
    }
    
    char buf[1024];
    while(!feof(f))
    {
        if(fgets(buf, 1024, f) < 0)
        {
            datav.clear();
            return errno;
        }
        datav.push_back(string(buf));
    }
    
    fclose(f);
    this->readInVectorFlag = 1;
    return 0;
}


int textfile::readInList()
{
    if(this->name.empty()) return -1;
    
    FILE* f;
    if((f = fopen((this->path+this->name).c_str(), "r")) == NULL )
    {
        return errno;
    }
    
    char buf[1024];
    while(!feof(f))
    {
        if(fgets(buf, 1024, f) < 0)
        {
            datal.clear();
            return errno;
        }
        datal.push_back(string(buf));
    }
    
    fclose(f);
    this->readInListFlag = 1;
    return 0;
}




int textfile::toRowCols(vector<vector<string> > &rows)
{
    string r;
    vector<string> rv;
    tool t;
    if(readInVectorFlag)
    {
        for(vector<string>::iterator it = datav.begin(); it != datav.end(); it++)
        {
            r = *it;
            rv = t.split(r, " ");
            rows.push_back(rv);
        }
    } 
    else if (readInListFlag)
    {
        for(list<string>::iterator it = datal.begin(); it != datal.end(); it++)
        {
            r = *it;
            rv = t.split(r, " ");
            rows.push_back(rv);
        } 
    }
    
    return 0;
}

