#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;


int countLines(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file: " << filename << endl;
        return -1;
    }
    int lineCount = 0;
    string line;
    while (getline(file, line)) {
        lineCount++;
    }
    file.close();
    return lineCount;
}

int countWords(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file: " << filename << endl;
        return -1;
    }
    int wordCount = 0;
    string word;
    while (file >> word) {
        wordCount++;
    }
    file.close();
    return wordCount;
}

vector<int> findOccurrences(const string& filename, const string& target) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file: " << filename << endl;
        return {};
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

void showHelp() {
    cout << "\nAvailable Commands:\n";
    cout << "  count_lines <filename>                 - Count number of lines in the file\n";
    cout << "  count_words <filename>                 - Count number of words in the file\n";
    cout << "  find_pattern <filename> <pattern>      - Find all lines containing the pattern\n";
    cout << "  help                                   - Show this help message\n";
    cout << "  exit                                   - Exit the program\n\n";
}

void handleCommand(const string& command) {
    stringstream ss(command);
    string action;
    ss >> action;

    if (action == "count_lines") {
        string filename;
        ss >> filename;
        if (!filename.empty()) {
            int lines = countLines(filename);
            if (lines != -1) {
                cout << "Line count: " << lines << endl;
            }
        } else {
            cerr << "Error: Usage: count_lines <filename>\n";
        }

    } else if (action == "count_words") {
        string filename;
        ss >> filename;
        if (!filename.empty()) {
            int words = countWords(filename);
            if (words != -1) {
                cout << "Word count: " << words << endl;
            }
        } else {
            cerr << "Error: Usage: count_words <filename>\n";
        }

    } else if (action == "find_pattern") {
        string filename;
        ss >> filename;
        string pattern;
        getline(ss, pattern);
        pattern = trim(pattern);

        if (!filename.empty() && !pattern.empty()) {
            vector<int> occurrences = findOccurrences(filename, pattern);
            if (!occurrences.empty()) {
                cout << "Pattern found on lines: ";
                for (int lineNum : occurrences) {
                    cout << lineNum << " ";
                }
                cout << endl;
            } else if (countLines(filename) != -1) {
                cout << "Pattern not found." << endl;
            }
        } else {
            cerr << "Error: Usage: find_pattern <filename> <pattern>\n";
        }

    } else if (action == "help") {
        showHelp();

    } else if (action == "exit") {
        cout << "Exiting program.\n";
        exit(0);

    } else {
        cerr << "Error: Unknown command '" << action << "'. Type 'help' for a list of commands.\n";
    }
}

int main() {
    cout << "===== File Analyzer CLI =====\n";
    cout << "Type 'help' for a list of commands.\n";

    string inputCommand;
    while (true) {
        cout << "\n> ";
        getline(cin, inputCommand);
        inputCommand = trim(inputCommand);

        if (!inputCommand.empty()) {
            handleCommand(inputCommand);
        }
    }

    return 0;
}
