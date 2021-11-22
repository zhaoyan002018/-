#include"queue.h"
#include"chainqueue.h"
int main10()
{
	Quque<int> q1;
	chainQueue<int> q2;
	cout << "请输入要入队元素的个数:" << endl;
	int n;
	cin >> n;
	cout << "请逐个输入元素值:" << endl;
	int i = 0;
	int* arr = new int[n];
	for (; i < n; i++) {
		cin >> arr[i];
	}
	//for (i = 0; i < n; i++) {
	//	if (q1.enQueue(arr[i])) {
	//		cout << "入队成功!" << endl;
	//	}
	//	else {
	//		cout << "入队失败！,从队首出队一个元素再入队。" << endl;
	//		int tmp;
	//		tmp = q1.deQueue();
	//		q1.enQueue(arr[i]);
	//	}
	//}
	//cout << "对队列元素进行一次遍历" << endl;
	//q1.print();

	for (i = 0; i < n; i++) {
		q2.enQueue(arr[i]);
	}
	cout << "对队列元素进行一次遍历" << endl;
	q2.print();
	q2.makeEmpty();
	cout << "清空队列" << endl;
	q2.print();
	cout << "重新写入" << endl;
	q2.enQueue(2);
	q2.enQueue(3);
	q2.print();

	return 0;
}
