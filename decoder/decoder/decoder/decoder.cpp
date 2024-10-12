#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <any>
#include <sstream>

using namespace std;

class StringNode {
private:
    string body;
    StringNode* next;

    friend class StackLinkedList;
    friend class StringDecoder;
};

class StackLinkedList {
private:
    int size;
    string decodeString;
    StringNode* head;
public:
    StackLinkedList();
    ~StackLinkedList();
    const string& get(int index) const;
    void add(const string& e);
    void pop();
    void printAll();
};

class StringDecoder {
private:
    string enc;
    string dec;
    char hexadecimalArr[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
public:
    vector<string> getFile(string path);
    vector<string> stringdecoder(vector<string> enc_list, StackLinkedList& linkedList);
    void compare_contents(string get_enc, string get_dec);
    bool isHexadecimal(char value);
    vector<int> getBracketIndex(string enc);
};

int main() {
    StackLinkedList linkedList;
    StringDecoder decoder;
    vector<string> enc = decoder.getFile("input.5");
    vector<string> dec = decoder.stringdecoder(enc, linkedList);
    
    linkedList.printAll();
	return 0;
}

StackLinkedList::StackLinkedList() : head(NULL), size(0) {}
StackLinkedList::~StackLinkedList() { while (size > 0) pop(); }

const string& StackLinkedList::get(int index) const {
    StringNode* curr = head;
    for (int i = 1; i < index; i++) {
        curr = curr->next;
    }
    return curr->body;
}

void StackLinkedList::add(const string& e) {
    StringNode* newNode = new StringNode;
    newNode->body = e;
    newNode->next = NULL;
    if (size == 0) {
        head = newNode;
    }
    else {
        StringNode* curr = head;
        for (int i = 1; i < size; i++) {
            curr = curr->next;
        }
        curr->next = newNode;
    }
    size++;
}

void StackLinkedList::pop() {
    if (head == NULL) {
        return;
    }
    StringNode* target;
    if (size == 1) {
        target = head;
        head = target->next;
    }
    else {
        StringNode* curr = head;
        for (int i = 1; i < size - 1; i++) {
            curr = curr->next;
        }
        target = curr->next;
        curr->next = NULL;
    }

    decodeString += target->body;

    delete target;
    size--;
}

void StackLinkedList::printAll() {
    for (int i = 1; i < size + 1; i++) {
        cout << get(i) << " ";
    }
    cout << endl;
}

vector<string> StringDecoder::getFile(string fileName) {
    vector<string> txt;
    string filePath = "PA02_test/" + fileName + ".txt";
    ifstream file(filePath);

    string line;
    while (getline(file, line)) {
        txt.push_back(line);
    }

    file.close();
    return txt;
}

vector<int> StringDecoder::getBracketIndex(string enc) {
    vector<int> index;
    for (int i = 0; i < enc.size(); i++) {
        if (enc[i] == '{') {
            int depth = 1;
            string tmpString;
            index.push_back(i);
            while (i < enc.size() && depth > 0) {
                i++;
                if (enc[i] == '{') {
                    depth++;
                    index.push_back(i);
                }
                else if (enc[i] == '}') {
                    depth--;
                    index.push_back(i);
                    if (depth == 0) {
                        break;
                    }
                }
            }
        }
    }

    return index;
}

vector<string> StringDecoder::stringdecoder(vector<string> enc_list, StackLinkedList& linkedList) {
    vector<string> result;

    for (int index = 0; index < enc_list.size(); index++) {
        string enc = enc_list[index];
        vector<int> bracketIdx = getBracketIndex(enc);
        string tmpString;

        for (int i = 0; i < enc.size(); i++) {
            bool isMatchIndex = false;
            for (int j = 0; j < bracketIdx.size(); j++) {
                if (i == bracketIdx[j]) {
                    isMatchIndex = true;
                    tmpString += " ";
                }
            }

            if (i > 0 && isHexadecimal(enc[i])) { 
                if (enc[i + 1] == '{') {
                    tmpString += " "; 
                }
            }

            if (!isMatchIndex) {
                tmpString += enc[i];
            }
        }

        result.push_back(tmpString);
        tmpString.clear();

        string input = result[index];
        stringstream ss(input);

        string word;
        vector<string> words;

        while (ss >> word) {
            words.push_back(word);
        }

        for (int i = words.size() - 1; i >= 0; i--) {
            linkedList.add(words[i]);
        }

        
    }

    return result;
}

bool StringDecoder::isHexadecimal(char value) {
    for (int i = 0; i < 16; i++) {
        if (hexadecimalArr[i] == value) return true;
    }
    return false;
}