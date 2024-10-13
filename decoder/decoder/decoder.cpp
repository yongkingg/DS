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

};

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
};

LinkedStack::LinkedStack() : S(), n(0) {}
int LinkedStack::size() const { return n; }
bool LinkedStack::empty() const { return n == 0; }

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

const Elem& LinkedStack::top() const {
    if (!empty()) return S.front();
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
        cout << curr->body << " ";
        curr = curr->next;
    }
    cout << endl;
}

class StringDecoder {
private:
    string enc;
    string dec;
    LinkedStack stack;
public:
    vector<string> getFile(string path);
    vector<string> stringdecoder(vector<string> enc_list);
    vector<string> split(istream& value);
    void infixToPostFix(string value);
    void compare_contents(string get_enc, string get_dec);
    bool isHexadecimal(char value);
};

vector<string> StringDecoder::split(istream& value) {
        vector<string> result;
        string line;
    
        while (getline(value, line)) {
            result.push_back(line);
        }
    
        return result;
}

vector<string> StringDecoder::getFile(string fileName) {
        string filePath = "PA02_test/" + fileName + ".txt";
        ifstream file(filePath);
    
        return split(file);
}

//depth 변수를 도입하여 괄호의 깊이를 추적합니다.
//currentValue를 사용하여 현재 처리 중인 문자열을 저장합니다.
//여는 괄호{ 를 만나면 이전 currentValue를 tmpString에 추가하고 초기화합니다.
//닫는 괄호 }를 만나면 현재 currentValue를 tmpString에 추가하고 초기화합니다.
//일반 문자는 currentValue와 postFix에 모두 추가합니다.

void StringDecoder::infixToPostFix(string value) {
    vector<string> tmpString;
    string currentValue;
    int depth = 0;

    for (int index = 0; index < value.length(); index++) {
        char word = value[index];
        if (word == '{') {
            stack.push(string(1, word));
            if (!currentValue.empty()) {
                tmpString.push_back(currentValue);
                currentValue.clear();
            }
            depth++;
        }
        else if (word == '}') {
            if (!currentValue.empty()) {
                tmpString.push_back(currentValue);
                currentValue.clear();
            }
            while (!stack.empty() && stack.top() != "{") {
                stack.pop();
            }
            depth--;
            if (depth == 0 && index != value.length() -1) {
                while (!stack.empty()) {
                    tmpString.push_back(stack.top());
                    stack.pop();
                }
                tmpString.push_back("+");
            }
        }
        else {
            currentValue += word;
        }
    }

    // 스택에 남은 모든 연산자를 후위 표기법에 추가
    while (!stack.empty()) {
        tmpString.push_back(stack.top());
        stack.pop();
    }

    // 후위 표기법 변환 결과 stack에 저장
    for (int i = tmpString.size()-1; i >= 0; i--) {
        stack.push(tmpString[i]);
    }
}
vector<string> StringDecoder::stringdecoder(vector<string> enc_list) {
    for (int index = 0; index < enc_list.size(); index++) {
        cout << enc_list[index] << endl;
        infixToPostFix(enc_list[index]);

        stack.printAll();
        string first = stack.top(); stack.pop();
        string second = stack.top(); stack.pop();

        cout << "first : " << first << endl;
        cout << "second : " << second << endl;

        while (stack.top() == "{") {
            
        }

        // 하나 계산 후 스택 초기화
        while (!stack.empty()) {
            cout << stack.top() << endl;
            stack.pop();
        }

        cout << endl;
    }

    return enc_list;
}

int main() {
    StringDecoder decoder;
    LinkedStack stack;
    vector<string> enc = decoder.getFile("input.8");
    vector<string> dec = decoder.stringdecoder(enc);

    return 0;
}


