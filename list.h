#pragma once
#include<iostream>
using namespace std;
//单链表类型模板

template<typename T> class Node
{
	T data;
	Node<T>* link;
public:
	//如果没有对外的接口，可想而知就如同C语言中用struct结构保存node一样，只需要数据类型。
	Node();
	//~Node();
	Node(const T& pdata);

	Node<T>* DeleteNextNode();//刪除后继节点，并返回指向该节点的指针
	void ShowNode();
	template<typename T> friend class MyChainList;//声明友元类，可以直接访问私有成员
};

template<typename T> Node<T>::Node()
{
	data = 0;//如果data是类，应该用其自身的清空接口。
	link = NULL;
}
template<typename T> Node<T>::Node(const T& pdata)
{
	//cout << "进入 node 构造函数中,data地址为：" << &pdata << endl;
	data = pdata;//data赋值，并没有依赖pdata的声明周期。
	link = NULL;
}
//析构时不能写入的原因？
//template<typename T> Node<T>::~Node()
//{
//	data = 0;
//	link = NULL;//不能删除link指向的内存空间，如果链表中删除了指向的后继节点，那么后继节点后的节点就找不到了。
//}
template<typename T> Node<T>* Node<T>::DeleteNextNode()
{
	Node<T>* tmpP = link;
	if (!tmpP)
		tmpP = NULL;
	else
		link = tmpP->link;
	return tmpP;
}
template<typename T> void Node<T>::ShowNode()
{
	//cout << data << endl;//data如果是类数据，需要重置<<
	data.show();
}

//单链表结构
template<typename T> class MyChainList
{
	Node<T>* head, * tail;
public:
	MyChainList();
	~MyChainList();
	void MakeEmpty();
	Node<T>* Find(T data);

	int Length();
	void PrintList();
	void InsertFront(Node<T>* p); //向前生成链表，在表头插入一个结点
	void InsertRear(Node<T>* p); //向后生成链表，在表尾添加一个结点
	void InsertOrder(Node<T>* p); //按升序生成链表
	Node<T>* CreatNode(T data); //创建一个结点（孤立结点）
	Node<T>* DeleteNode(Node<T>* p);

};

//查找、插入（链头、链尾）、升序插入
template<typename T> MyChainList<T>::MyChainList()
{
	head = tail = new Node<T>();
}template<typename T> MyChainList<T>::~MyChainList()
{
	MakeEmpty();
	delete head;
	head = tail = NULL;
}
template<typename T> Node<T>* MyChainList<T>::Find(T data)
{
	Node<T>* tmpP = head->link;
	for (; tmpP; tmpP = tmpP->link)
	{
		if (tmpP->data == data)
		{
			break;
		}
	}
	return tmpP;
}
template<typename T> void MyChainList<T>::MakeEmpty()
{
	Node<T>* tmpP = head->link;
	while (tmpP) {
		Node<T>* p = tmpP;
		tmpP = tmpP->link;
		//p->data = 0;//或者改为data.empty()
		//p->link = NULL;
		//放在node的析构函数中完成
		delete p;
	}
	head->link = NULL;
	tail = head;
}
template<typename T>int MyChainList<T>::Length()
{
	int i = 0;
	Node<T>* tmpP = head->link;
	while (tmpP)
	{
		i++;
		tmpP = tmpP->link;
	}
	return i;
}
template<typename T>void MyChainList<T>::PrintList()
{
	int i = 1;
	Node<T>* tmpP = head->link;
	while (tmpP)
	{
		cout << "第" << i << "个节点的值为：";
		tmpP->ShowNode();
		i++;
		tmpP = tmpP->link;
	}
}
template<typename T> void  MyChainList<T>::InsertFront(Node<T>* p)
{
	if (head->link) {
		p->link = head->link;
	}
	else {
		p->link = NULL;
		tail = p;
	}
	head->link = p;
}
template<typename T> void  MyChainList<T>::InsertRear(Node<T>* p)
{
	tail->link = p;
	tail = p;
}
template<typename T> void  MyChainList<T>::InsertOrder(Node<T>* p)
{
	//插入的结点跟头结点比较，直到找到后继为空，或者第一个大于它的结点，并将该节点放在其前一个结点。
	Node<T>* tmpP = head->link;
	Node<T>* lastP = head;

	while (tmpP) {
		if (p->data < tmpP->data)
		{
			p->link = tmpP;
			lastP->link = p;
			break;
		}
		tmpP = tmpP->link;
		lastP = lastP->link;
	}
	if (!tmpP) {
		lastP->link = p;
		tail = p;
	}
}
template<typename T> Node<T>* MyChainList<T>::CreatNode(T data)
{
	//如果参数data是值传递，那么new node时传入data，会不会由于是引用，随着参数data生命周期结束而出错呢？
	//结果并没有出错。为什么呢？
	//因为在构造函数中并没有保存这个data参数，只是使用了。汗。。
	//所以也可以给CreatNode的参数设置成const &
	Node<T>* node = new Node<T>(data);
	return node;
}
template<typename T> Node<T>* MyChainList<T>::DeleteNode(Node<T>* p)
{
	//如何找到该p结点？如果知道p的上一个结点位置，则不需要进行查找。
	Node<T>* tmpP = head;
	for (; tmpP->link && tmpP->link != p;)
		tmpP = tmpP->link;
	//if (p->link == NULL) tail = tmpP;
	if (tmpP->link == tail) tail = tmpP;
	return tmpP->DeleteNextNode();
}
