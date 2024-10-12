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
	enum {DEF_CAPACITY = 100}; // 기본 스택 용량
public:
	ArrayStack(int cap = DEF_CAPACITY);
	int size() const;
	bool empty() const;
	const E& top() const throw(StackEmpty);
	void push(const E& e) throw(StackFull);
	void pop() throw(StackEmpty);
private:
	E* S;
	int capacity; // 용량
	int t; // 최 상단 stack 인덱스
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
	S[++t] = e; // t를 1만큼 증가시키고, 증가된 t의 값을 S의 index에 대입
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
			stack.push(index);  // 정상적으로 푸시됨
		}

		// 여섯 번째 요소를 push할 때 예외 발생 (스택이 가득 참)
		stack.push(6);  // 여기서 StackFull 예외 발생

		for (int i = 0; i < 6; i++) {
			stack.pop();  // 정상적으로 팝됨
		}

		// 추가로 pop을 시도할 때 예외 발생 (스택이 비어 있음)
		stack.pop();  // 여기서 StackEmpty 예외 발생
	}
	catch (const StackFull& e) {
		cout << "Exception: " << e.getMessage() << endl;
	}
	catch (const StackEmpty& e) {
		cout << "Exception: " << e.getMessage() << endl;
	}
	return 0;
}
