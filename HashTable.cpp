/*
 * HashTable.cpp
 * Jan Konings (jkonin01)
 * Jude Vamenta (jvamen01)
 * 12/10/2024
 *
 * CS 15 Final Project: Gerp
 *
 * Implenets the HashTable class and takes care of load factor and makes sure 
 * the hastable used in the gerp program operates safely and reliably in order
 * for the gerp program to be as functional as possible.
 *
 */


#include "HashTable.h"
#include <iostream>


/*
 * name:      HashTable
 * purpose:   Constructor that initializes a HashTable with a default size 
 *            of 1000 and an empty table. Sets the number of elements to 0.
 * arguments: none
 * returns:   none
 * effects:   Creates a table of size 1000 and initializes the number of 
 *            elements to 0.
 */
HashTable::HashTable() {
    TableSize = 1000;
    table.resize(TableSize); 
    numElements = 0;
}


/*
 * name:      checkLoad
 * purpose:   Checks if the load factor of the hash table exceeds the threshold 
 *            of 0.7, indicating that rehashing is required.
 * arguments: none
 * returns:   boolean value: true if load factor > 0.7, false otherwise.
 * effects:   none
 */
bool HashTable::checkLoad() {
    float loadFactor = float(numElements) / float(TableSize);
    // std::cout << (loadFactor) << std::endl;
    return(loadFactor > 0.7);
}


/*
 * name:      reHash
 * purpose:   Doubles the table size and rehashes all existing elements into 
 *            the new table to maintain efficient lookup performance.
 * arguments: none
 * returns:   none
 * effects:   Resizes the table, rehashes all existing elements, and updates 
 *            the table size.
 */
void HashTable::reHash() {
    std::vector<std::vector<WordData>> oldTable = table;
    table.clear(); // Get rid of everything
    TableSize *= 2; // double table size
    table.resize(TableSize); //resize the vector to accomodate the space
    
    for (auto &B : oldTable) { //check every bucket for an entry
        for (WordData &D : B) { // for every entry, rehash into new table
            int newIndex = hash(D.word);
            table.at(newIndex).push_back(D);
        }
    }
}


/*
 * name:      hash
 * purpose:   Calculates a hash value for a given string key and returns the 
 *            corresponding index in the table.
 * arguments: a string key to be hashed.
 * returns:   an integer index representing the location in the table.
 * effects:   none
 */
int HashTable::hash(std::string key) {
    std::size_t index = hashFunc(key) % TableSize; // get index from hashfunc

    return (int)index; // return index as int
}



/*
 * name:      getData
 * purpose:   Retrieves the data associated with the given key from the 
 *            hash table, if it exists.
 * arguments: a string key to search for in the table.
 * returns:   a pointer to a WordData struct if the key exists, or nullptr 
 *            if not found.
 * effects:   none
 */
HashTable::WordData *HashTable::getData(std::string key) {
    int index = hash(key);

    for (WordData &D : table.at(index)) { // Go through possible collisions
        if (D.word == key) { 
            return &D;  // if data found return pointer
        }
    }

    return nullptr; // else retrun null
}


/*
 * name:      insert
 * purpose:   Inserts a new key-value pair (word with file and line numbers) 
 *            into the hash table, rehashing if the load factor exceeds 0.7.
 * arguments: an integer FileNum (file number), an integer LineNum (line 
 *            number), and a string key (the word to be inserted).
 * returns:   none
 * effects:   Adds a new entry to the hash table, or updates an existing entry 
 *            with new file and line number data. Rehashes the table if needed.
 */
void HashTable::insert(int FileNum, int LineNum, std::string key) {
    int index = hash(key);

    Dub newDub;     // make coordinate pair for the current location of word
    newDub.file = FileNum;
    newDub.lineNum = LineNum;

    // Check to see if there is anything already at the index for collisions
    for (WordData &D : table.at(index)) {
        if (D.word == key) {
            D.locations.push_back(newDub);
            return;
        }
    }

    // If there is not already a struct for the word make WordData struct
    WordData newEntry;
    newEntry.word = key;
    
    // add coordinate pair to wordData struct vector
    newEntry.locations.push_back(newDub);
    
    if (checkLoad()) {
        reHash();           // if load capacity is reach, we must rehash
        index = hash(key);
    }

    table.at(index).push_back(newEntry);
    numElements++; // increase element count
}


