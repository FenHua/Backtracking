/*Nqueens.cpp : 定义控制台应用程序的入口点。
问题描述：在n×n格的棋盘上放置彼此不受攻击的n个皇后。按照国际象棋的规则，皇后可以攻击与之
处在同一行或同一列或同一斜线上的棋子。n后问题等价于在n×n格的棋盘上放置n个皇后，任何2个皇
后不放在同一行或同一列或同一斜线上。
由此约束条件剪去不满足行、列和斜线约束的子树。程序的递归回溯实现如下：
*/

#include "stdafx.h"
#include<iostream>
#include"math.h"
using namespace std;

class Queen
{
	friend int nQueen(int);
private:
	bool Place(int k);
	//void Backtrack(int t);
	void Backtrack(void);
	int n,//皇后个数
		*x;//当前解
	long sum;//当前已经找到的可行方案数
};


int main()
{
	int n = 4, m;
	cout << n << "n皇后问题的解为：" << endl;
	m = nQueen(n);
	cout << n << "皇后问题共有";
	cout << m << "不同的解！" << endl;
	return 0;
}

bool Queen::Place(int k)
{
	for (int j = 1; j < k; j++)
	{
		if ((abs(k - j) == abs(x[j] - x[k])) || (x[j] == x[k]))
		{
			return false;
		}
	}
	return true;
}
/*
void Queen::Backtrack(int t)//t扩展的是行
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
		//搜索第t行的每一列是否有元素满足要求
		for (int i = 1; i <= n; i++)
		{
			x[t] = i;
			if (Place(t))
			{
				Backtrack(t + 1);
			}
		}
	}
}
*/
int nQueen(int n)
{
	Queen X;
	X.n = n;
	X.sum = 0;
	int *p = new int[n + 1];
	for (int i = 0; i <= n; i++)
	{
		p[i] = 0;
	}
	X.x = p;
	//X.Backtrack(1);
	X.Backtrack();
	delete[]p;
	return X.sum;
}

//非递归回溯
void Queen::Backtrack()
{
	x[1] = 0;
	int k = 1;
	while (k > 0)
	{
		x[k] += 1;
		while ((x[k] <= n) && (!(Place(k))))//寻找能够放置皇后的位置
		{
			x[k] += 1;
		}
		if (x[k] <= n)//找到位置
		{
			if (k == n)
			{
				for (int i = 1; i <= n; i++)
				{
					cout << x[i] << " ";
				}
				cout << endl;
				sum++;
			}
			else
			{
				k++;
				x[k] = 0;
			}
		}
		else
		{
			k--;
		}
	}

}