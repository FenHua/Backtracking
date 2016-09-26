/*FlowShop.cpp : 定义控制台应用程序的入口点。
批处理作业调度问题要从n个作业的所有排列中找出具有最小完成时间和的作业调度，所以如图，批处理作业调度问题的解空间是一颗排列树。按照回溯法搜索排列树的算法框
架，设开始时x=[1,2,……n]是所给的n个作业，则相应的排列树由x[1:n]的所有排列构成。
*/

#include "stdafx.h"
#include"iostream"
using namespace std;

class FlowShop
{
	friend int Flow(int**M,int n,int bestx[]);
private:
	void Backtrack(int i);
	int**M,//各作业所需的处理时间
		*x,//当前作业调度
		*bestx,//当前最优作业调度
		*f2,//机器2的完成时间
		f1,//机器1完成处理的时间
		f,//完成的时间和
		bestf,//当前最优值
		n;//作业数
};
int Flow(int **M, int n, int bestx[]);
template<class Type>inline void Swap(Type&a, Type&b);


int main()
{
	int n = 3, bf;
	int M1[4][3] = { { 0, 0, 0 }, { 0, 2, 1 }, { 0, 3, 1 }, { 0, 2, 3 } };
	int**M = new int*[n + 1];
	for (int i = 0; i <= n; i++)
	{
		M[i] = new int[3];
	}
	cout << "M(i,j)值如下：" << endl;
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			M[i][j] = M1[i][j];
		}
	}
	int bestx[4];
	for (int i = 1; i <= n; i++)
	{
		cout << "(";
		for (int j = 1; j < 3; j++)
		{
			cout << M[i][j] << " ";
		}
		cout << ")";
	}
	bf = Flow(M, n, bestx);
	for (int i = 0; i <= n; i++)
	{
		delete[]M[i];
	}
	delete[]M;
	cout << "最优值是：" << bf << endl;
	cout << "最优调度是：";
	for (int i = 1; i <= n; i++)
	{
		cout << bestx[i] << " ";
	}
	cout << endl;
	return 0;
}

void FlowShop::Backtrack(int i)
{
	if (i > n)
	{
		for (int j = 1; j <= n; j++)
		{
			bestx[j] = x[j];//当前作业调度赋值给最优调度
		}
		bestf = f;//完成时间和
	}
	else
	{
		for (int j = i; j <= n; j++)
		{
			f1 += M[x[j]][1];
			f2[i] = ((f2[i - 1] > f1) ? f2[i - 1] : f1) + M[x[j]][2];//机器2执行的是机器1已完成的作业，所以i-1
			f += f2[i];
			if (f < bestf)//剪枝
			{
				Swap(x[i], x[j]);
				Backtrack(i + 1);
				Swap(x[i], x[j]);
			}
			f1 -= M[x[j]][1];
			f -= f2[i];
		}
	}
}
template <class Type>inline void Swap(Type &a, Type &b)
{
	Type temp = a;
	a = b;
	b = temp;
}
int Flow(int**M, int n, int bestx[])
{
	int ub = 30000;
	FlowShop X;
	X.n = n;
	X.x = new int[n + 1];
	X.f2 = new int[n + 1];
	X.M = M;
	X.bestx = bestx;
	X.bestf = ub;
	X.f1 = 0;
	X.f = 0;
	for (int i = 0; i <= n; i++)
	{
		X.f2[i] = 0, X.x[i] = i;
	}
	X.Backtrack(1);
	delete[] X.x;
	delete[]X.f2;
	return X.bestf;
}
/* 由于算法Backtrack在每一个节点处耗费O(1)计算时间，故在最坏情况下，整个算法计算时间复杂性为O(n!)。*/