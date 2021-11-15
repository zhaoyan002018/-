#include<iostream>
#include"dblist.h"

using namespace std;

int main5()
{
	MyChainDbList<int> dbl1;
	dbNode<int>* tp = NULL;
	int i, a[11] = { 19,11,17,13,7,2,3,5,23,31,29 };
	for (i = 0; i < 11; i++)
		dbl1.Insert(a[i]);
	dbl1.print();
	cout << "双向链表长度为：" << dbl1.length() << endl;

	tp = dbl1.find(7);
	if (tp) cout << "查到并删除的结点数据为：";
	tp->show();
	dbl1.remove(tp);
	cout << "双向链表长度为：" << dbl1.length() << endl;
	dbl1.print();
	cout << "清空链表" << endl;
	dbl1.makeEmpty();
	cout << "双向链表长度为：" << dbl1.length() << endl;

	return 0;
}
