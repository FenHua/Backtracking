/*FlowShop.cpp : �������̨Ӧ�ó������ڵ㡣
��������ҵ��������Ҫ��n����ҵ�������������ҳ�������С���ʱ��͵���ҵ���ȣ�������ͼ����������ҵ��������Ľ�ռ���һ�������������ջ��ݷ��������������㷨��
�ܣ��迪ʼʱx=[1,2,����n]��������n����ҵ������Ӧ����������x[1:n]���������й��ɡ�
*/

#include "stdafx.h"
#include"iostream"
using namespace std;

class FlowShop
{
	friend int Flow(int**M,int n,int bestx[]);
private:
	void Backtrack(int i);
	int**M,//����ҵ����Ĵ���ʱ��
		*x,//��ǰ��ҵ����
		*bestx,//��ǰ������ҵ����
		*f2,//����2�����ʱ��
		f1,//����1��ɴ����ʱ��
		f,//��ɵ�ʱ���
		bestf,//��ǰ����ֵ
		n;//��ҵ��
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
	cout << "M(i,j)ֵ���£�" << endl;
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
	cout << "����ֵ�ǣ�" << bf << endl;
	cout << "���ŵ����ǣ�";
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
			bestx[j] = x[j];//��ǰ��ҵ���ȸ�ֵ�����ŵ���
		}
		bestf = f;//���ʱ���
	}
	else
	{
		for (int j = i; j <= n; j++)
		{
			f1 += M[x[j]][1];
			f2[i] = ((f2[i - 1] > f1) ? f2[i - 1] : f1) + M[x[j]][2];//����2ִ�е��ǻ���1����ɵ���ҵ������i-1
			f += f2[i];
			if (f < bestf)//��֦
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
/* �����㷨Backtrack��ÿһ���ڵ㴦�ķ�O(1)����ʱ�䣬���������£������㷨����ʱ�临����ΪO(n!)��*/