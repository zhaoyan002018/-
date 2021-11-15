#include<iostream>
#include<cstring>

using namespace std;

//自由存储区对象的分配和释放
class CGoods {
	string Name;
	int Amount;
	float Price;
	float Total_value;
public:
	CGoods() { cout << "调用默认构造函数" << endl; }
	CGoods(string name, int amount, float price) {
		cout << "调用三参数构造函数" << endl;
		Name = name;
		Amount = amount;
		Price = price;
		Total_value = price * amount;
	}
	~CGoods() {
		cout << "调用析构函数" << endl;
	}
};

void func7_3()
{
	int n;
	CGoods* pc, * pc1, * pc2;
	pc = new CGoods("夏利2000", 10, 118000);
	pc1 = new CGoods();
	cout << "输入商品类数组元素个数" << endl;
	cin >> n;
	pc2 = new CGoods[n];

	delete pc;
	delete pc1;
	delete[]pc2;
}


//深复制、自定义析构函数以释放动态分配的内存，自定义复制构造函数、复制赋值操作符实现深复制。
class student {
	char* pName;
public:
	student();
	student(const char* pname);
	student(student& s);
	~student();
	student& operator=(student& s);
};
student::student()
{
	cout << "Constructor";
	pName = NULL;
	cout << "默认" << endl;
}
student::student(const char* pname) {
	cout << "Constructor";
	if (pName = new char[strlen(pname) + 1])
		strcpy_s(pName, strlen(pname) + 1, pname);
	cout << pName << endl;
}
student::student(student& s) {
	cout << "Copy Constructor";
	if (s.pName) {
		if (pName = new char[strlen(s.pName) + 1])strcpy_s(pName, strlen(s.pName) + 1, s.pName);
		cout << pName << endl;
	}
	else pName = NULL;
}
student::~student() {
	cout << "Destructor";
	if (pName)cout << pName << endl;
	delete[]pName;
}
student& student::operator=(student& s) {
	cout << "Copy Assign Operator";
	delete[] pName;
	if (s.pName) {
		if (pName = new char[strlen(s.pName) + 1])strcpy_s(pName, strlen(s.pName) + 1, s.pName);
		cout << pName << endl;
	}
	else pName = NULL;
	return *this;//返回一个表达式的值，因为this本身是指针，返回类型为引用的话，必须*this
}

void func7_4()
{
	student s1("小明"), s2("二明"), s3;
	student s4 = s1;//复制构造
	s3 = s2;//赋值运算符重载


}


int main2()
{
	func7_4();
	return 0;
}
