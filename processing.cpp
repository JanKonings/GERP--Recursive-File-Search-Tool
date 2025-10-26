/*
 *  processing.cpp
 *  Jan Konings (jkonin01)
 *  Jude Vamenta (jvamen01)
 *  December 2, 2024
 *
 *  CS 15 Project 4 - Gerp
 *
 *  This files holds the implementation of both the stripping of non-
 *  alphanumeric characters, and the traversal of directories. Utilziing a 
 *  recursive helper, the program prints out the paths taken to std::cout.
 *
 */


#include "processing.h"
#include <cctype>



/*
 * name:      stripNonAlphaNum
 * purpose:   Removes all leading and trailing non-alphanumeric characters from 
 *            a string.
 * arguments: the string to be stripped of non-alphanumeric characters.
 * returns:   A string with all non-alphanumeric characters removed from both 
 *            ends.
 * effects:   None.
 */
string stripNonAlphaNum(string input) {
    int firstIndex = 0; //starting index
    int size = input.size();
    int lastIndex = size - 1; //starting index for reverse traversal

    while ((not isalnum(input[firstIndex])) and (firstIndex < size)) {
        firstIndex++;   //increment index if alnum not found
    }

    if (firstIndex == size) return "";

    while ((not isalnum(input[lastIndex])) and (lastIndex >= 0)) {
        lastIndex--;    //increment index if alnum not found
    }

    //return the substring starting at first alnum and ending at last alnum
    return input.substr(firstIndex, (lastIndex - firstIndex) + 1);    
}



/*
 * name:      traverseDirectory
 * purpose:   Initiates the traversal of a directory tree and prints all file 
 *            paths.
 * arguments: the root directory to be traversed.
 * returns:   None.
 * effects:   Constructs an FSTree object and prints file paths to cout
 */
void traverseDirectory(string directory) {
    // Create tree
    FSTree newTree(directory);
    DirNode *curr = newTree.getRoot();

    traverseRecursive(curr, directory); //call recursive helper
}


/*
 * name:      traverseRecursive
 * purpose:   Recursively traverses a the FStree and prints all file paths.
 * arguments: pointer to the current directory node being traversed and a
 *            reference to a string storing the current directory path.
 * returns:   None.
 * effects:   Modifies the path string as it navigates through subdirectories.
 *            and resizes it appropriately. 
 */
void traverseRecursive(DirNode *curr, string &path) {
    if (not curr) return; // check for nullptr
    int subDirs = curr->numSubDirs();
    int files = curr->numFiles();

    int ogSize = path.size();

    for (int i = 0; i < subDirs; i++) {
        path += "/" + curr->getSubDir(i)->getName(); //update path for next dir
        traverseRecursive(curr->getSubDir(i), path);
        path.resize(ogSize); //reset path to remove other sub dir of curr dir
    }

    for (int i = 0; i < files; i++) {
        cout << path + "/" + curr->getFile(i) << "\n"; //print path
    }
}