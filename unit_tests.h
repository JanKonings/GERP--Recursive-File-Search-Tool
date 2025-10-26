/*
 *  unit_tests.h
 *  Jan Konings (jkonin01)
 *  Jude Vamenta (jvamen01)
 *  November 12, 2024
 *
 *  CS 15 Final Project - gerp
 *
 *  Run tests for all the functions within gerp
 *  
 *
 */

#include <cassert>
#include <iostream>
#include "processing.h"

using namespace std;

void test_isAlphaNumeric_default() {
   string test = "!@##!!#!@!#COMP-15!!!!!!!";

   string result = stripNonAlphaNum(test);

   assert(result == "COMP-15");
}


void test_isAlphaNumeric_singleChar() {
   string test = "a";

   string result = stripNonAlphaNum(test);

   assert(result == "a");
}

void test_isAlphaNumeric_inBetween() {
   string test = "!@#$%^&*()h#e#l#l#o!@#$%^&*()";

   string result = stripNonAlphaNum(test);

   assert(result == "h#e#l#l#o");
}

void test_isAlphaNumeric_empty() {
   string test = "";

   string result = stripNonAlphaNum(test);

   assert(result == "");
}

void test_isAlphaNumeric_noHits() {
   string test = "!@#$%^&*()!@#$%^&*()";

   string result = stripNonAlphaNum(test);

   assert(result == "");
}

void test_isAlphaNumeric_allValid() {
   string test = "hello";

   string result = stripNonAlphaNum(test);

   assert(result == "hello");
}

void test_directory_simple() {
   string directory = "testDirectory";
   traverseDirectory(directory);

   assert(1 == 1);
}

void test_directory_tinyData() {
   string directory = "/comp/15/files/proj-gerp-test-dirs/tinyData";
   traverseDirectory(directory);

   assert(1 == 1);
}

void test_directory_smallGutenberg() {
   string directory = "/comp/15/files/proj-gerp-test-dirs/smallGutenberg";
   traverseDirectory(directory);

   assert(1 == 1);
}

void test_directory_lab1() {
   string directory = "/comp/15/files/lab_arraylists";
   traverseDirectory(directory);

   assert(1 == 1);
}


