/* Knap.cpp : 定义控制台应用程序的入口点。
问题解析：0-1背包问题是子集选取问题。0-1 背包问题的解空间可以用子集树表示。在搜索解空间树时，只要其左
儿子节点是一个可行节点，搜索就进入左子树。当右子树中有可能含有最优解时，才进入右子树搜索。否则，将右子
树剪去。设r是当前剩余物品价值总和，cp是当前价值；bestp是当前最优价值。当cp+r<=bestp时，可剪去右子树。
计算右子树上界的更好的方法是将剩余物品依次按其单位价值排序，然后依次装入物品，直至装不下时，再装入物品
一部分而装满背包。
在实现时，由Bound计算当前节点处的上界。类Knap的数据成员记录解空间树中的节点信息，以减少参数传递调用所
需要的栈空间。在解空间树的当前扩展节点处，仅要进入右子树时才计算上界Bound,以判断是否可将右子树剪去。进入
左子树时不需要计算上界，因为上界预期父节点的上界相同。
*/

#include "stdafx.h"
#include<iostream>
using namespace std;

template<class Typew, class Typep>class Knap
{
	template<class Typew, class Typep>friend Typep Knapsack(Typep[], Typew[], Typew, int);
private:
	Typep Bound(int i);
	void Backtrack(int i);
	Typew c;//背包容量
	int n;//物品数
	Typew*w;//物品重量数组
	Typep *p;//物品价值数组
	Typew cw;//当前重量
	Typep cp;//当前价值
	Typep bestp;//当前最后价值
};
template<class Typew, class Typep>Typep Knapsack(Typep p[], Typew w[], Typew c, int n);
template<class Type>inline void Swap(Type&a, Type&b);
template<class Type>void BubbleSort(Type a[], int n);

int main()
{
	int n = 4;//物品数  
	int c = 7;//背包容量  
	int p[] = { 0, 9, 10, 7, 4 };//物品价值 下标从1开始  
	int w[] = { 0, 3, 5, 2, 1 };//物品重量 下标从1开始
	cout << "背包容量为：" << c << endl;
	cout << "物品重量和价值分别为：" << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << "(" << w[i] << "," << p[i] << ")";
	}
	cout << endl;
	cout << "背包能装下的最大价值为" << Knapsack(p, w, c, n) << endl;
	return 0;
}

template<class Typew, class Typep>void Knap<Typew, Typep>::Backtrack(int i)
{
	if (i > n)//到达叶子节点
	{
		bestp = cp;//当前的价值赋值给最后价值量
		return;
	}
	if (cw + w[i] <= c)//进入左子树
	{
		cw += w[i];
		cp += p[i];
		Backtrack(i + 1);
		cw -= w[i];
		cp -= p[i];
	}
	if (Bound(i + 1) > bestp)//进入右子树
	{
		Backtrack(i + 1);
	}
}
template<class Typew, class Typep>Typep Knap<Typew, Typep>::Bound(int i)//计算上界
{
	Typew cleft = c - cw;//剩余容量
	Typep b = cp;
	//以物品单位重量价值递减装入物品
	while ((i <= n) && (w[i] <= cleft))
	{
		cleft -= w[i];
		b += p[i];
		i++;
	}
	//装满背包
	if (i <= n)
	{
		b += p[i] * (cleft / w[i]);
	}
	return b;
}
class Object
{
	template<class Typew, class Typep>friend Typep Knapsack(Typep[], Typew[], Typew, int);
private:
	int ID;
	float d;
public:
	int operator<=(Object a)const
	{
		return (d >= a.d);
	}
};
template<class Typew, class Typep>Typep Knapsack(Typep p[], Typew w[] ,Typew c, int n)
{
	//为Knap::Backtrack初始化
	Typew W = 0;
	Typep P = 0;
	Object*Q = new Object[n];
	for (int i = 1; i <= n; i++)
	{
		Q[i - 1].ID = i;
		Q[i - 1].d = 1.0*p[i] / w[i];
		P += p[i];
		W += w[i];
	}
	if (W<= c)//装入所有物品
	{
		return P;
	}
	//根据物品单位重量价值排序
	BubbleSort(Q, n);
	Knap<Typew, Typep>K;
	K.p = new Typep[n + 1];
	K.w = new Typew[n + 1];
	for (int i = 1; i <= n; i++)
	{
		K.p[i] = p[Q[i - 1].ID];
		K.w[i] = w[Q[i - 1].ID];
	}
	K.cp = 0;
	K.cw = 0;
	K.c = c;
	K.n = n;
	K.bestp = 0;
	K.Backtrack(1);//回溯搜索
	delete[]Q;
	delete[]K.w;
	delete[]K.p;
	return K.bestp;
}
template<class Type>void BubbleSort(Type a[], int n)
{
	int i, j;
	for (j = 0; j < n - 1; j++)
	{
		for (i = 0; i < n - 1 - j; i++)
		{
			if (a[i+1]<=a[i])
			{
				Swap(a[i], a[i + 1]);
			}
		}
	}
}
template <class Type>inline void Swap(Type &a, Type&b)
{
	Type temp = a;
	a = b;
	b = temp;
}