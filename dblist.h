#pragma once
#include<iostream>
using namespace std;
//双向链表类型模板

template <typename T> class dbNode
{
	T data;
	dbNode<T>* llink, * rlink;//左右指针
public:
	dbNode();
	dbNode(const T& pdata);
	void show();
	template<typename T> friend class MyChainDbList;
};
template <typename T> dbNode<T>::dbNode()
{
	llink = rlink = NULL;
}
template <typename T> dbNode<T>::dbNode(const T& pdata)
{
	data = pdata;
	llink = rlink = NULL;
}

template <typename T> void dbNode<T>::show()
{
	cout << data << endl;
}


template<typename T>  class MyChainDbList {

	dbNode<T>* head, * tail;//由于双向链表，tail尾指针实际可以用head->llink表示，可以简化只保留head
public:
	MyChainDbList();
	~MyChainDbList();
	void Insert(const T& data);
	void remove(dbNode<T>* p);
	void print();
	int length();
	dbNode<T>* find(const T& data);
	void makeEmpty();
	dbNode<T>* createNode(const T& data);
};

template<typename T> MyChainDbList<T>::MyChainDbList()
{
	head = tail = createNode(NULL);
	head->llink = head->rlink = head;//指向自己，形成闭环。
}

template<typename T> MyChainDbList<T>::~MyChainDbList()
{
	makeEmpty();
	if (head)
		delete head;
	head = tail = NULL;
}

template<typename T>  dbNode<T>* MyChainDbList<T>::createNode(const T& data)
{
	dbNode<T>* node;
	if (data)
		node = new dbNode<T>(data);
	else
		node = new dbNode<T>();
	return node;
}
//采取链尾插入方式
template<typename T> void MyChainDbList<T>::Insert(const T& data)
{
	dbNode<T>* tmpP = createNode(data);

	tmpP->llink = tail;
	tmpP->rlink = tail->rlink;

	tail->rlink->llink = tmpP;
	tail->rlink = tmpP;

	tail = tmpP;
}

template<typename T> void MyChainDbList<T>::remove(dbNode<T>* p)
{
	//此时默认p一定是链表内的结点，并非稳健，优化需要先对链表进行一次遍历查找。
	dbNode<T>* lp = p->llink;
	if (lp != p) {
		lp->rlink = p->rlink;
		p->rlink->llink = lp;
		delete p;
	}
}

template<typename T> void MyChainDbList<T>::print()
{
	dbNode<T>* tmpP = head->rlink;
	while (tmpP != head) {
		tmpP->show();
		tmpP = tmpP->rlink;
	}
}

template<typename T> int MyChainDbList<T>::length()
{
	int i = 0;
	dbNode<T>* tmpP = head->llink;
	while (tmpP != head) {
		i++;
		tmpP = tmpP->llink;
	}
	return i;
}

template<typename T> dbNode<T>* MyChainDbList<T>::find(const T& data)
{
	dbNode<T>* tmpP = head->llink;
	while (tmpP != head) {
		if (tmpP->data == data)
			break;
		tmpP = tmpP->llink;
	}
	if (tmpP == head)
		return NULL;
	else
		return tmpP;
}
template<typename T> void MyChainDbList<T>::makeEmpty()
{
	dbNode<T>* p = head;
	while (p->rlink != head) {
		dbNode<T>* rp = p->rlink;
		rp->rlink->llink = p;
		p->rlink = rp->rlink;

		delete rp;

	}
}
