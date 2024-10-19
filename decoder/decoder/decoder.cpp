#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class StringNode {
private:
    string body;
    StringNode* next;

    friend class SLinkedList;
    friend class StringDecoder;
    friend class LinkedStack;

};

class SLinkedList {
private:
    StringNode* top;
    friend class LinkedStack;
public:
    SLinkedList();
    ~SLinkedList();
    bool empty() const;
    const string& front() const;
    void addFront(const string& e);
    void removeFront();
    string get(int index);
};

SLinkedList::SLinkedList() : top(NULL) {}
SLinkedList::~SLinkedList() { while (!empty()) removeFront(); }
bool SLinkedList::empty() const { return top == NULL; }
const string& SLinkedList::front() const { return top->body; }

void SLinkedList::addFront(const string& e) {
    StringNode* v = new StringNode;
    v->body = e;
    v->next = top;
    top = v;
}

void SLinkedList::removeFront() {
    StringNode* old = top;
    top = old->next;
    delete old;
}

string SLinkedList::get(int index) {
    StringNode* curr = top;
    for (int i = 1; i < index; i++) {
        curr = curr->next;
    }
    return curr->body;
}

typedef string Elem;
class LinkedStack {
private:
    SLinkedList S;
    int n;
public:
    LinkedStack();
    int size() const;
    bool empty() const;
    const Elem& top() const;
    void push(const Elem& e);
    void pop();
    void printAll();
    void clearAll();
};

LinkedStack::LinkedStack() : S(), n(0) {}
int LinkedStack::size() const { return n; }
bool LinkedStack::empty() const { return n == 0; }
void LinkedStack::clearAll() {
    while (n == 0) {
        pop();
    }
}

const Elem& LinkedStack::top() const {
    if (!empty()) {
        return S.front();
    }
    throw runtime_error("Top of empty Stack");
}

void LinkedStack::push(const Elem& e) {
    ++n;
    S.addFront(e);
}

void LinkedStack::pop() {
    if (!empty()) {
        Elem value = S.front();
        S.removeFront();
        --n;
    }
}

void LinkedStack::printAll() {
    StringNode* curr = S.top;
    while (curr != NULL) {
        cout << curr->body << "";
        curr = curr->next;
    }
    cout << endl;
}

class StringDecoder {
private:
    LinkedStack post_fix_stack;
    LinkedStack cal_stack;
public:
    vector<string> read(string path);
    string repeatString(string value, string count);
    void infixToPostFix(string value);
    string stringdecoder(string enc);
    bool compare_contents(string dec, string solution);
};

vector<string> StringDecoder::read(string fileName) {
    ifstream file(fileName);

    vector<string> result;
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            result.push_back(line);
        }
        file.close();
    }

    return result;
}

void StringDecoder::infixToPostFix(string value) {
    vector<string> tmpString;
    string currentValue;
    int bracketCount = 0;

    for (int index = 0; index < value.length(); index++) {
        char word = value[index];
        if (word == '{') {
            post_fix_stack.push(string(1, word));
            if (!currentValue.empty()) {
                tmpString.push_back(currentValue);
                currentValue.clear();
            }
            bracketCount++;
        }
        else if (word == '}') {
            if (!currentValue.empty()) {
                tmpString.push_back(currentValue);
                currentValue.clear();
            }
            while (!post_fix_stack.empty() && post_fix_stack.top() != "{") {
                post_fix_stack.pop();
            }
            bracketCount--;
            if (bracketCount == 0 && index != value.length() - 1) {
                while (!post_fix_stack.empty()) {
                    tmpString.push_back(post_fix_stack.top());
                    post_fix_stack.pop();
                }
                tmpString.push_back("+");
            }
        }
        else {
            currentValue += word;
        }
    }

    if (!currentValue.empty()) {
        tmpString.push_back(currentValue);
    }

    if (!post_fix_stack.empty()) {
        post_fix_stack.clearAll();
    }

    for (int i = tmpString.size() - 1; i >= 0; i--) {
        post_fix_stack.push(tmpString[i]);
    }
}

string StringDecoder::repeatString(string value, string count) {
    try {
        string countValue = count;
        string extraString;
        string result;

        if (value == "ERROR") {
            return "ERROR";
        }
        else if (count.length() != 1) {
            for (int index = 0; index < count.size() - 1; index++) {
                extraString += count[index];
            }
            countValue = count[count.size() - 1];
        }

        result += extraString;
        int decimalValue = stoi(countValue, nullptr, 16);
        for (int i = 0; i < decimalValue; ++i) {
            result += value;
        }
        return result;
    }
    catch (const invalid_argument& e) {
        return "ERROR";
    }
    catch (const out_of_range& e) {
        return "ERROR";
    }
}

string StringDecoder::stringdecoder(string enc) {
    vector<string> resultVector;
    string result = "";

    infixToPostFix(enc);

    while (!post_fix_stack.empty()) {
        string top = post_fix_stack.top();
        if (top == "{") {
            string left = cal_stack.top(); cal_stack.pop();
            string right = cal_stack.top(); cal_stack.pop();
            string resultString = repeatString(left, right);
            cal_stack.push(resultString);
            left.clear();
            right.clear();
            post_fix_stack.pop();
        }
        else if (top == "+") {
            post_fix_stack.pop();
        }
        else {
            cal_stack.push(top);
            post_fix_stack.pop();
        }
    }

    while (!cal_stack.empty()) {
        resultVector.push_back(cal_stack.top());
        cal_stack.pop();
    }

    for (int i = resultVector.size() - 1; i >= 0; i--) {
        result += resultVector[i];
    }

    if (result.find("ERROR") != std::string::npos) {
        result = "ERROR: Invalid input";
    }

    return result;
}

bool StringDecoder::compare_contents(string dec, string solution) {
    LinkedStack* compareStack = new LinkedStack;
    compareStack->push(dec);
    compareStack->push(solution);

    while (!compareStack->empty()) {
        string first = compareStack->top(); compareStack->pop();
        string second = compareStack->top(); compareStack->pop();
        if (first != second) {
            return false;
        }
    }

    delete compareStack;
    return true;
}


int main() {
    StringDecoder decoder;
    LinkedStack stack;

    vector<string> encList;
    vector<string> solutionList;

    for (int index = 1; index < 51; index++) {
        string inputFileName = "input." + to_string(index) + ".txt";
        string outputFileName = "output." + to_string(index) + ".txt";
        for (int j = 0; j < 2; j++) {
            encList.push_back(decoder.read(inputFileName)[j]);
            solutionList.push_back(decoder.read(outputFileName)[j]);
        }
    }

    for (int index = 0; index < 100; index++) {
        string dec = decoder.stringdecoder(encList[index]);
        string solution = solutionList[index];
        if (decoder.compare_contents(dec, solution) == true) {
            cout << "matched" << endl;
        }
        else {
            cout << "not matched" << endl;
        }
    }

    return 0;
}