#pragma once
#include"list.h"
//基于单链表类的双端队列，可在队列两端插入，一端删除。

template<typename T> class dbendQueue
{
	MyChainList<T> container;
	Node<T>* front, * rear;
public:
	dbendQueue() {
		front = container.head;
		rear = container.tail;
	}
	void enQueueFront(const T& ele);
	void enQueueRear(const T& ele);
	T deQueue();
	void print();
};
template<typename T> void dbendQueue<T>::enQueueFront(const T& ele)
{
	container.InsertFront(container.CreatNode(ele));

}
template<typename T> void dbendQueue<T>::enQueueRear(const T& ele)
{
	container.InsertRear(container.CreatNode(ele));
	rear = container.tail;//移动队尾rear，需要同步容器的tail
}
template<typename T> T dbendQueue<T>::deQueue()
{
	T ele = rear->getData();
	container.DeleteNode(rear);
	rear = container.tail;
	return ele;
}

template<typename T> void dbendQueue<T>::print()
{
	Node<T>* begin = front->getLink();
	while (begin != NULL)
	{
		cout << begin->getData() << endl;
		begin = begin->getLink();

	}
}
