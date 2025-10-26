/*
* Gerp.* Jan Konings (jkonin01)
* Jude Vamenta (jvamen01)
* 12/10/2024
* 
* CS 15 Final Project: Gerp
*
* Implements the gerp program which runs takes in a directory name and can 
* return the location of any lines within any files within that directory that
* contain a user inputted query. It is dynamic and you may search with case
* sensitivity activated ro not to cater to your specifc location needs. 
*
*/

#include "Gerp.h"


/*
 * name:      Gerp
 * purpose:   Constructor that initializes the Gerp class.
 * arguments: none
 * returns:   none
 * effects:   none.
 */
Gerp::Gerp() {

}


/*
 * name:      start
 * purpose:   Starts the Gerp program by processing a directory and output file.
 * arguments: the directory path to traverse and the file to output results to.
 * returns:   none
 * effects:   Calls traverseDirectory to process the directory, 
 *            and startQuery to handle user queries.a
 */
void Gerp::start(std::string directory, std::string outputFile) {
    // Go through the entire directory, insert all information
    // into a vector of vectors (strings), and a hash table
    outputName = outputFile;
    if (not send()) return;

    if(traverseDirectory(directory)) startQuery();
    
    return;
}


/*
 * name:      startQuery
 * purpose:   Starts the user query process, allowing searches with optional
              case sensitivity.
 * arguments: none
 * returns:   none
 * effects:   Loops to accept user input for queries, processes the queries, and 
 *            outputs results to the specified output file.
 */
void Gerp::startQuery() {
    std::string raw;
    std::cout << "Query? "; // initial query
    bool caseSen = false; // intialize bool

    while ((std::cin >> raw) and (raw != "@q" and raw != "@quit")) { // q query
        if (raw == "@i" or raw == "@insensitive") {   // Case insensitive   
            std::cin >> raw;
            std::string s = stripNonAlphaNum(raw);
            findWord(s, caseSen);
        } else if (raw == "@f") {
            if (not send()) return;
            outputStr.clear();
            std::cin >> raw;
            outputName = raw;
        } else {
            caseSen = true; // Case sensitive so set flag to true
            std::string s = stripNonAlphaNum(raw);
            findWord(s, caseSen);
        }
        caseSen = false;    
        std::cout << "Query? ";
    }

    if (not send()) return; // if end of loop, thank user
    std::cout << "Goodbye! Thank you and have a nice day.\n"; 
    return;
}


/*
 * name:      printToOutput
 * purpose:   Appends a string to the output.
 * arguments: input - the string to be appended to the output.
 * returns:   none
 * effects:   Modifies the output string by appending the given input.
 */
void Gerp::printToOutput(std::string &input) {
    outputStr += input; //add to output string
}


/*
 * name:      send
 * purpose:   Writes the output to the specified file and returns the success
 * arguments: none
 * returns:   true if file was written to, and false if it cant be written to
 * effects:   overwrites the output file with the new input string
 */
bool Gerp::send() {
    std::ofstream out(outputName); // make output stream for output file

    if (not out.is_open()) {  // check if file is openable/writeable
        std::cerr << "Could not open output file\n";
        return false;
    }

    out << outputStr;   // send output to output file
    out.close();
    return true;
}


/*
 * name:      findWord
 * purpose:   Finds and processes a word in the hash table, outputting results.
 * arguments: word - the word to be searched.
 *            i - flag indicating case sensitivity (true for case-sensitive).
 * returns:   none
 * effects:   Looks up the word in the hash table, and outputs the locations 
 *            where it is found or an error message if not found.
 */
void Gerp::findWord(std::string &word, bool i) {
    std::string lowerWord = "";

    for (char &c : word) {
        lowerWord += tolower(c); // access insensitive word always
    }

    HashTable::WordData *wordD = table.getData(lowerWord);
    
    if (not collectData(wordD, i, word)) { // if word cannot be found
        std::string intermediate = "";
        if (i) {
            // if word doesnt exist, suggest using insensitive
            intermediate = (word + " Not Found. Try with @insensitive or @i.\n");
            printToOutput(intermediate);
        } else {
            // if not foud with case insensitive, doesnt exist 
            intermediate = (word + " Not Found.\n");
            printToOutput(intermediate);
        }
    }
}


/*
 * name:      collectData
 * purpose:   Collects and formats the data related to a found word from the hash table.
 * arguments: word - pointer to the WordData struct for the word to be processed.
 *            i - flag indicating case sensitivity (true for case-sensitive).
 *            ogWord - the original word used for accuracy checking.
 * returns:   boolean value indicating if data was found and collected (true) or not (false).
 * effects:   If the word is found, its file and line locations are printed to the output.
 */
bool Gerp::collectData(HashTable::WordData *word, bool i, std::string &ogWord) {
    // Does not exist
    if ((not word)) return false; // null = doesnt exist

    if (ogWord == "") return false; // doesnt exist

    bool foundMatch = false;

    std::set<HashTable::Dub> duplicateCheck; // takes care of duplicate lines
    // = new std::set<HashTable::Dub>;
    
    // Not nullptr, double check to see if it exists, print to outptut
    for (int j = 0; j < word->locations.size(); j++) {

        std::string output;
            
        int fileIndex = word->locations.at(j).file; // access fileIndex
        int lineNumIndex = word->locations.at(j).lineNum; //acces LineNum

        HashTable::Dub newDub; // make new double for the file and lineNum
        newDub.file = fileIndex;
        newDub.lineNum = lineNumIndex;

        if (not duplicateCheck.insert(newDub).second) {
            continue; // if there was a duplicate in set, skip current try
        }

        // If case sensitive, check to see if the words actually match
        if (i) {
            std::string lineCheck;
            lineCheck = array.at(fileIndex).lines.at(lineNumIndex);

            if (not accuracyCheck(ogWord, lineCheck)) continue; // exact check
        }

        // Path
        output += array.at(fileIndex).path + ":";
        
        // Line number
        output += std::to_string(lineNumIndex + 1) + ": ";

        // Full Line
        output += array.at(fileIndex).lines.at(lineNumIndex) + "\n";

        // std::cout << output << std::endl;

        printToOutput(output);
        foundMatch = true;
    }

    return foundMatch;
}


/*
 * name:      accuracyCheck
 * purpose:   Checks if the original word matches any of the words in the full line.
 * arguments: ogWord - the original word being checked.
 *            fullLine - the line to check for the word.
 * returns:   true if a match is found, false otherwise.
 * effects:   none
 */
bool Gerp::accuracyCheck(std::string &ogWord, std::string &fullLine) {
    std::istringstream iss(fullLine); 

    std::string toCheck;

    while (iss >> toCheck) { // get every word
        std::string strippedCheck = stripNonAlphaNum(toCheck); 
        if (ogWord == strippedCheck) return true; //if match return true
    }
    
    return false; // if not exact match, sensitive match is false
}


/*
 * name:      stripNonAlphaNum
 * purpose:   Removes all leading and trailing non-alphanumeric characters from 
 *            a string.
 * arguments: the string to be stripped of non-alphanumeric characters.
 * returns:   A string with all non-alphanumeric characters removed from both 
 *            ends.
 * effects:   None.
 */
std::string Gerp::stripNonAlphaNum(std::string &input) {
    if (input.empty()) return ""; // Handle empty strings

    int firstIndex = 0; //starting index
    int size = input.size();
    int lastIndex = size - 1; //starting index for reverse traversal

    while ( (firstIndex < size) and (not isalnum(input[firstIndex]))) {
        firstIndex++;   //increment index if alnum not found
    }

    if (firstIndex == size) return "";

    while ((lastIndex >= 0) and (not isalnum(input[lastIndex]))) {
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
bool Gerp::traverseDirectory(std::string &directory) {
    try {
        // utilize FSTree to build directory structure
        FSTree newTree(directory); 
        DirNode *curr = newTree.getRoot();
        int fileNum = 0;

        //call recursive helper
        traverseRecursive(curr, directory, &fileNum);
    } catch (std::runtime_error &e) { //catches so program can continue to run
        std::cerr << "Could not build index, reason:\n" << e.what() 
        << std::endl;
        return false;
    } 

    return true;
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
void Gerp::traverseRecursive(DirNode *curr, std::string &path, int *fileNum) {
    if (not curr) return; // check for nullptr
    int subDirs = curr->numSubDirs();
    int files = curr->numFiles();

    int ogSize = path.size();

    for (int i = 0; i < subDirs; i++) {
        path += "/" + curr->getSubDir(i)->getName(); //update path for next dir
        traverseRecursive(curr->getSubDir(i), path, fileNum);
        path.resize(ogSize); //reset path to remove other sub dir of curr dir
    }

    for (int i = 0; i < files; i++) {
        fileData newEntry;
        newEntry.path = path + "/" + curr->getFile(i); // if file add path
    
        std::ifstream infile(newEntry.path); // open file

        if (not infile.is_open()) std::cout << "bad file" << std::endl;

        // check if openeable
        std::string currLine;
        int lineNum = 0;

        while (std::getline(infile, currLine)) {
            newEntry.lines.push_back(currLine); // add line to data structure

            std::stringstream iss(currLine); // parse line into words

            std::string currWord;
            while (iss >> currWord) { // while words in line
                std::string stripped = stripNonAlphaNum(currWord);
                std::string lowerWord = "";

                for (char c : stripped) {
                    lowerWord += tolower(c);
                }

                // Send to hash table
                table.insert(*fileNum, lineNum, lowerWord); // insert word        
            }

            lineNum++; // increment lineNum
        }
        *fileNum += 1;   

        array.push_back(newEntry);
    }
}

