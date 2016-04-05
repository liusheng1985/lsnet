#ifndef FILE_H
#define FILE_H

#include "main.h"
#include "tool.h"
using namespace std;

class textfile
{
    private:
    

    public:
    vector<string> datav;
    list<string> datal;
    char filesep;
    string path;  // /xxx/yyy/
    string name;  // zzz.tar.gz
    string type;  // tar.gz
    string type2; // gz
    int readInVectorFlag;
    int readInListFlag;

    textfile();
    textfile(string fullName);
    int setFullName(string fullName);

    int isReadVector();
    int isReadList();

    int readInVector();
    int readInList();

    int toRowCols(vector<vector<string> > &rows);

    
    
    
};

#endif /* FILE_H */

