#include"stack.h"

int main6()
{
	int n;
	cout << "请输入栈容器的大小:" << endl;
	cin >> n;
	stack<int> s1(n);
	int i = 0;

	cout << "请输入" << n << "个数字至栈中" << endl;
	while (i < n) {
		int tmp;
		cin >> tmp;
		s1.push(tmp);
		i++;
	}
	s1.traverse();
	if (!s1.push(3)) {
		cout << "栈已满无法push" << endl;
	}

	int e;
	s1.pop(e);
	cout << "取出栈顶数据为" << e << endl;
	s1.makeEmpty();
	if (!s1.pop(e))
	{
		cout << "栈已空无法pop" << endl;
	}
	return 0;
}
