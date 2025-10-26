#ifndef _FILETABLE_H_
#define _FILETABLE_H_




#include <string>
#include <vector>



class FileTable {
public:

    struct fileData {
        std::string path;
        std::vector<std::string> lines;
    };      

    fileData *getData();
    
    


private:
    


    std::vector<fileData> table;
};

#endif
