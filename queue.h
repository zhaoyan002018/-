#pragma once
#include<iostream>
using namespace std;
//循环队列顺序表作容器

template<typename T> class Quque
{
	//容器、队首指针、队尾指针。
	//数据从队尾入队，队首出队
	T* container;
	int head, tail;
	int max;
public:
	Quque(int n = 10) {
		head = 0;
		tail = 1;//从1开始存储,指向下一个存储的位置
		container = new T[n + 1];//不指定长度，默认为容器大小为11，其中10个单位长度用来存储，1个单位用来区分队首队尾 }
		max = n + 1;
	}
	~Quque() {
		makeEmpty();
		delete[] container;
	}
	bool enQueue(const T& ele);
	T deQueue();
	bool isFull();
	bool isEmpty();
	void makeEmpty();
	void print();

};
template<typename T>bool Quque<T>::enQueue(const T& ele)
{
	if (isFull()) {
		cout << "队列已满" << endl;
		return false;
	}
	container[tail] = ele;
	tail = (tail + 1) % max;
	return true;
}

template<typename T>T Quque<T>::deQueue()
{
	if (isEmpty()) {
		cout << "队列为空" << endl;
		return false;
	}

	head = (head + 1) % max;
	T ele = container[head];
	return ele;

}

//如果tail下一个位置是head，则满
template<typename T>bool Quque<T>::isFull()
{
	//int nextTail = (tail + 1) % max;//注意，此时tail还没有存放数据，所以需要判断的是tail自己是不是head，而head指向的空间是不会存储的，永远取head+1的位置。
	if (tail == head)
		return true;
	return false;
}
//如果head下一个位置是tail，则空
template<typename T>bool Quque<T>::isEmpty()
{
	int nextHead = (head + 1) % max;
	if (nextHead == tail)
		return true;
	return false;
}

template<typename T>void  Quque<T>::makeEmpty()
{
	int  nextHead;
	while ((nextHead = (head + 1) % max) != tail) {
		container[nextHead] = 0;
		head = nextHead;
	}
}

template<typename T>void  Quque<T>::print()
{
	int  nextHead = (head + 1) % max;
	while (nextHead != tail) {
		cout << container[nextHead] << endl;
		nextHead = (nextHead + 1) % max;
	}
}
