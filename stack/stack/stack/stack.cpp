#include <iostream>
#include <string>
using namespace std;

class RuntimeException {
private:
	string errMsg;
public:
	RuntimeException(const string& err) { errMsg = err; }
	string getMessage() const { return errMsg; }
};

class StackEmpty : public RuntimeException {
public:
	StackEmpty(const string& err) : RuntimeException(err) {}
};

class StackFull : public RuntimeException {
public : 
	StackFull(const string& err) : RuntimeException(err) {}
};

template <typename E>
class Stack {
public:
	int size() const;
	bool empty() const;
	const E& top() const throw(StackEmpty);
	void push(const E& e);
	void pop() throw(StackEmpty);
};

template <typename E>
class ArrayStack {
	enum {DEF_CAPACITY = 100}; // �⺻ ���� �뷮
public:
	ArrayStack(int cap = DEF_CAPACITY);
	int size() const;
	bool empty() const;
	const E& top() const throw(StackEmpty);
	void push(const E& e) throw(StackFull);
	void pop() throw(StackEmpty);
private:
	E* S;
	int capacity; // �뷮
	int t; // �� ��� stack �ε���
};

template <typename E> ArrayStack<E>::ArrayStack(int cap) : S(new E[cap]), capacity(cap), t(-1) {}
template <typename E> int ArrayStack<E>::size() const { return (t + 1); }
template <typename E> bool ArrayStack<E>::empty() const { return (t < 0); }

template <typename E>
const E& ArrayStack<E>::top() const throw(StackEmpty) {
	if (empty()) throw StackEmpty("Top of empty stack");
	return S[t];
}

template <typename E>
void ArrayStack<E>::push(const E& e) throw(StackFull) {
	if (size() == capacity) throw StackFull("Push to full stack");
	S[++t] = e; // t�� 1��ŭ ������Ű��, ������ t�� ���� S�� index�� ����
}

template <typename E>
void ArrayStack<E>::pop() throw(StackEmpty) {
	if (empty()) throw StackEmpty("Pop from empty stack");
	--t;
}
int main() {
	try {
		ArrayStack<int> stack(5);
		for (int index = 1; index < 6; index++) {
			stack.push(index);  // ���������� Ǫ�õ�
		}

		// ���� ��° ��Ҹ� push�� �� ���� �߻� (������ ���� ��)
		stack.push(6);  // ���⼭ StackFull ���� �߻�

		for (int i = 0; i < 6; i++) {
			stack.pop();  // ���������� �˵�
		}

		// �߰��� pop�� �õ��� �� ���� �߻� (������ ��� ����)
		stack.pop();  // ���⼭ StackEmpty ���� �߻�
	}
	catch (const StackFull& e) {
		cout << "Exception: " << e.getMessage() << endl;
	}
	catch (const StackEmpty& e) {
		cout << "Exception: " << e.getMessage() << endl;
	}
	return 0;
}
