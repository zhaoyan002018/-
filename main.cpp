#include"dbendQueue.h"
#include"stack.h"

int main()
{
	/*习题7.9
	class dbendQueue < int> dbq1;
	dbq1.enQueueFront(1);
	dbq1.enQueueFront(2);
	dbq1.enQueueFront(3);
	dbq1.enQueueRear(4);
	dbq1.enQueueRear(5);
	dbq1.print();
	dbq1.deQueue();
	cout << "从队尾出队一个元素" << endl;
	dbq1.print();*/

	/*习题7.8
	stack<int> s1(5);
	int arr[11] = { 1,2,3,4,5,6,7,8,9,10,11 };
	for (int i = 0; i < 11; i++)
	{
		s1.push(arr[i]);
	}
	s1.traverse();*/

	MyChainList<int> cl1, cl2;
	int arr[10] = { 1,1,3,4,5,6,7,7,9,9 };
	for (int i = 0; i < 10; i++)
	{
		cl1.InsertRear(cl1.CreatNode(arr[i]));


	}
	int arr2[5] = { 10,11,15,16,18 };
	for (int i = 0; i < 5; i++)
	{
		cl2.InsertRear(cl2.CreatNode(arr2[i]));

	}

	cl1.PrintList();
	cl1.deleteDataNode(1);
	cl1.deleteDataNode(9);
	cl1.PrintList();
	Node<int>* n1 = cl1.getNode(3);
	cout << "链表第3位元素值是：" << n1->getData() << endl;
	cout << "链表逆转后：" << endl;
	cl1.reverseList();
	cl1.PrintList();
	//MyChainList<int>* cl3 = &(cl1 + cl2);//注意，返回的是引用，但又不想调用赋值构造函数，因为这样就无法释放+产生的对象了，难不成其生命周期会随着+表达式结束而结束？
	//MyChainList<int> cl3;
	//cl3 = cl1 + cl2;//+表达式
	//cout << "cl1+cl2=" << endl;
	//cl3.PrintList();


	MyChainList<int> cl4;
	int arr3[5] = { 12,13,17,19,20 };
	for (int i = 0; i < 5; i++)
	{
		cl4.InsertRear(cl4.CreatNode(arr3[i]));

	}
	MyChainList<int> cl5;
	cl5.orderMerge(cl2, cl4);
	cout << "俩个有序表分别为：" << endl;
	cl2.PrintList();
	cout << "以及" << endl;
	cl4.PrintList();
	cout << "俩个有序链表合并后：" << endl;
	cl5.PrintList();

}
