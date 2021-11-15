#include"chainstack.h"

int main7()
{
	cout << "请输入要键入链栈的数据个数" << endl;
	int n;
	cin >> n;
	chainStack<int> cs1;
	int i = 0;

	while (i < n)
	{
		int data;
		cin >> data;
		cs1.push(data);
		i++;
	}
	cs1.traverse();

	int e;

	if (cs1.pop(e))
	{
		cout << "pop出的结果为" << e;
	}
	else {
		cout << "pop失败" << endl;
	}

	cs1.makeEmpty();
	if (cs1.pop(e))
	{
		cout << "pop出的结果为" << e;
	}
	else {
		cout << "pop失败" << endl;
	}
	return 0;
}
