#include<iostream>
#include"list.h"

using namespace std;

class student2 {
	int id;
	string name;
	char sex;
	int age;
	string address;
	float eng, phy, math, electron;
public:
	student2(int = 0, string = "", char = '\0', int = 0, string = "", float = 0.0, float = 0.0, float = 0.0, float = 0.0);
	bool operator<(student2 ele) { return id < ele.id; }
	bool operator>(student2 ele) { return id > ele.id; }
	bool operator!=(student2 ele) { return id != ele.id; }
	bool operator==(student2 ele) { return id == ele.id; }
	void show() {
		cout << id << '\t' << name << '\t' << sex << '\t' << age << '\t' << address << '\t' << eng << '\t' << phy << '\t' << math << '\t' << electron << '\t' << endl;
	}
};
student2::student2(int id, string name, char sex, int age, string address, float eng, float phy, float math, float electron) {
	this->id = id;
	this->name = name;
	this->sex = sex;
	this->age = age;
	this->address = address;
	this->eng = eng;
	this->phy = phy;
	this->math = math;
	this->electron = electron;
}
/*
//由于要使用ShowNode的data.show(),所以下面模板参数为int类型的编译就无法通过。
void func7_5()
{
	Node<int>* P1;
	MyChainList<int>list1, list2;
	int a[16], i, j;
	cout << "请输入16个整数" << endl;
	for (i = 0; i < 16; i++)
		cin >> a[i];
	for (i = 0; i < 16; i++) {
		P1 = list1.CreatNode(a[i]);
		list1.InsertFront(P1);
		P1 = list2.CreatNode(a[i]);
		list2.InsertRear(P1);
	}
	list1.PrintList();
	cout << "list1长度:" << list1.Length() << endl;
	list2.PrintList();
	cout << "请输入一个要求删除的整数" << endl;
	cin >> j;
	P1 = list1.Find(j);

	if (P1 != NULL) {
		P1 = list1.DeleteNode(P1);
		delete P1;
		list1.PrintList();
		cout << "list1长度：" << list1.Length() << endl;
	}
	else
	{
		cout << "未找到" << endl;
	}
	list1.MakeEmpty();
	for (i = 0; i < 16; i++) {
		P1 = list1.CreatNode(a[i]);
		list1.InsertOrder(P1);
	}
	list1.PrintList();

}
*/
void func7_6() {
	const int h = 4;
	int i, j;
	Node<student2>* P1;
	MyChainList<student2>list1, list2;
	student2 n[h] = {
		student2(6004327,"小明",'w',18,"北京路58号",80,85,90,78),
		student2(6004328,"小芳",'m',19,"上海路58号",67,77,99,90),
		student2(6004329,"小亮",'m',19,"广州路58号",88,67,67,82),
		student2(6004330,"小王",'m',19,"济南路58号",90,88,89,70)
	};
	for (i = 0; i < h; i++) {
		P1 = list1.CreatNode(n[i]);
		list1.InsertFront(P1);
		P1 = list2.CreatNode(n[i]);
		list2.InsertRear(P1);
	}
	list1.PrintList();
	cout << "list1的长度为" << list1.Length() << endl;
	list2.PrintList();
	cout << "请输入一个要求删除的学生号" << endl;
	cin >> j;
	P1 = list1.Find(j);
	if (P1 != NULL) {
		P1 = list1.DeleteNode(P1);
		delete P1;
		list1.PrintList();
		cout << "list1长度：" << list1.Length() << endl;
	}
	else {
		cout << "未找到" << endl;
	}
	list1.MakeEmpty();
	for (i = 0; i < h; i++)
	{
		P1 = list1.CreatNode(n[i]);
		list1.InsertOrder(P1);
	}
	list1.PrintList();

}

int main3()
{
	const int num = 5;
	MyChainList<int> l1;
	int arr[num] = { 5,9,2,6,7 };

	//int* text = new int(55);
	//Node<int> t(*text);
	//t.ShowNode();
	//delete text;
	//t.ShowNode();

	/*for (int i = 0; i < num; i++) {
		Node<int>* n = l1.CreatNode(arr[i]);
		l1.InsertOrder(n);
	}
	l1.PrintList();
*/
//func7_5();
	func7_6();
	return 0;
}
