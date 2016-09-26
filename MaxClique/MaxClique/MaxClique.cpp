/*MaxClique.cpp : 定义控制台应用程序的入口点。
问题描述
给定无向图G=(V, E)，其中V是非空集合，称为顶点集；E是V中元素构成的无序二元组的集合，称为边
集，无向图中的边均是顶点的无序对，无序对常用圆括号“( )”表示。如果U∈V，且对任意两个顶点u，
v∈U有(u, v)∈E，则称U是G的完全子图(完全图G就是指图G的每个顶点之间都有连边)。G的完全子图U是
G的团当且仅当U不包含在G的更大的完全子图中。G的最大团是指G中所含顶点数最多的团。
算法设计
无向图G的最大团和最大独立集问题都可以用回溯法在O(n2^n)的时间内解决。图G的最大团和最大独立
集问题都可以看做是图G的顶点集V的子集选取问题。因此可以用子集树来表示问题的解空间。首先设最
大团为一个空团，往其中加入一个顶点，然后依次考虑每个顶点，查看该顶点加入团之后仍然构成一个团，
如果可以，考虑将该顶点加入团或者舍弃两种情况，如果不行，直接舍弃，然后递归判断下一顶点。对于
无连接或者直接舍弃两种情况，在递归前，可采用剪枝策略来避免无效搜索。为了判断当前顶点加入团之后
是否仍是一个团，只需要考虑该顶点和团中顶点是否都有连接。程序中采用了一个比较简单的剪枝策略，即
如果剩余未考虑的顶点数加上团中顶点数不大于当前解的顶点数，可停止继续深度搜索，否则继续深度递归
当搜索到一个叶结点时，即可停止搜索，此时更新最优解和最优值。
*/
//最大团，回溯法
#include "stdafx.h"
#include<iostream>
#include<fstream>
using namespace std;

const int N = 5;//图G的顶点数
ifstream fin("C:\\Users\\YAN\\Desktop\\data.txt");
class Clique
{
	friend int MaxClique(int**, int[], int);
private:
	void Backtrack(int i);
	int **a,//图G的邻接矩阵
		n,//图G的顶点数
		*x,//当前解
		*bestx,//当前最优解
		cn,//当前顶点数
		bestn;//当前最大顶点数
};
int MaxClique(int**a, int v[], int n);

int main()
{
	int v[N + 1];
	int **a = new int*[N + 1];
	for (int i = 1; i <= N; i++)
	{
		a[i] = new int[N + 1];
	}
	cout << "图G的邻接矩阵为：" << endl;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			fin >> a[i][j];
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << "图G的最大团解向量为：" << endl;//先执行函数再完成输出
	cout << "图G的最大团顶点个数为：" << MaxClique(a, v, N) << endl;
	for (int i = 1; i <= N; i++)
	{
		delete[]a[i];
	}
	delete[]a;
	return 0;
}

void Clique::Backtrack(int i)
{
	if (i > n)
	{
		//到达了叶节点
		for (int j = 1; j <= n; j++)
		{
			bestx[j] = x[j];
			cout << x[j] << " ";
		}
		cout << endl;
		bestn = cn;
		return;
	}
	//检查顶点i与当前团的连接
	int OK = 1;
	for (int j = 1; j < i; j++)
	{
		if (x[j] && (a[i][j] == 0))
		{
			OK = 0;//i与j不相连
			break;
		}
	}
	if (OK)
	{
		//进入左子树
		x[i] = 1;
		cn++;
		Backtrack(i + 1);
		x[i] = 0;
		cn--;
	}
	if (cn + n - i >= bestn)
	{
		//进入右子树
		x[i] = 0;
		Backtrack(i + 1);
	}
}
int MaxClique(int**a, int v[], int n)
{
	Clique Y;
	//初始化Y
	Y.x = new int[n + 1];
	Y.a = a;
	Y.n = n;
	Y.cn = 0;
	Y.bestn = 0;
	Y.bestx = v;
	Y.Backtrack(1);
	delete[]Y.x;
	return Y.bestn;
}