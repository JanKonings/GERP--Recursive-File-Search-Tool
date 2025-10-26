/*
 *  main.cpp
 *  Jan Konings (jkonin01)
 *  
 *  November 18, 2024
 *
 *  
 *
 *  
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include "Gerp.h"

using namespace std;


int main(int argc, char *argv[]) {
    if (argc != 3) { 
        cerr << "Usage: ./gerp inputDirectory outputFile" << endl;
        return EXIT_FAILURE;
    }

    Gerp gerp;
    gerp.start(argv[1], argv[2]);

   //start gerp and feed in directory 
}
