#include<iostream>
#include<cstring>
using namespace std;

//动态数组的建立与撤销
void func7_1()
{
	int n;
	char* pc;
	cout << "请输入动态数组的元素个数" << endl;
	cin >> n;
	pc = new char[n];
	//c语言风格：char * pc = (char *)malloc(sizeof(int)*n);
	strncpy_s(pc, n - 1, "动态分配", 9);
	cout << pc << endl;

	char* pc1 = pc;
	delete[]pc1;
}

//多维数组的动态分配
void func7()
{
	//建立三维动态数组
	float(*cp)[30][20];//三级指针
	//cp = new float[15][30][20];
	//cp等效为一个3维数组名。
	float(*bp)[20];//二级指针,指针没有指出边界，忽略了最高维的元素数量
	//bp = new float[20];错误
	cp = new float[1][30][20];
	bp = new float[30][20];
	//俩者占用的内存空间一样，但概念不同

	delete[] bp;
	delete[] cp;
}
int m = 4;//行
int n = 6;//列
void display(double** data) {
	int i, j;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++)
			cout << data[i][j] << '\t';
		cout << endl;
	}
}

void de_allocate(double** data) {
	int i;
	for (i = 0; i < m; i++)delete[] data[i];
	delete[] data;//此时并不能通过data来清空所有空间。data保存的是 double*类型的内存地址。而double*指向的空间需要在此之前释放。
	//func7中释放多维数组因为cp、bp接收的可以看作数组名，指向首个元素的指针，其元素是由所有低维元素构成的数组。而数组的长度被系统记录了起来，与分配空间的首地址相关，应该是类似索引的方式。
	//c语言中free也是如此，malloc给出了具体的大小，但free只需要首地址，系统也是应该根据首地址作为index去找了大小的值，这份索引存放在什么位置呢？
}
//用指针数组方式建立多维数组
void func7_2()
{
	int i, j;
	double** data;
	data = new double* [m];//建立指向组成二维数组各行的指针数组
	//申请m个double *指针类型。data指向首个元素。
	if ((data) == 0) {
		cout << "申请空间失败";
		exit(-1);
	}
	for (j = 0; j < m; j++)
	{
		data[j] = new double[n];
		if (data[j] == 0) {
			cout << "申请空间失败";
			exit(-1);
		}

	}
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			data[i][j] = double(i) * n + j;
	display(data);
	de_allocate(data);
}
int main1()
{
	func7_2();
	return 0;
}
