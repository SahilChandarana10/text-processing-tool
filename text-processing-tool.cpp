#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> // For stringstream
#include <algorithm> // For find

using namespace std;

// Function to count lines in a file
int countLines(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file: " << filename << endl;
        return -1; // Indicate error
    }
    int lineCount = 0;
    string line;
    while (getline(file, line)) {
        lineCount++;
    }
    file.close();
    return lineCount;
}

// Function to count words in a file
int countWords(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file: " << filename << endl;
        return -1; // Indicate error
    }
    int wordCount = 0;
    string word;
    while (file >> word) {
        wordCount++;
    }
    file.close();
    return wordCount;
}

// Function to find occurrences of a word/phrase
vector<int> findOccurrences(const string& filename, const string& target) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file: " << filename << endl;
        return {}; // Return empty vector on error
    }

    vector<int> lineNumbers;
    string line;
    int lineNumber = 1;
    while (getline(file, line)) {
        if (line.find(target) != string::npos) {
            lineNumbers.push_back(lineNumber);
        }
        lineNumber++;
    }
    file.close();
    return lineNumbers;
}

// Function to handle commands
void handleCommand(const string& command) {
    stringstream ss(command);
    string action;
    ss >> action;

    if (action == "count_lines") {
        string filename;
        if (ss >> filename) {
            int lines = countLines(filename);
            if (lines != -1) {
                cout << "Line count: " << lines << endl;
            }
        } else {
            cerr << "Error: Invalid command format. Usage: count_lines <filename>" << endl;
        }
    } else if (action == "count_words") {
        string filename;
        if (ss >> filename) {
            int words = countWords(filename);
            if (words != -1) {
                cout << "Word count: " << words << endl;
            }
        } else {
            cerr << "Error: Invalid command format. Usage: count_words <filename>" << endl;
        }
    } else if (action == "find_pattern") {
        string filename, pattern;
        if (ss >> filename >> pattern) {
            vector<int> occurrences = findOccurrences(filename, pattern);
            if (!occurrences.empty()) {
                cout << "Pattern found on lines: ";
                for (int lineNum : occurrences) {
                    cout << lineNum << " ";
                }
                cout << endl;
            } else if (occurrences.empty() && countLines(filename) != -1) {
                cout << "Pattern not found." << endl;
            }
        } else {
            cerr << "Error: Invalid command format. Usage: find_pattern <filename> <pattern>" << endl;
        }
    }

    else {
        cerr << "Error: Unknown command: " << action << endl;
    }
}


