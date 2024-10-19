#include <iostream>

using namespace std;

class Node {
private:
	int elem;
	Node* next;

	friend class LinkedList;
};

class LinkedList {
private:
	Node* head;
public:
	LinkedList() {
		head = NULL;
	}

	~LinkedList() {
		while (!empty()) {
			removeFront();
		}
	}

	int front() {
		return head->elem;
	}

	bool empty() {
		return head == NULL;
	}

	void addFront(int value) {
		Node* newNode = new Node;
		newNode->elem = value;
		newNode->next = head;
		head = newNode;
	}

	void removeFront() {
		Node* deleteNode = head;
		head = head->next;
		delete deleteNode;
	}
};

class Stack {
private:
	LinkedList S;
	int n;
public:
	bool empty() {
		return n == 0;
	}
	void pop() {
		if (!empty()) {
			S.removeFront();
			--n;
		}
	}
	void push(int value) {
		++n;
		S.addFront(value);
	}

	int top() {
		if (!empty()) {
			return S.front();
		}
	}
};

class Queue {
private:
	Stack enqueStack;
	Stack dequeStack;
public:
	void enqueue(int value) {
		enqueStack.push(value);
	}

	void dequeue() {
		if (dequeStack.empty()) {
			while (!enqueStack.empty()) {
				dequeStack.push(enqueStack.top());
				enqueStack.pop();
			}
		}
		return dequeStack.pop();
	}

	bool isEmpty() {
		return enqueStack.empty() && dequeStack.empty();
	}
};



int main() {
	return 0;
}