/*
 *  processing.cpp
 *  Jan Konings (jkonin01)
 *  Jude Vamenta (jvamen01)
 *  December 2, 2024
 *
 *  CS 15 Project 4 - Gerp
 *
 *  This file holds the definitions for the stripping of alphanumeric 
 *  characters, and the traversal of directories. Utilziing a 
 *  recursive helper, the program prints out the paths taken to std::cout.
 *
 */

#ifndef __PROCESSING_H
#define __PROCESSING_H

#include <string>
#include <iostream>
#include "FSTree.h"

using namespace std;

string stripNonAlphaNum(string input);
void traverseDirectory(string directory);
void traverseRecursive(DirNode *curr, string &path); //recursive helper

#endif 