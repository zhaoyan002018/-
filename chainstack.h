#pragma once
#include<iostream>
using namespace std;
//链栈（以链表作为容器）

template<typename T> class stackNode
{
	//根据栈节点的特点，先进先出，用单链表即可
	T data;
	stackNode<T>* link;
public:
	stackNode();
	stackNode(T pdata);
	~stackNode();
	template<typename T> friend class chainStack;
};
template<typename T> stackNode<T>::stackNode()
{
	link = NULL;
}
template<typename T> stackNode<T>::stackNode(T pdata)
{
	data = pdata;
	link = NULL;
}
template<typename T> stackNode<T>::~stackNode()
{
	link = NULL;
}

template<typename T> class chainStack
{
	//从栈顶插入，栈底不动
	stackNode<T>* top, * head;//栈底并不需要给出
	//设计成head并不指向任何实际数据，仅作为找到chainStack的作用,top指向head的下一个节点。bottom指向最后一个节点。
	//待优化：并不需要head指出链表的位置
public:
	chainStack();
	~chainStack();
	bool push(const T& ele);
	bool pop(T& ele);
	bool isEmpty();
	void makeEmpty();
	void traverse();
};

template<typename T> chainStack<T>::chainStack()
{
	head = new stackNode<T>();
	top = head->link;
}
template<typename T> chainStack<T>::~chainStack()
{
	delete head;
}
template<typename T> bool chainStack<T>::push(const T& ele)
{
	top = new stackNode<T>(ele);
	if (!top) {
		cout << "分配stacknode失败" << endl;
		return false;
	}
	top->link = head->link;
	head->link = top;
	return true;
}
template<typename T> bool chainStack<T>::pop(T& ele)
{
	if (isEmpty())
		return false;

	ele = top->data;
	head->link = top->link;
	delete top;
	top = head->link;

	return true;
}
template<typename T> bool chainStack<T>::isEmpty()
{
	if (head->link == NULL)
		return true;
	return false;
}
template<typename T> void chainStack<T>::makeEmpty()
{
	/*while (top)
	{
		stackNode<T>* pnode = top;
		top = pnode->link;
		delete pnode;
	}
	head->link = NULL;*/
	int i;
	while (pop(i));
}
template<typename T> void chainStack<T>::traverse()
{
	cout << "栈中的数据按照顺序依次为：" << endl;
	stackNode<T>* pnode = top;
	while (pnode)
	{
		cout << pnode->data << endl;
		pnode = pnode->link;

	}
}
