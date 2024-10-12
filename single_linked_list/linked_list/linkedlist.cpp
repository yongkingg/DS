#include <iostream>

using namespace std;

class StringNode {
private:
	string elem;
	StringNode* next;

	friend class StringLinkedList;
};

class StringLinkedList {
private:
	StringNode* head;

public:
	int size;
	StringLinkedList();    // constructor : head를 NULL로 초기화
	~StringLinkedList();   // destructor  : 객체가 메모리에서 해제될때, 리스트에 남아있는 모든 노드들을 제거함 
	bool empty() const;
	const string& front() const;
	const string& get(int index) const;
	void addFront(const string& e);
	void removeFront();
	void removeTail();
	void removeNode(int index);
	void insertNode(const string& e, int index);
	void addTail(const string& e);
	void printAll();
};


StringLinkedList::StringLinkedList() : head(NULL), size(0) {}
StringLinkedList::~StringLinkedList() {
	while (!empty()) { // node 전체가 비워질때까지 반복
		removeFront();	}
	size = 0;
}

void StringLinkedList::printAll() {
	for (int i = 1; i < size + 1; i++) {
		cout << get(i) << " ";
	}
	cout << endl;
}
bool StringLinkedList::empty() const {
	return head == NULL; // Head가 비어있으면 true, 값이 있으면 false
}

const string& StringLinkedList::front() const {
	return head->elem;
}

const string& StringLinkedList::get(int index) const {
	StringNode* curr = head;
	for (int i = 1; i < index; i++) {
		curr = curr->next;
	}
	return curr->elem;
}

void StringLinkedList::addFront(const string& e) {
	StringNode* node = new StringNode;
	node->elem = e;
	node->next = head;
	head = node;
	size++;
}

void StringLinkedList::removeFront() {
	StringNode* old = head;
	head = old->next;
	delete old;
	size--;
}

void StringLinkedList::removeTail() {
	if (size == 1) {  // 리스트에 노드가 하나만 남은 경우
		removeFront();
		return;
	}

	StringNode* cur = head;
	for (int i = 1; i < size - 1; i++) {
		cur = cur->next;
	}
	StringNode* old = cur->next;
	cur->next = NULL;
	delete old;
	size--;
}


void StringLinkedList::removeNode(int index) {
	if (index == 1) {  // 첫 번째 노드를 삭제하는 경우
		removeFront(); 
		return;
	}

	StringNode* curr = head;
	for (int i = 1; i < index - 1; i++) {
		curr = curr->next;  // 삭제할 노드의 이전 노드
	}

	StringNode* old = curr->next;  // 삭제할 노드의 이전 노드의 next = 삭제할 노드 
	curr->next = old->next;  // 이전 노드가 삭제할 노드의 다음 노드를 가리키도록 업데이트
	delete old;  
	size--;  
}

void StringLinkedList::insertNode(const string& e, int index) {
	StringNode* newNode = new StringNode;
	newNode->elem = e;
	newNode->next = NULL;

	if (index == 1) {
		addFront(e);
		return;
	}

	StringNode* curr = head;
	for (int i = 1; i < index - 1; i++) {
		curr = curr->next;
	}
	newNode->next = curr->next;
	curr->next = newNode;
	size++;
}

void StringLinkedList::addTail(const string& e) {
	StringNode* curr = head;
	StringNode* newNode = new StringNode;
	newNode->elem = e;
	newNode->next = NULL;
	
	for (int i = 1; i < size; i++) {
		curr = curr->next;
	}

	curr->next = newNode;
	size++;
}

int main() {
	StringLinkedList singleLinkedList;
	singleLinkedList.addFront("반갑습니다2");
	singleLinkedList.addFront("반갑습니다1");
	singleLinkedList.addFront("안녕하세요");
	singleLinkedList.insertNode("하이", 4);
	singleLinkedList.printAll();
	singleLinkedList.addTail("안녕히가세요");
	singleLinkedList.printAll();
	singleLinkedList.removeTail();
	singleLinkedList.printAll();

	return 0;
}