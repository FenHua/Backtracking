/*Nqueens.cpp : �������̨Ӧ�ó������ڵ㡣
������������n��n��������Ϸ��ñ˴˲��ܹ�����n���ʺ󡣰��չ�������Ĺ��򣬻ʺ���Թ�����֮
����ͬһ�л�ͬһ�л�ͬһб���ϵ����ӡ�n������ȼ�����n��n��������Ϸ���n���ʺ��κ�2����
�󲻷���ͬһ�л�ͬһ�л�ͬһб���ϡ�
�ɴ�Լ��������ȥ�������С��к�б��Լ��������������ĵݹ����ʵ�����£�
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
	int n,//�ʺ����
		*x;//��ǰ��
	long sum;//��ǰ�Ѿ��ҵ��Ŀ��з�����
};


int main()
{
	int n = 4, m;
	cout << n << "n�ʺ�����Ľ�Ϊ��" << endl;
	m = nQueen(n);
	cout << n << "�ʺ����⹲��";
	cout << m << "��ͬ�Ľ⣡" << endl;
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
void Queen::Backtrack(int t)//t��չ������
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
		//������t�е�ÿһ���Ƿ���Ԫ������Ҫ��
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

//�ǵݹ����
void Queen::Backtrack()
{
	x[1] = 0;
	int k = 1;
	while (k > 0)
	{
		x[k] += 1;
		while ((x[k] <= n) && (!(Place(k))))//Ѱ���ܹ����ûʺ��λ��
		{
			x[k] += 1;
		}
		if (x[k] <= n)//�ҵ�λ��
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