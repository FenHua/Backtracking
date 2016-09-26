/*MaxStamp.cpp : 定义控制台应用程序的入口点。
问题描述
假设国家发行了n种不同面值的邮票，并且规定每张信封上最多只允许贴m张邮票。连续邮资问题要求
对于给定的n和m的值，给出邮票面值的最佳设计，在1张信封上可贴出从邮资1开始，增量为1的最大
连续邮资区间。例如，当n=5和m=4时，面值为(1,3,11,15,32)的5种邮票可以贴出邮资的最大连续邮资区间是1到70。
考虑如果使用动态规划方法计算数组y的值，状态转移过程：将x[i-1]加入等价类集S中，将会引起数组x能贴出的
邮资范围变大，对S的影响是如果S中的邮票不满m张，那就一直贴x[i-1],直到S中有m张邮票，这个过程会产生很
多不同的邮资，取能产生最多不同邮资的用邮票最少的那个元素。
*/
//连续邮资问题
#include "stdafx.h"
#include"iostream"
using namespace std;

class Stamp
{
	friend int MaxStamp(int, int, int[]);
private:
	int Bound(int i);
	void Backtrack(int i, int r);
	int n;//邮票面值数
	int m;//每张信封最多允许贴的邮票数
	int maxvalue;//当前最优值
	int maxint;//大整数
	int maxl;//邮资上界
	int *x;//当前解
	int*y;//贴出各种邮资所需最少邮票数
	int*bestx;//当前最优解
};
int MaxStamp(int n,int m,int bestx[]);

int main()
{
	int*bestx;
	int n = 5;
	int m = 4;
	cout << "邮票面值数" << n << endl;
	cout << "每张信封最多允许贴的邮票数：" << m << endl;
	bestx = new int[n + 1];
	for (int i = 1; i <= n; i++)
	{
		bestx[i] = 0;
	}
	cout << "最大邮资：" << MaxStamp(n, m, bestx) << endl;
	cout << "当前最优解：";
	for (int i = 1; i <= n; i++)
	{
		cout << bestx[i] << " ";
	}
	cout << endl;
	return 0;
}

void Stamp::Backtrack(int i, int r)
{
	/*
	动态规划方法计算数组y的值。状态转移过程：考虑将x[i-1]加入等价类集S中，将会引起数组x能贴出的
	邮资范围变大，对s的影响是如果s中的邮票不满m张，那就一直贴x[i-1]，直到S中有m张邮票，这个过程会产生很多不同的邮资
	取能产生最多不同邮资的用邮票最少的那个元素
	*/
	for (int j = 0; j <= x[i - 2] * (m - 1); j++)
	{
		if (y[j] < m)
		{
			for (int k = 1; k <= m - y[j]; k++)//k x[i-1]的重复次数
			{
				if (y[j] + k < y[j + x[i - 1] * k])
				{
					y[j + x[i - 1] * k] = y[j] + k;
				}
			}
		}
	}
	//如果y[r]的值在上述动态规划运算过程中已经赋值，则y[r]<maxint
	while (y[r] < maxint)
	{
		r++;
	}
	if (i>n)
	{
		if (r - 1 > maxvalue)
		{
			maxvalue = r - 1;
			for (int j = 1; j <= n; j++)
			{
				bestx[j] = x[j];
			}
		}
		return;
	}
	int*z = new int[maxl + 1];
	for (int k = 1; k <= maxl; k++)
	{
		z[k] = y[k];
	}
	for (int j = x[i - 1] + 1; j <= r; j++)
	{
		x[i] = j;
		Backtrack(i + 1, r);
		for (int k = 1; k <= maxl; k++)
		{
			y[k] = z[k];
		}
	}
	delete[]z;
}
int MaxStamp(int n, int m, int bestx[])
{
	Stamp X;
	int maxint = 32767;
	int maxl = 1500;
	X.n = n;
	X.m = m;
	X.maxvalue = 0;
	X.maxint = maxint;
	X.maxl = maxl;
	X.bestx = bestx;
	X.x = new int[n + 1];
	X.y = new int[maxl + 1];
	for (int i = 0; i <= n; i++)
	{
		X.x[i] = 0;
	}
	for (int i = 1; i < maxl; i++)
	{
		X.y[i] = maxint;
	}
	X.x[1] = 1;
	X.y[0] = 0;
	X.Backtrack(2, 1);
	delete[]X.x;
	delete[]X.y;
	return X.maxvalue;
}