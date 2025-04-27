#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(std::string& in, const std::string& floating, std::set<std::string>& words, int num, const std::set<std::string>& dict);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    //helper that does recursion
    set<string> words;
    string trial = in;
    wordleHelper(trial, floating, words, 0, dict);

    return words;

}

void wordleHelper(std::string& in, const std::string& floating, set<string>& wordSet,
    int start, const std::set<std::string>& dict)
{
    //check if valid size
    if (in.find('-') == string::npos && floating.size() == 0) {
        //check all floating are used
        
        if (dict.find(in) != dict.end()) {
            wordSet.insert(in);
        }
        return;
    }
    //early pruning if number of - is less than floating letters
    size_t emptyCount = 0;
    for (char c : in) {
        if (c == '-') emptyCount++;
    }
    if (emptyCount < floating.size()) {
        return;
    }

    for (size_t i = start; i < in.size(); i++) {
        if (in[i] != '-') {
            continue;
        }
        for (char c = 'a'; c <= 'z'; c++) {
            in[i] = c;

            //creates new floating string that removes used letters
            string remFloating = floating;
            size_t pos = remFloating.find(c);
            if (pos != string::npos) remFloating.erase(pos,1);
            
            wordleHelper(in, remFloating, wordSet, int(i + 1), dict);
            in[i] = '-';
        }
    }
    return;

}

// Define any helper functions here
