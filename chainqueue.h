#pragma once
#include<iostream>
using namespace std;
//循环队列 链表作容器

template<typename T> class queueNode
{
	T data;
	queueNode<T>* link;
public:
	queueNode() { link = NULL; }
	queueNode(const T& pdata) { data = pdata; link = NULL; }
	template<typename T> friend class chainQueue;
};

template<typename T> class chainQueue
{
	queueNode<T>* head, * tail;
public:
	chainQueue() { head = tail = NULL; }
	~chainQueue() { makeEmpty(); }
	bool enQueue(const T& ele);
	bool deQueue(T& ele);
	bool isEmpty();
	void makeEmpty();
	void print();
};
template<typename T>bool chainQueue<T>::enQueue(const T& ele)
{
	queueNode<T>* node = new queueNode<T>(ele);

	if (!head)
	{
		head = tail = node;
	}
	else {
		tail->link = node;
		tail = node;
	}
	return true;
}
template<typename T>bool chainQueue<T>::deQueue(T& ele)
{
	if (isEmpty())
		return false;
	ele = head->data;
	queueNode<T>* node = head;
	if (tail == head)
		tail = NULL;
	head = head->link;
	delete node;
}
template<typename T>bool chainQueue<T>::isEmpty()
{
	if (!head)
		return true;
	return false;
}
template<typename T>void  chainQueue<T>::makeEmpty()
{
	while (head) {
		queueNode<T>* node = head;
		head = head->link;
		delete node;
	}
	tail = head;
}
template<typename T>void  chainQueue<T>::print()
{
	queueNode<T>* node = head;
	while (node) {
		cout << node->data << endl;
		node = node->link;
	}
}
