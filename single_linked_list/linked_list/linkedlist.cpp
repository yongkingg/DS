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
	StringLinkedList();    // constructor : head�� NULL�� �ʱ�ȭ
	~StringLinkedList();   // destructor  : ��ü�� �޸𸮿��� �����ɶ�, ����Ʈ�� �����ִ� ��� ������ ������ 
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
	while (!empty()) { // node ��ü�� ����������� �ݺ�
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
	return head == NULL; // Head�� ��������� true, ���� ������ false
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
	if (size == 1) {  // ����Ʈ�� ��尡 �ϳ��� ���� ���
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
	if (index == 1) {  // ù ��° ��带 �����ϴ� ���
		removeFront(); 
		return;
	}

	StringNode* curr = head;
	for (int i = 1; i < index - 1; i++) {
		curr = curr->next;  // ������ ����� ���� ���
	}

	StringNode* old = curr->next;  // ������ ����� ���� ����� next = ������ ��� 
	curr->next = old->next;  // ���� ��尡 ������ ����� ���� ��带 ����Ű���� ������Ʈ
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
	singleLinkedList.addFront("�ݰ����ϴ�2");
	singleLinkedList.addFront("�ݰ����ϴ�1");
	singleLinkedList.addFront("�ȳ��ϼ���");
	singleLinkedList.insertNode("����", 4);
	singleLinkedList.printAll();
	singleLinkedList.addTail("�ȳ���������");
	singleLinkedList.printAll();
	singleLinkedList.removeTail();
	singleLinkedList.printAll();

	return 0;
}