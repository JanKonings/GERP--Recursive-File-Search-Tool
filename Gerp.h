#ifndef _GERP_H_
#define _GERP_H_




#include <string>
#include <vector>



class Gerp {
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
/*
 * Gerp.h
 * Jan Konings (jkonin01)
 * Jude Vamenta (jvamen01)
 * 12/10/2024
 * 
 * CS 15 Final Project: Gerp.h
 *
 * Gerp.h defines the Gerp class, which manages the processing of files and 
 * queries within the Gerp program.
 *
 * Includes functions for traversing directories, processing text, and 
 * generating output based on user queries.
 *
 */


#ifndef _GERP_H_
#define _GERP_H_

#include <string>
#include <vector>
#include "FSTree.h"
#include "HashTable.h"
#include <fstream>
#include <sstream>
#include <cctype>
#include <iostream>
#include <utility>
#include <set>


class Gerp {
public:

    Gerp();

    // struct to hold array filepaths and the file Lines
    struct fileData {
        std::string path;
        std::vector<std::string> lines;
    };      

    fileData *getData();
    
    void start(std::string directory, std::string outputFile);
    void startQuery();

private:

    // private helper functions for gerp
    bool traverseDirectory(std::string &directory);
    void traverseRecursive(DirNode *curr, std::string &path, int *fileNum);
    std::string stripNonAlphaNum(std::string &input);
    void findWord(std::string &word, bool i);
    void printToOutput(std::string &input);
    bool collectData(HashTable::WordData *word, bool i, std::string &ogWord);
    bool accuracyCheck(std::string &ogWord, std::string &fullLine);
    void setOutputStream(const std::string &newOutputName);
    bool send();

    // hashtable used to store data 
    HashTable table;
    std::vector<fileData> array;

    // data holders
    std::string outputName;
    std::ofstream outputStream;
    std::string outputStr;
};

#endif
