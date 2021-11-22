#pragma once
#include<iostream>
#include<algorithm>
using namespace std;
//二叉树模板类

template<typename T> class treeNode
{
	//节点包含左右俩个孩子指针。
	T info;
	treeNode<T>* lchild, * rchild;
public:
	treeNode(T pinfo = 0) { info = pinfo; lchild = rchild = NULL; }
	//取得结点数据、修改结点数据、取得左子树、取得右子树、设置左子树，设置右子树。
	T getInfo();
	void setInfo(const T& pinfo);
	treeNode<T>* getLchild();
	treeNode<T>* getRchild();
	void setLchild(treeNode<T>* plchild);
	void setRchild(treeNode<T>* prchild);
	bool operator<(const treeNode& p) { return this->info < p.info; }
	template<typename T> friend class binaryTree;
};
template<typename T> T treeNode<T>::getInfo()
{
	return info;
}
template<typename T> void treeNode<T>::setInfo(const T& pinfo)
{
	info = pinfo;
}
template<typename T> treeNode<T>* treeNode<T>::getLchild()
{
	return lchild;
}
template<typename T> treeNode<T>* treeNode<T>::getRchild()
{
	return rchild;
}
template<typename T> void treeNode<T>::setLchild(treeNode<T>* plchild)
{
	lchild = plchild;
}
template<typename T> void treeNode<T>::setRchild(treeNode<T>* prchild)
{
	rchild = prchild;
}

template<typename T> class binaryTree
{
	treeNode<T>* root;//head用于指向根结点，不包含任何数据
	int spend2Num;
	int leafNum;
	void inOrderTraverse(treeNode<T>* proot);
	void preOrderTraverse(treeNode<T>* proot);
	void postOrderTraverse(treeNode<T>* proot);
	void insertOrder(treeNode<T>*& proot, treeNode<T>* pnode);//proot为指针类型的引用，才能修改proot原本的值，为指针传递的地址
	void insertOrder_iter(treeNode<T>* pnode);

	void statSpend2(treeNode<T>* proot);
	void statleaf(treeNode<T>* proot);
	int getDeepFunc(treeNode<T>*& proot);

	void clearTree(treeNode<T>*& proot);
public:
	binaryTree(treeNode<T>* proot = NULL) { spend2Num = leafNum = 0; root = proot; }
	~binaryTree() {
		clearTree(root);
	}
	binaryTree(const binaryTree<T>&);
	binaryTree<T>& operator=(const binaryTree<T>&);

	void inOrder() { inOrderTraverse(root); }
	void preOrder() { preOrderTraverse(root); }
	void postOrder() { postOrderTraverse(root); }
	void insert(treeNode<T>* pnode) {
		//insertOrder(root, pnode); 
		insertOrder_iter(pnode);
	}
	treeNode<T>* find(T pinfo);

	void clear() { clearTree(root); }//注意此时传递的是root中保存的地址，而函数外root的值不变，要想同时改变指针本身的值，需要传递引用 
	void createOrderTree(T* arr, int n);
	void preOrderFunc(const treeNode<T>* proot, binaryTree<T>*, void (*func)(binaryTree<T>*, T info));

	int getDeep() { return getDeepFunc(root); }
	int getspend2() { spend2Num = 0; statSpend2(root); return spend2Num; }
	int getleaf() { leafNum = 0; statleaf(root); return leafNum; }
	friend void cstSetfunc(binaryTree<T>* pt, T info);
};

template<typename T> void binaryTree<T>::createOrderTree(T* arr, int n)
{
	int i = 0;
	while (i < n)
	{
		insert(new treeNode<T>(arr[i]));
		i++;
	}

}

template<typename T> void binaryTree<T>::insertOrder(treeNode<T>*& proot, treeNode<T>* pnode)
{
	//二叉排序树的特点是，比根结点小的结点都在左子树，比根结点大的都在右子树,但并不意味着位于根结点左子数第i层的数要大于第i-1层的子树
	if (!proot) {
		proot = pnode;////proot为指针类型的引用，才能修改proot原本的值，为指针时proot保存的是传递的地址，而无法修改指向原本实参处的值
		return;
	}
	if (proot->info > pnode->info) {
		insertOrder(proot->lchild, pnode);
	}
	else {
		insertOrder(proot->rchild, pnode);
	}
}
template<typename T> void binaryTree<T>::insertOrder_iter(treeNode<T>* pnode)
{
	treeNode<T>** nodetmp = &root;

	while (1)
	{
		if (!*nodetmp) {
			*nodetmp = pnode;
			return;
		}
		if ((*nodetmp)->info > pnode->info) {
			nodetmp = &((*nodetmp)->lchild);
		}
		else {
			nodetmp = &((*nodetmp)->rchild);
		}
	}
}

template<typename T> treeNode<T>* binaryTree<T>::find(T pinfo)
{
	treeNode<T>* nodetmp = root;
	while (1)
	{
		if (!nodetmp) {
			return NULL;
		}
		if (nodetmp->info == pinfo)
		{
			return nodetmp;
		}
		else if (nodetmp->info > pinfo) {
			nodetmp = nodetmp->lchild;
		}
		else {
			nodetmp = nodetmp->rchild;
		}
	}
}

template<typename T> void binaryTree<T>::inOrderTraverse(treeNode<T>* proot)
{
	if (!proot)
	{
		return;
	}
	inOrderTraverse(proot->lchild);
	cout << proot->info << endl;
	inOrderTraverse(proot->rchild);
}
template<typename T> void binaryTree<T>::preOrderTraverse(treeNode<T>* proot)
{
	if (!proot)
	{
		return;
	}

	cout << proot->info << endl;
	preOrderTraverse(proot->lchild);
	preOrderTraverse(proot->rchild);
}
template<typename T> void binaryTree<T>::postOrderTraverse(treeNode<T>* proot)
{
	if (!proot)
	{
		return;
	}
	postOrderTraverse(proot->lchild);
	postOrderTraverse(proot->rchild);
	cout << proot->info << endl;
}

template<typename T> void binaryTree<T>::clearTree(treeNode<T>*& proot)
{
	if (!proot)
	{
		return;
	}
	clearTree(proot->lchild);
	clearTree(proot->rchild);
	delete proot;//删除的是proot指向的空间
	proot = 0;//发现如果只是delete，proot的值并不会=NULL，所以要手动给指针赋NULL
	//采取后序的办法，才能保证每一处根结点最后删除,以及其左右子树能够被索引。

}

template<typename T> void binaryTree<T>::statSpend2(treeNode<T>* proot)
{
	//返回值，返回当前proot下子树的个数
	if (!proot)
	{
		return;
	}
	if (proot->lchild && proot->rchild)
		spend2Num++;

	statSpend2(proot->lchild);
	statSpend2(proot->rchild);

}
template<typename T> void binaryTree<T>::statleaf(treeNode<T>* proot)
{
	if (!proot)
	{
		return;
	}
	if (!proot->lchild && !proot->rchild)
		leafNum++;

	statleaf(proot->lchild);
	statleaf(proot->rchild);
}

template<typename T> void binaryTree<T>::preOrderFunc(const treeNode<T>* proot, binaryTree<T>* pt, void (*func)(binaryTree<T>* pt, T info))
{
	if (!proot)
	{
		return;
	}

	func(pt, proot->info);
	preOrderFunc(proot->lchild, pt, func);
	preOrderFunc(proot->rchild, pt, func);
}
template<typename T> void cstSetfunc(binaryTree<T>* pt, T info)
{
	pt->insert(new treeNode<T>(info));
}
template<typename T> binaryTree<T>::binaryTree(const binaryTree<T>& pbTree)
{
	preOrderFunc(pbTree.root, this, &cstSetfunc);
	//复制构造函数，还可以使用另一个递归方式创建，TODO
}
template<typename T> binaryTree<T>& binaryTree<T>::operator=(const binaryTree<T>& pbTree)
{
	cout << "进入二叉树的=运算符的重载函数" << endl;
	preOrderFunc(pbTree.root, this, &cstSetfunc);
	return *this;
}

template<typename T>int binaryTree<T>::getDeepFunc(treeNode<T>*& proot)
{
	if (!proot)
	{
		return 0;
	}
	//改为进入叶子节点就返回，而不是叶子节点下的俩个空孩子，因为只需要+1,
	if (!proot->lchild && !proot->rchild)
		return 1;
	int ld, rd;
	ld = getDeepFunc(proot->lchild);
	rd = getDeepFunc(proot->rchild);
	return max(ld, rd) + 1;//1的作用，体现在每次回归后深度+1；
}
