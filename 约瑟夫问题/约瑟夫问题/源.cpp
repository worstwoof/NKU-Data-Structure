#include <iostream>
using namespace std;
struct Node {
	int data;
	Node* next;
	Node(int val):data(val),next(nullptr){}
};
class LinkedList {	
public:
	Node* head;
	Node* tail;
	LinkedList():head(nullptr),tail(nullptr){}
	~LinkedList() {
		if (!head) {
			return;
		}
		Node* current = head;
		while (current!= head&&current!=tail) {
			Node* next = current->next;
			delete current;
			current = next;
		}
		delete tail;
		head = nullptr;
		tail = nullptr;
	}
	void append(int val) {
		Node* newNode = new Node(val);
		if (head == nullptr) {
			head = newNode;
			tail = newNode;
			tail->next = head;
			head->next = tail;
			return;
		}
		newNode->next = head;
		tail->next = newNode;
		tail = newNode;
	}
};

int main() {
	LinkedList list;
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		list.append(i);
	}
	Node* current = list.tail;
	while (n > 0) {
		for (int i = 0; i < k - 1; i++) {
			current = current->next;
		}
		Node* temp = current->next;
		cout << temp->data;
		if (n > 1) {
			cout << "->";
			current->next = temp->next;
			if (temp == list.head) {
				list.head = current->next;
			}
			if (temp == list.tail) {
				list.tail = current;
			}
			delete temp;
		}
		else {
			delete temp;
			list.head = nullptr;
			list.tail = nullptr;
		}
		n--;
	}
}