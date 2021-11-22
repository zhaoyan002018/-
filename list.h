
#include<iostream>
using namespace std;
//单链表类型模板

template<typename T> class Node
{
	T data;
	Node<T>* link;
public:
	//如果没有对外的接口，可想而知就如同C语言中用struct结构保存node一样，只需要数据类型。
	Node();
	//~Node();
	Node(const T& pdata);

	Node<T>* DeleteNextNode();//刪除后继节点，并返回指向该节点的指针
	void ShowNode();
	T getData() { return data; }
	Node<T>* getLink() { return link; }
	void setLink(Node<T>* pnode) { link = pnode; }
	template<typename T> friend class MyChainList;//声明友元类，可以直接访问私有成员
};

template<typename T> Node<T>::Node()
{
	data = 0;//如果data是类，应该用其自身的清空接口。
	link = NULL;
}
template<typename T> Node<T>::Node(const T& pdata)
{
	//cout << "进入 node 构造函数中,data地址为：" << &pdata << endl;
	data = pdata;//data赋值，并没有依赖pdata的声明周期。
	link = NULL;
}
//析构时不能写入的原因？
//template<typename T> Node<T>::~Node()
//{
//	data = 0;
//	link = NULL;//不能删除link指向的内存空间，如果链表中删除了指向的后继节点，那么后继节点后的节点就找不到了。
//}
template<typename T> Node<T>* Node<T>::DeleteNextNode()
{
	Node<T>* tmpP = link;
	if (!tmpP)
		tmpP = NULL;
	else
		link = tmpP->link;
	return tmpP;
}
template<typename T> void Node<T>::ShowNode()
{
	cout << data << endl;//data如果是类数据，需要重置<<
	//data.show();
}

//单链表结构
template<typename T> class MyChainList
{
	Node<T>* head, * tail;
public:
	MyChainList();
	~MyChainList();
	MyChainList(const MyChainList<T>&);
	MyChainList<T>& operator=(const MyChainList<T>&);
	//实现俩个链表对象的连接，但要去除数据域中相同的结点，可用友元函数，即俩个参数，第一个参数不一定为自身。

	//MyChainList<T> operator+(const MyChainList<T>&);

	//由于模板类的友元函数，不属于该类，但如果用类的模板参数T来声明友元函数，则会造成依赖，和定义有出入。
	template<typename U>
	friend MyChainList<U> operator+(const MyChainList<U>&, const MyChainList<U>&);//假设链表对象不需要有序。那么每次插入，都需要从链表头部向后遍历一遍。

	void MakeEmpty();
	Node<T>* Find(T data);

	int Length();
	void PrintList();
	void InsertFront(Node<T>* p); //向前生成链表，在表头插入一个结点
	void InsertRear(Node<T>* p); //向后生成链表，在表尾添加一个结点
	void InsertOrder(Node<T>* p); //按升序生成链表
	Node<T>* CreatNode(T data); //创建一个结点（孤立结点）
	Node<T>* DeleteNode(Node<T>* p);

	void deleteDataNode(const T& pdata);//删除链表中所有数据域为指定值的结点
	Node<T>* getNode(int K);//取出链表中第K个元素。
	void reverseList();//链表翻转
	void orderMerge(const MyChainList<T>&, const MyChainList<T>&);//俩个有序链表合并为一个有序链表，归并排序？

	template<typename T>friend class dbendQueue;
};

//查找、插入（链头、链尾）、升序插入
template<typename T> MyChainList<T>::MyChainList()
{
	head = tail = new Node<T>();
}
template<typename T> MyChainList<T>::~MyChainList()
{
	MakeEmpty();
	delete head;
	head = tail = NULL;
}
template<typename T> Node<T>* MyChainList<T>::Find(T data)
{
	Node<T>* tmpP = head->link;
	for (; tmpP; tmpP = tmpP->link)
	{
		if (tmpP->data == data)
		{
			break;
		}
	}
	return tmpP;
}
template<typename T> void MyChainList<T>::MakeEmpty()
{
	Node<T>* tmpP = head->link;
	while (tmpP) {
		Node<T>* p = tmpP;
		tmpP = tmpP->link;
		//p->data = 0;//或者改为data.empty()
		//p->link = NULL;
		//放在node的析构函数中完成
		delete p;
	}
	head->link = NULL;
	tail = head;
}
template<typename T>int MyChainList<T>::Length()
{
	int i = 0;
	Node<T>* tmpP = head->link;
	while (tmpP)
	{
		i++;
		tmpP = tmpP->link;
	}
	return i;
}
template<typename T>void MyChainList<T>::PrintList()
{
	int i = 1;
	Node<T>* tmpP = head->link;
	while (tmpP)
	{
		cout << "第" << i << "个节点的值为：";
		tmpP->ShowNode();
		i++;
		tmpP = tmpP->link;
	}
}
template<typename T> void  MyChainList<T>::InsertFront(Node<T>* p)
{
	if (head->link) {
		p->link = head->link;
	}
	else {
		p->link = NULL;
		tail = p;
	}
	head->link = p;
}
template<typename T> void  MyChainList<T>::InsertRear(Node<T>* p)
{
	tail->link = p;
	tail = p;
}
template<typename T> void  MyChainList<T>::InsertOrder(Node<T>* p)
{
	//插入的结点跟头结点比较，直到找到后继为空，或者第一个大于它的结点，并将该节点放在其前一个结点。
	Node<T>* tmpP = head->link;
	Node<T>* lastP = head;

	while (tmpP) {
		if (p->data < tmpP->data)
		{
			p->link = tmpP;
			lastP->link = p;
			break;
		}
		tmpP = tmpP->link;
		lastP = lastP->link;
	}
	if (!tmpP) {
		lastP->link = p;
		tail = p;
	}
}
template<typename T> Node<T>* MyChainList<T>::CreatNode(T data)
{
	//如果参数data是值传递，那么new node时传入data，会不会由于是引用，随着参数data生命周期结束而出错呢？
	//结果并没有出错。为什么呢？
	//因为在构造函数中并没有保存这个data参数，只是使用了。汗。。
	//所以也可以给CreatNode的参数设置成const &
	Node<T>* node = new Node<T>(data);
	return node;
}
template<typename T> Node<T>* MyChainList<T>::DeleteNode(Node<T>* p)
{
	//如何找到该p结点？如果知道p的上一个结点位置，则不需要进行查找。
	Node<T>* tmpP = head;
	for (; tmpP->link && tmpP->link != p;)
		tmpP = tmpP->link;
	//if (p->link == NULL) tail = tmpP;
	if (tmpP->link == tail) tail = tmpP;
	return tmpP->DeleteNextNode();
}
//课后习题
template<typename T> void MyChainList<T>::deleteDataNode(const T& pdata)
{
	Node<T>* pnode = head->link, * last = head;

	while (pnode)
	{
		if (pnode->data == pdata)
		{
			last->link = pnode->link;
			delete pnode;
			pnode = last->link;
		}
		else {
			last = pnode;
			pnode = pnode->link;
		}

	}
}
template<typename T> Node<T>* MyChainList<T>::getNode(int K)
{
	int i = 1;
	Node<T>* tmpP = head->link;
	while (tmpP) {
		if (i == K) {
			return tmpP;
		}
		tmpP = tmpP->link;
		i++;
	}
	return NULL;


}
template<typename T>  MyChainList<T>::MyChainList(const MyChainList<T>& plist)
{
	cout << "调用复制构造函数" << endl;//注意调用复制构造函数后，不会去调用构造函数了。所以要兼具默认构造函数的功能
	head = tail = new Node<T>();
	//对链表结点挨个进行深复制
	Node<T>* pnode = plist.head->link;
	Node<T>* tnode = this->head;

	for (; pnode; pnode = pnode->link)
	{
		tnode = tail = tnode->link = CreatNode(pnode->data);//可见不需用给node类编写复制构造函数，其效用CreatNode成员就足够
	}
}
template<typename T> void MyChainList<T>::reverseList()
{
	//不删除结点、也不另建一个链表来取代、通过改变指针域的连接方向。
	Node<T>* tnode = head->link, * nextTmp, * lastTmp;//三个工作指针，一个用于偏移遍历链表，一个保存上一次的结点，一个保存下一次访问的结点
	tail = tnode;
	lastTmp = NULL;

	while (tnode)
	{
		nextTmp = tnode->link;	//保存原本结点的下一个方向
		tnode->link = lastTmp;	//结点指针翻转
		lastTmp = tnode;		//保存当前结点位置，作为下一次翻转的方向
		tnode = nextTmp;
	}
	head->link = lastTmp;
}
template<typename T> MyChainList<T>& MyChainList<T>::operator=(const MyChainList<T>& plist)
{
	//注意如果+表达式返回类型不是&，那么这里也需要用&来直接操作返回的临时对象。
	cout << "调用=运算符重载函数" << endl;
	Node<T>* pnode = plist.head->link;
	Node<T>* tnode = this->head;
	//现将自身链表清空
	MakeEmpty();

	for (; pnode; pnode = pnode->link)
	{
		tnode = tail = tnode->link = CreatNode(pnode->data);//可见不需用给node类编写复制构造函数，其效用CreatNode成员就足够
	}

	//如果+重载函数返回的是&,那么必须释放+表达式传来的新对象。
	/*MyChainList<T>* p = &plist;
	delete p;*/

	return *this;
}

//template<typename T> MyChainList<T> MyChainList<T>::operator+(const MyChainList<T>& plist)
//{//注意必须给俩个引用类型的参数加上const，原因是无法对可以作为左值的实参进行类型转换，p137
//
//	//假设链表对象不需要有序。那么每次插入，都需要从链表头部向后遍历一遍。
//	//连接俩个链表对象后生成的新链表，与原本俩个链表无关。
//	cout << "进入+运算符重载" << endl;
//	//MyChainList<T>* newList = new MyChainList<T>(*this);//调用复制构造函数
//	MyChainList<T> newList(*this);//创建局部链表，生命周期应该为表达式的生命周期，
//	Node<T>* pnode = plist.head->link;
//	for (; pnode; pnode = pnode->link)
//	{
//		Node<T>* nnode = newList.head->link;
//		bool rep = false;
//		for (; nnode; nnode = nnode->link)
//		{
//			if (nnode->data == pnode->data)
//			{
//				rep = true;
//				break;
//			}
//		}
//		if (!rep) {
//			newList.tail = newList.tail->link = newList.CreatNode(pnode->data);
//		}
//		rep = false;
//	}
//	///return newList;
//	//程序返回后newList会析构吗？会，所以应该返回一个指针，让=表达式来释放。因此不允许写a+b;的表达式出来
//	//TODO 可优化的是，如果返回值不设置成&，调用一次复制拷贝，而在=中则不需要释放，返回的链表生命周期也会结束。
//	//那么要问的就是，return 返回值的生命周期什么时候结束呢？
//	//比如int a= func();其中func返回一个int值，这个值在给a赋值后，去哪了？流程是，函数内的变量赋值给这个无名的临时变量，而这个无名的临时变量在传递给外面要被赋值的对象后结束。如果外面没有要被赋值的对象，那么这个临时变量还会产生吗？猜测应该会产生，但随即消失，是谁释放的呢？
//	//书上73页，给出，临时变量在主调用函数中的表达式执行结束后撤销。
//	//return *newList;//使用&的问题在于，必须要进行手动释放，如果释放在=函数中进行，那么就无法实现多个+运算，比如a=b+c+d;因为c+d产生的临时对象无法释放了。
//	return newList;
//}


//使用友元函数, 会产生链接错误

template<typename U> MyChainList<U> operator+(const MyChainList<U>& plist1, const MyChainList<U>& plist2)
{//注意必须给俩个引用类型的参数加上const，原因是无法对可以作为左值的实参进行类型转换，p137


	//假设链表对象不需要有序。那么每次插入，都需要从链表头部向后遍历一遍。
	//连接俩个链表对象后生成的新链表，与原本俩个链表无关。
	cout << "进入+运算符重载" << endl;
	//MyChainList<T>* newList = new MyChainList<T>(plist1);//调用复制构造函数
	MyChainList<U> newList(plist1);//创建局部链表，生命周期应该为表达式的生命周期，
	Node<U>* pnode = plist2.head->getLink();
	for (; pnode; pnode = pnode->getLink())
	{

		//Node<U>* nnode = newList.head->link;//无法直接访问node类型的私有成员，因为虽然本函数是list类的友元函数，但却不是node的友元函数，无法直接访问。
		Node<U>* nnode = newList.head->getLink();
		bool rep = false;
		for (; nnode; nnode = nnode->getLink())
		{
			if (nnode->getData() == pnode->getData())
			{
				rep = true;
				break;
			}
		}
		if (!rep) {
			newList.tail->setLink(newList.CreatNode(pnode->getData()));
			newList.tail = newList.tail->getLink();
		}
		rep = false;
	}
	///return newList;
	//程序返回后newList会析构吗？会，所以应该返回一个指针，让=表达式来释放。因此不允许写a+b;的表达式出来
	//TODO 可优化的是，如果返回值不设置成&，调用一次复制拷贝，而在=中则不需要释放，返回的链表生命周期也会结束。
	//那么要问的就是，return 返回值的生命周期什么时候结束呢？
	//比如int a= func();其中func返回一个int值，这个值在给a赋值后，去哪了？流程是，函数内的变量赋值给这个无名的临时变量，而这个无名的临时变量在传递给外面要被赋值的对象后结束。如果外面没有要被赋值的对象，那么这个临时变量还会产生吗？猜测应该会产生，但随即消失，是谁释放的呢？
	//书上73页，给出，临时变量在主调用函数中的表达式执行结束后撤销。
	//return *newList;//使用&的问题在于，必须要进行手动释放，如果释放在=函数中进行，那么就无法实现多个+运算，比如a=b+c+d;因为c+d产生的临时对象无法释放了。
	return newList;
}

template<typename T> void MyChainList<T>::orderMerge(const MyChainList<T>& plist1, const MyChainList<T>& plist2)
{
	//MyChainList<T>* newList = new MyChainList<T>();
	Node<T>* pnode = plist1.head->link;
	Node<T>* tnode = plist2.head->link;
	while (pnode && tnode)
	{
		T dataTmp;
		if (pnode->data < tnode->data) {
			dataTmp = pnode->data;
			pnode = pnode->link;
		}
		else {
			dataTmp = tnode->data;
			tnode = tnode->link;
		}
		this->tail = this->tail->link = this->CreatNode(dataTmp);
	}
	while (pnode)
	{
		this->tail = this->tail->link = this->CreatNode(pnode->data);
		pnode = pnode->link;
	}
	while (tnode)
	{
		this->tail = this->tail->link = this->CreatNode(tnode->data);
		tnode = tnode->link;
	}
}
