/*BT_triangle.cpp : 定义控制台应用程序的入口点。
符号三角形问题要求对于给定的n，计算有多少个不同的符号三角形，使其所含的“+”和“-”的个数相同。
三角形所包含的“+”个数与“-”个数均不超过n*(n+1)/4 。
解向量：用n元组x[1:n]表示符号三角形的第一行。 当x[i]=1时表示符号三角形第一行的第i个符号为"+"；当i=0时，表
示符号三角形第一行的第i个符号为"-"；1<=x<=n。由于x[i]是二值的，所以可以用一棵完全二叉树来表示解空间。
无解的判断：对于给定的n，当n*(n+1)/2为奇数时，显然不存在包含的"+"号个数与"-"号个数相同的符号三角形。
*/

#include "stdafx.h"
#include"iostream"
using namespace std;

class Triangle
{
	friend int Compute(int);
private:
	void Backtrack(int i);
	int n,//第一行符号个数
		half,//n*(n+1)/4
		count,//当前“+”个数
		**p;//符号三角矩阵
	long sum;//已经找到的符号三角形数
};
int Compute(int n);


int main()
{
	for (int n = 1; n <= 10; n++)
	{
		cout << "n=" << n << "时，共有" << Compute(n);
		cout << "个不同的符号三角形！" << endl;
	}
	return 0;
}

void Triangle::Backtrack(int t)
{
	if ((count > half) || (t*(t - 1) / 2 - count > half))
	{
		return;
	}
	if (t > n)
	{
		sum++;
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			p[1][t] = i;//第一个符号
			count += i;//当前“+”个数
			for (int j = 2; j <= t; j++)
			{
				p[j][t - j + 1] = p[j - 1][t - j + 1] ^ p[j - 1][t - j + 2];
				count += p[j][t - j + 1];
			}
			Backtrack(t + 1);
			for (int j = 2; j <= t; j++)
			{
				count -= p[j][t - j + 1];
			}
			count -= i;
		}
	}
}
int Compute(int n)
{
	Triangle X;
	X.n = n;
	X.count = 0;
	X.sum = 0;
	X.half = n*(n + 1) / 2;
	if (X.half % 2 == 1)
		return 0;
	X.half = X.half / 2;
	int**p = new int*[n + 1];
	for (int i = 0; i <= n; i++)
	{
		p[i] = new int[n + 1];
	}
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= n; j++)
			p[i][j] = 0;
	}
	X.p = p;
	X.Backtrack(1);
	for (int i = 0; i <= n; i++)
	{
		delete[]p[i];
	}
	delete[]p;
	p = 0;
	return X.sum;
}