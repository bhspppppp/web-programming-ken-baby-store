#include <iostream>
#include <fstream>
#include <string>
#include "tree.h"

using namespace std;

string cleanWord(string w) {
    string result = "";
    for (int i = 0; i < w.length(); i++) {
        if (isalpha(w[i]) || w[i] == '\'')
            result += tolower(w[i]);
    }
    return result;
}

int main() {
    string filename;
    cout << "enter filename: ";
    cin >> filename;

    ifstream file(filename.c_str());
    if (!file.is_open()) {
        cout << "cant open file " << filename << endl;
        return 1;
    }

    BST<string> tree;
    string line;
    int lineNum = 0;

    while (getline(file, line)) {
        lineNum++;
        string word = "";
        for (int i = 0; i <= line.length(); i++) {
            if (i < line.length() && (isalpha(line[i]) || line[i] == '\'')) {
                word += line[i];
            } else {
                if (!word.empty()) {
                    string cleaned = cleanWord(word);
                    if (!cleaned.empty())
                        tree.insert(cleaned, lineNum);
                    word = "";
                }
            }
        }
    }

    file.close();

    cout << endl;
    cout << "--- cross reference ---" << endl;
    tree.inorder();

    return 0;
}
