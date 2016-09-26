/*BT_triangle.cpp : �������̨Ӧ�ó������ڵ㡣
��������������Ҫ����ڸ�����n�������ж��ٸ���ͬ�ķ��������Σ�ʹ�������ġ�+���͡�-���ĸ�����ͬ��
�������������ġ�+�������롰-��������������n*(n+1)/4 ��
����������nԪ��x[1:n]��ʾ���������εĵ�һ�С� ��x[i]=1ʱ��ʾ���������ε�һ�еĵ�i������Ϊ"+"����i=0ʱ����
ʾ���������ε�һ�еĵ�i������Ϊ"-"��1<=x<=n������x[i]�Ƕ�ֵ�ģ����Կ�����һ����ȫ����������ʾ��ռ䡣
�޽���жϣ����ڸ�����n����n*(n+1)/2Ϊ����ʱ����Ȼ�����ڰ�����"+"�Ÿ�����"-"�Ÿ�����ͬ�ķ��������Ρ�
*/

#include "stdafx.h"
#include"iostream"
using namespace std;

class Triangle
{
	friend int Compute(int);
private:
	void Backtrack(int i);
	int n,//��һ�з��Ÿ���
		half,//n*(n+1)/4
		count,//��ǰ��+������
		**p;//�������Ǿ���
	long sum;//�Ѿ��ҵ��ķ�����������
};
int Compute(int n);


int main()
{
	for (int n = 1; n <= 10; n++)
	{
		cout << "n=" << n << "ʱ������" << Compute(n);
		cout << "����ͬ�ķ��������Σ�" << endl;
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
			p[1][t] = i;//��һ������
			count += i;//��ǰ��+������
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