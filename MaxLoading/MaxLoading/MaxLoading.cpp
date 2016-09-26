/*MaxLoading.cpp : �������̨Ӧ�ó������ڵ㡣
���ݷ���һ��ѡ������������ѡ��������ǰ�������ԴﵽĿ�ꡣ����̽����ĳһ��ʱ������ԭ��ѡ��
���Ż�ﲻ��Ŀ�꣬���˻�һ������ѡ�������߲�ͨ���˻����ߵļ���Ϊ���ݷ���
���ݷ�������Ľ�ռ����У���������Ȳ��ԣ��Ӹ�������������ռ������㷨��������ռ���������һ��ʱ�����жϸý���Ƿ��������Ľ⡣����϶����������������Ըý��Ϊ��
������������������������Ƚ����ݣ����򣬽����������������������Ȳ���������
װ�����⣺���һ������װ�������н⣬���������Ĳ��Կɵõ�����װ�ط�����
    (1)���Ƚ���һ���ִ�������װ����
    (2)��ʣ��ļ�װ��װ�ϵڶ����ִ���
    ����һ���ִ�������װ���ȼ���ѡȡȫ�弯װ���һ���Ӽ���ʹ���Ӽ��м�װ������֮����ӽ�C1���ɴ�
��֪��װ������ȼ������������0-1�������⡣
*/
//�ݹ����
#include "stdafx.h"
#include<iostream>
using namespace std;

template<class Type>class Loading
{
public:
	void Backtrack(int i);
	int n,//��װ����
		*x,//��ǰ��
		*bestx;//��ǰ���Ž�
		Type*w,//��װ����������
		c,//��һ���ִ���������
		cw,//��ǰ������
		bestw,//��ǰ����������
		r;
};
template<class Type>void Loading<Type>::Backtrack(int i);
template<class Type>Type MaxLoading(Type w[],Type c,int n,int bestx[]);//�ݹ鷽��

int main()
{
	int n = 3, m;
	int c = 50, c2 = 50;
	int w[4] = { 0, 10, 40, 40 };
	int bestx[4];
	m = MaxLoading(w, c, n, bestx);
	cout << "�ִ��������ֱ�Ϊ��" << endl;
	cout << "c(1)=" << c << ",c(2)=" << c2 << endl;
	cout << "��װ��װ��������ֱ�Ϊ��" << endl;
	cout << "w(i)=";
	for (int i = 1; i <= n; i++)
	{
		cout << w[i] << " ";
	}
	cout << endl;
	cout << "����ѡ����Ϊ��" << endl;
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
		cout << "��Ϊm(2)����c(2)������ԭ�����޽⣡" << endl;
	}
	return 0;
}

template<class Type>void Loading<Type>::Backtrack(int i)//������i��ڵ�
{
	if (i > n)//����Ҷ�ڵ�
	{
		if (cw > bestw)
		{
			for (int j = 1; j <= n; j++)
			{
				bestx[j] = x[j];//�������Ž�
				bestw = cw;
			}
		}
		return;
	}
	r -= w[i];
	if (cw + w[i] <= c)//����������
	{
		x[i] = 1;
		cw += w[i];
		Backtrack(i + 1);
		cw -= w[i];
	}
	if (cw + r > bestw)
	{
		//����������
		x[i] = 0;
		Backtrack(i + 1);
	}
	r += w[i];
}
/*
template<class Type>Type MaxLoading(Type w[], Type c, int n, int bestx[])//��������������
{
	Loading<Type>X;
	//��ʼ��
	X.x = new int[n + 1];
	X.w = w;
	X.c = c;
	X.n = n;
	X.bestx = bestx;
	X.bestw = 0;
	X.cw = 0;
	X.r = 0;//��ʼ��r
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
	//�������ݷ������������������Լ�����Ӧ�Ľ⣬��ʼ�����ڵ�
	int i = 1;//��ǰ�㣬x[1:i-1]
	int *x = new int[n + 1];
	Type bestw = 0,//��ǰ����������
		cw = 0,//��ǰ������
		r = 0;//ʣ�༯װ������
	for (int j = 1; j <= n; j++)
	{
		r += w[j];
	}
	while (true)//��������
	{
		while ((i <= n) && (cw + w[i] <= c))//����������
		{
			r -= w[i];
			cw += w[i];
			x[i] = 1;
			i++;
		}
		if (i > n)//����Ҷ�ڵ�
		{
			for (int j = 1; j <= n; j++)
			{
				bestx[j] = x[j];
			}
			bestw = cw;
		}
		else
		{
			//����������
			r -= w[i];
			x[i] = 0;
			i++;
		}
		while (cw + r <= bestw)//��֦����
		{
			i--;
			while ((i > 0) && (!x[i]))
			{
				r += w[i];
				i--;
			}
			//������������
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