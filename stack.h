#pragma once
#include<iostream>
using namespace std;
//顺序栈类模板，（顺序表即指数组）

//压栈、弹出、取元素、清空栈元素、判断空、满。，并且栈满不可再入栈，栈空不可再出栈
template<typename T> class stack
{
	//栈顶指针、栈容器、大小。
	T* container;
	int top;//指向下一个要push的位置
	int max;
public:
	stack();
	stack(int n);
	~stack();
	bool push(const T& ele);
	bool pop(T& ele);
	bool isEmpty();
	bool isFull();
	void makeEmpty();
	void traverse();

};

template<typename T> stack<T>::stack()
{
	int n;
	cout << "请输入栈容器的大小:" << endl;
	cin >> n;
	container = new T[n];
	if (!container) {
		cout << "分配失败！" << endl;
		exit(-1);
	}
	top = 0;
	max = n;
}
template<typename T> stack<T>::stack(int n)
{
	container = new T[n];
	if (!container) {
		cout << "分配失败！" << endl;
		exit(-1);
	}
	top = 0;
	max = n;
}
template<typename T> stack<T>::~stack()
{
	delete[] container;
	top = max = 0;
}
template<typename T> bool stack<T>::push(const T& ele)
{
	if (isFull())
		return false;

	container[top++] = ele;

	return true;
}
template<typename T> bool stack<T>::pop(T& ele)
{
	if (isEmpty())
		return false;
	ele = container[--top];
	container[top] = 0;
	return true;
}
template<typename T> bool stack<T>::isEmpty()
{
	if (!top)
		return true;
	return false;
}
template<typename T> bool stack<T>::isFull()
{
	if (top == max)
		return true;
	return false;
}
template<typename T> void stack<T>::makeEmpty()
{

	while (top) {

		container[top - 1] = 0;
		top--;
	}
}

template<typename T> void stack<T>::traverse()
{
	if (isEmpty())
		return;
	int t = top;
	cout << "栈中的数据按照顺序依次为：" << endl;
	while (t)
	{
		cout << container[t - 1] << endl;
		t--;
	}
}
