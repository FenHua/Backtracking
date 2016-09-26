/* MColoring.cpp : 定义控制台应用程序的入口点。
算法设计
考虑所有的图，讨论在至多使用m种颜色的情况下，可对一给定的图着色的所有不同方法。通过回溯的方法，不
断的为每一个节点着色，在前面n-1个节点都合法的着色之后，开始对第n个节点进行着色，这时候枚举可用的m
个颜色，通过和第n个节点相邻的节点的颜色，来判断这个颜色是否合法，如果找到那么一种颜色使得第n个节点
能够着色，那么说明m种颜色的方案是可行的。
用m种颜色为无向图G=(V,E)着色，其中，V的顶点个数为n，可以用一个n元组x=(x1,x2,…,xn)来描述图的一种可能
着色，其中，xi∈{1, 2, …, m}，(1≤i≤n)表示赋予顶点i的颜色。例如，5元组(1, 2, 2, 3, 1)表示对具有5个顶点的无向
图（a）的一种着色，顶点A着颜色1，顶点B着颜色2，顶点C着颜色2，如此等等。如果在n元组X中，所有相邻顶点
都不会着相同颜色，就称此n元组为可行解，否则为无效解。容易看出，每个顶点可着颜色有m种选择，n个顶点就有
mn种不同的着色方案，问题的解空间是一棵高度为n的完全m叉树，这里树高度的定义为从根节点到叶子节点的路径
的长度。每个分支结点，都有m个儿子结点。最底层有mn个叶子结点。例如，表示用3种颜色为3个顶点的图着色的状
态空间树。如图所示，对第i（i>=1）层上的每个顶点，从其父节点到该节点的边上的标号表示顶点i着色的颜色编号。
*/

#include "stdafx.h"
#include"iostream"
#include<fstream>
using namespace std;

const int N = 5;//图的顶点数
const int M =3;//色彩数
ifstream fin("C:\\Users\\YAN\\Desktop\\data.txt");
class Color
{
	friend int mColoring(int, int, int**);
private:
	bool Ok(int k);
	void Backtrack(int t);
	int n,//图的顶点数
		m,//可用的颜色数
		**a,//图的邻接矩阵
		*x;//当前解
	long sum;//当前已经找到的可m着色的方案数
};
int mColoring(int n, int m, int**a);


int main()
{
	int**a = new int*[N + 1];
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
	cout << "图G的着色方案如下：" << endl;
	cout << "当m=" << M << "时，图G的可行着色方案数目为：" << mColoring(N, M, a) << endl;
	for (int i = 1; i <= N; i++)
	{
		delete[]a[i];
	}
	delete[]a;
	return 0;
}

void Color::Backtrack(int t)
{
	if (t > n)
	{
		sum++;
		for (int i = 1; i <= n; i++)
		{
			cout << x[i] << " ";
		}
		cout << endl;
	}
	else
	{
		for (int i = 1; i <= m; i++)
		{
			x[t] = i;//t出给i色
			if (Ok(t))
			{
				Backtrack(t + 1);
			}
			x[t] = 0;
		}
	}
}
bool Color::Ok(int k)//检查颜色的可用性
{
	for (int j = 1; j <= n; j++)
	{
		if ((a[k][j] == 1) && (x[j] == x[k]))
		{
			return false;
		}
	}
	return true;
}
int mColoring(int n, int m, int**a)
{
	Color X;
	//初始化
	X.n = n;
	X.m = m;
	X.a = a;
	X.sum = 0;
	int*p = new int[n + 1];
	for (int i = 0; i <= n; i++)
	{
		p[i] = 0;
	}
	X.x = p;
	X.Backtrack(1);
	delete[]p;
	return X.sum;
}