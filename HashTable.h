/*
 * HashTable.h
 * Jan Konings (jkonin01)
 * Jude Vamenta (jvamen01)
 * 12/10/2024
 *
 * CS 15 Final Project: HashTable.h
 *
 * Defines the HashTable class, which is used to store and manage word data 
 * in the gerp program including the locations (files and lines) where each 
 * word appears.
 *
 */


#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_


#include <vector>
#include <string>
#include <functional>



class HashTable {
public:

    HashTable();
    
    void insert(int FileNum, int LineNum, std::string key);

    int hash(std::string key);

    // structs used by the gerp program to store hashed data
    struct Dub {
        int file;
        int lineNum;

        bool operator<(const Dub& other) const {
        if (file == other.file) {
            return lineNum < other.lineNum;
        }
            return file < other.file;
        }
    };

    struct WordData {
        std::string word;
        std::vector<Dub> locations;
    };

    WordData *getData(std::string key);

private:

    // load factor functions
    void reHash();
    bool checkLoad();

    // count holders
    int TableSize;
    int numElements;

    // data structures to store hastable
    std::hash<std::string> hashFunc;
    std::vector<std::vector<WordData>> table;
};

#endif