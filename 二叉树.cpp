#include"binaryTree.h"
int main12()
{
	binaryTree<int> bt1;

	//treeNode<int>* ptn;
	//cout << "请输入将要插入二叉树内的数据个数" << endl;
	//int n;
	//cin >> n;
	//cout << "请输入各个数据值:" << endl;
	//int i = 0;
	//int* arr = new int[n];
	//for (; i < n; i++)
	//{
	//	cin >> arr[i];
	//}
	//for (i = 0; i < n; i++)
	//{
	//	ptn = new treeNode<int>(arr[i]);
	//	bt1.insert(ptn);
	//}
	int arr[8] = { 55,29,10,60,88,24,57,12 };
	bt1.createOrderTree(arr, 8);

	//cout << "中序遍历树得到：" << endl;
	//bt1.inOrder();
	//cout << "前序遍历树得到：" << endl;
	//bt1.preOrder();
	//cout << "后序遍历树得到：" << endl;
	//bt1.postOrder();
	//if (bt1.find(10))
	//{
	//	cout << "成功找到10对应的结点" << endl;;
	//}
	//cout << "该树的深度为：" << bt1.getDeep() << endl;
	binaryTree<int> bt2 = bt1;//调用赋值构造函数进行初始化
	binaryTree<int> bt3;
	bt3 = bt2;
	bt1.clear();
	bt3.preOrder();
	cout << "度为2的节点数：" << bt2.getspend2() << "叶子结点数：" << bt2.getleaf();
	return 0;
}
