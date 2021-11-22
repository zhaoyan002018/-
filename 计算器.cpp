#include"chainstack.h"
#include<string>
#include <iomanip> 


template<typename T> class calculator
{
	const int N = 4;
	const int op_oder[4] = { '+','-','*','/' };
	//预先将俩俩运算符的优先级比较关系记录在数组中
	//从第二行开始，首个字符表示哪个新op要压入栈 >表示压入栈中，<表示出栈处理
	const int op[4][4] = {
		//'+','-','*','/',
		'<','<','<','<',
		'<','<','<','<',
		'>','>','<','<',
		'>','>','<','<',
	};
	T(calculator::* op_func[4])(T, T) = { &calculator::addfunc ,&calculator::delfunc ,&calculator::mulfunc ,&calculator::divfunc };//这里使用addfunc必须加上&calculator::
	//指向成员函数指针的用法：除了需要给出返回值类型、参数类型和个数外，还需要给成员函数所属的类
	chainStack<T> number_stack;
	chainStack<int> operator_stack;
public:
	calculator() {}
	~calculator() {}
	void expparse(string& s, chainStack<T>& number_stack, chainStack<int>& operator_stack);
	void col(string& s);
	bool isNumberChar(char);
	T addfunc(T add1, T add2) { return add1 + add2; }
	T delfunc(T del1, T del2) { return del1 - del2; }
	T mulfunc(T mul1, T mul2) { return mul1 * mul2; }
	T divfunc(T div1, T div2) { return div1 / div2; }
};
template<typename T>  bool calculator<T>::isNumberChar(char c)
{
	if (c == '.' || isdigit(c))
		return true;
	return false;
}

//实现+,-,*,/的运算
template<typename T>  void calculator<T>::expparse(string& s, chainStack<T>& number_stack, chainStack<int>& operator_stack)
{
	unsigned int i = 0;
	while (1)
	{

		int c;//逐个字符处理对于浮点数而言有问题
		//找到第一个不是数字组成的字符，作为结束位。
		bool floatFlag = false;

		//数字部分处理
		string numberStr;
		while (i < s.size()) {
			c = s.at(i);
			if (c == '.') {
				floatFlag = true;
				numberStr += c;
			}
			else if (isdigit(c)) {
				numberStr += c;
			}
			else {
				break;
			}
			i++;
		}
		if (floatFlag) {
			double t = stof(numberStr);
			numberStr.clear();
			number_stack.push(t);
			floatFlag = false;
		}
		else {
			int t = stoi(numberStr);
			numberStr.clear();
			number_stack.push(t);
		}

		if (i >= s.size() || c == '=')//当遇到=号或者最后一位数字时结束计算
			break;

		//操作符部分处理
		//新op入栈时，和栈顶的op进行比较，若新op的优先级高，则压入栈中，若小于则从栈顶中取出高优先级的运算符进行一次计算。
		if (operator_stack.isEmpty())
		{
			operator_stack.push(c);
		}
		else {
			int stack_c;
			operator_stack.pop(stack_c);
			int i = 0, j = 0;
			while (op_oder[i] != stack_c)i++;//原本存在栈中的运算符
			while (op_oder[j] != c)j++;
			if (i >= N || j >= N)
			{
				cout << "出现预料之外的操作符" << endl;
				exit(-1);
			}
			if (op[j][i] == '>')
			{
				operator_stack.push(stack_c);
				operator_stack.push(c);
			}
			else
			{
				//处理stack_c 1+2*3/4*5+6
				//取出栈中比要比较的操作符优先级大的操作符，直到遇到比他优先级小的或一致的
				//注意处理顺序，应该从左向右，但取出时是从右向左的。
				//由此遇到俩个问题，1、需要不断pop找到同级或小的操作符，2、需要保存pop出来的操作符
				//发现这样处理很麻烦，不如通过优化运算关系，栈中像+-和*/同级的操作符进行一次运算，比如1+2+3，不能存在，必须保存为3+3。
				//这样上面的算式就变成 1+6/4 -> 1+1*5 ->1 +5+6 
				//可以发现最终opstack栈中只会剩下优先级最低的操作符组成的栈。
				T num1, num2;
				number_stack.pop(num2);
				number_stack.pop(num1);
				T newNum;
				newNum = (this->*op_func[i])(num1, num2);
				number_stack.push(newNum);
				operator_stack.push(c);

			}

		}

		i++;
	}
}


template<typename T>  void calculator<T>::col(string& s)
{
	chainStack<T> number_stack;
	chainStack<int> operator_stack;
	expparse(s, number_stack, operator_stack);
	//解析完成后，注意视觉上是从表达式右边向左边开始解析的。
	int op_i;
	while (operator_stack.pop(op_i))
	{
		int i = 0;
		while (op_oder[i] != op_i)i++;
		T num1, num2, newNum;
		number_stack.pop(num2);
		number_stack.pop(num1);
		newNum = (this->*op_func[i])(num1, num2);
		number_stack.push(newNum);
	}
	T result;
	number_stack.pop(result);
	cout << "结果为：" << result << endl;

}
int main8()
{
	//分为俩步：1、解析表达式（数字和运算符分别各自入栈），2、计算，（出栈）
	calculator<float> c1;
	string exp;
	cout << "请输入运算表达式" << endl;
	cin >> exp;
	c1.col(exp);
	return 0;
}
