/*TSP.cpp : 定义控制台应用程序的入口点。
问题分析
旅行售货员问题的解空间是一棵排列树。对于排列树的回溯法与生成1,2,……n的所有排列的递归算法Perm类似
。开始时x=[1,2,……n],则相应的排列树有x[1:n]的所有排列构成。
在递归算法Backtrack中，当i=n时，当前扩展节点是排列树的叶节点的父节点。此时算法检测图G是否存在一条
从顶点x[n-1]到顶点x[n]的边和一条从顶点x[n]到顶点1的边。如果这两条边都存在，则找到一条旅行员售货回路
。此时，算法还需要判断这条回路的费用是否优于已找到的当前最优回流的费用bestc。如果是，则必须更新当
前最优值bestc和当前最优解bestx。
当i<n时，当前扩展节点位于排列树的第i-1层。图G中存在从顶点x[i-1]到顶点x[i]的边时，x[1:i]构成图G的一条路
径，且当x[1:i]的费用小于当前最优值时算法进入树的第i层，否则将剪去相应的子树。
*/

#include "stdafx.h"
#include"iostream"
#include<fstream>
using namespace std;

ifstream fin("C:\\Users\\YAN\\Desktop\\data.txt");
const int N = 4;//顶点数
template<class Type>class Traveling
{
	template<class Type>friend Type TSP(Type**a, int n);
private:
	void Backtrack(int i);
	int n,//图G的顶点数
		*x,//当前解
		*bestx;//当前最优解
	Type**a,//图G 的邻接矩阵
		cc,//当前的费用
		bestc;//当前最优值
	int NoEdge;//无边标记
};
template<class Type>inline void Swap(Type&a, Type&b);
template<class Type>Type TSP(Type**a, int n);

int main()
{
	cout << "图的顶点个数为："<<N<< endl;
	int**a = new int*[N + 1];
	for (int i = 0; i <= N; i++)
	{
		a[i] = new int[N + 1];
	}
	cout << "图的邻接矩阵为：" << endl;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			fin >> a[i][j];
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << "最短回路长度为：" << TSP(a, N) << endl;
	for (int i = 0; i <= N; i++)
	{
		delete[]a[i];
	}
	delete[]a;
	return 0;
}

template<class Type>void Traveling<Type>::Backtrack(int i)
{
	if (i == n)
	{
		if ((a[x[n - 1]][x[n]] != 0) && (a[x[n]][1] != 0) && (cc + a[x[n - 1]][x[n]] + a[x[n]][1] < bestc || bestc == 0))
		{
			for (int j = 1; j <= n; j++)
				bestx[j] = x[j];
			bestc = cc + a[x[n - 1]][x[n]] + a[x[n]][1];
		}
	}
	else
	{
		for (int j = i; j <= n; j++)
		{
			//是否可进入x[j]子树
			if ((a[x[i - 1]][x[j]] != 0) && (cc + a[x[i - 1]][x[i]] < bestc || bestc == 0))
			{
				//搜索子树
				Swap(x[i], x[j]);//之所以交换x，因为初始化时x已经赋值（顺序）
				cc += a[x[i - 1]][x[i]];//当前费用累加和
				Backtrack(i + 1);//排列向右扩展，排列树向下一层扩展
				cc -= a[x[i - 1]][x[i]];
				Swap(x[i], x[j]);
			}
		}
	}
}
template<class Type>Type TSP(Type**a, int n)
{
	Traveling<Type>Y;
	Y.n = n;
	Y.x = new int[n + 1];
	Y.bestx = new int[n + 1];
	for (int i = 1; i <= n; i++)
	{
		Y.x[i] = i;
	}
	Y.a = a;
	Y.cc = 0;
	Y.bestc = 0;
	Y.NoEdge = 0;
	Y.Backtrack(2);
	cout << "最短回路为：" << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << Y.bestx[i] << "-->";
	}
	cout << Y.bestx[1] << endl;
	delete[]Y.x;
	delete[]Y.bestx;
	return Y.bestc;
}
template<class Type>inline void Swap(Type&a, Type&b)
{
	Type temp = a;
	a = b;
	b = temp;
}