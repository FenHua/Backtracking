/*MaxLoading.cpp : 定义控制台应用程序的入口点。
回溯法是一种选优搜索法，按选优条件向前搜索，以达到目标。但当探索到某一步时，发现原先选择并
不优或达不到目标，就退回一步重新选择，这种走不通就退回再走的技术为回溯法。
回溯法在问题的解空间树中，按深度优先策略，从根结点出发搜索解空间树。算法搜索至解空间树的任意一点时，先判断该结点是否包含问题的解。如果肯定不包含，则跳过对该结点为根
的子树的搜索，逐层向其祖先结点回溯；否则，进入该子树，继续按深度优先策略搜索。
装载问题：如果一个给定装载问题有解，则采用下面的策略可得到最优装载方案。
    (1)首先将第一艘轮船尽可能装满；
    (2)将剩余的集装箱装上第二艘轮船。
    将第一艘轮船尽可能装满等价于选取全体集装箱的一个子集，使该子集中集装箱重量之和最接近C1。由此
可知，装载问题等价于以下特殊的0-1背包问题。
*/
//递归回溯
#include "stdafx.h"
#include<iostream>
using namespace std;

template<class Type>class Loading
{
public:
	void Backtrack(int i);
	int n,//集装箱数
		*x,//当前解
		*bestx;//当前最优解
		Type*w,//集装箱重量数组
		c,//第一艘轮船的载重量
		cw,//当前载重量
		bestw,//当前最优载重量
		r;
};
template<class Type>void Loading<Type>::Backtrack(int i);
template<class Type>Type MaxLoading(Type w[],Type c,int n,int bestx[]);//递归方法

int main()
{
	int n = 3, m;
	int c = 50, c2 = 50;
	int w[4] = { 0, 10, 40, 40 };
	int bestx[4];
	m = MaxLoading(w, c, n, bestx);
	cout << "轮船载重量分别为：" << endl;
	cout << "c(1)=" << c << ",c(2)=" << c2 << endl;
	cout << "待装集装箱的重量分别为：" << endl;
	cout << "w(i)=";
	for (int i = 1; i <= n; i++)
	{
		cout << w[i] << " ";
	}
	cout << endl;
	cout << "回溯选择结果为：" << endl;
	cout << "m(1)=" << m << endl;
	cout << "x(i)=";
	for (int i = 1; i <= n; i++)
	{
		cout << bestx[i] << " ";
	}
	cout << endl;
	int m2 = 0;
	for (int j = 1; j <= n; j++)
	{
		m2 = m2 + w[j] * (1 - bestx[j]);
	}
	cout << "m(2)=" << m2 << endl;
	if (m2 > c2)
	{
		cout << "因为m(2)大于c(2)，所以原问题无解！" << endl;
	}
	return 0;
}

template<class Type>void Loading<Type>::Backtrack(int i)//搜索第i层节点
{
	if (i > n)//到达叶节点
	{
		if (cw > bestw)
		{
			for (int j = 1; j <= n; j++)
			{
				bestx[j] = x[j];//更新最优解
				bestw = cw;
			}
		}
		return;
	}
	r -= w[i];
	if (cw + w[i] <= c)//搜索左子树
	{
		x[i] = 1;
		cw += w[i];
		Backtrack(i + 1);
		cw -= w[i];
	}
	if (cw + r > bestw)
	{
		//搜素右子树
		x[i] = 0;
		Backtrack(i + 1);
	}
	r += w[i];
}
/*
template<class Type>Type MaxLoading(Type w[], Type c, int n, int bestx[])//返回最优载重量
{
	Loading<Type>X;
	//初始化
	X.x = new int[n + 1];
	X.w = w;
	X.c = c;
	X.n = n;
	X.bestx = bestx;
	X.bestw = 0;
	X.cw = 0;
	X.r = 0;//初始化r
	for (int i = 1; i <= n; i++)
	{
		X.r += w[i];
	}
	X.Backtrack(1);
	delete[]X.x;
	return X.bestw;
}
*/
template<class Type>Type MaxLoading(Type w[], Type c, int n, int bestx[])
{
	//迭代回溯法，返回最优载重量以及其相应的解，初始化根节点
	int i = 1;//当前层，x[1:i-1]
	int *x = new int[n + 1];
	Type bestw = 0,//当前最优载重量
		cw = 0,//当前载重量
		r = 0;//剩余集装箱重量
	for (int j = 1; j <= n; j++)
	{
		r += w[j];
	}
	while (true)//搜索子树
	{
		while ((i <= n) && (cw + w[i] <= c))//进入左子树
		{
			r -= w[i];
			cw += w[i];
			x[i] = 1;
			i++;
		}
		if (i > n)//到达叶节点
		{
			for (int j = 1; j <= n; j++)
			{
				bestx[j] = x[j];
			}
			bestw = cw;
		}
		else
		{
			//进入右子树
			r -= w[i];
			x[i] = 0;
			i++;
		}
		while (cw + r <= bestw)//剪枝回溯
		{
			i--;
			while ((i > 0) && (!x[i]))
			{
				r += w[i];
				i--;
			}
			//从右子树返回
			if (i == 0)
			{
				delete[]x;
				return bestw;
			}
			x[i] = 0;
			cw -= w[i];
			i++;
		}
	}
}