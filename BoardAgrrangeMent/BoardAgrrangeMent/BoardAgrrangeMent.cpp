/*BoardAgrrangeMent.cpp : �������̨Ӧ�ó������ڵ㡣\
��������
��n���·����������з�ʽ�������n����۵Ļ����С�n���·��Ĳ�ͬ���з�ʽ��Ӧ�ڲ�ͬ�ĵ�·����뷽����
��B={1, 2, ��, n}��n���·��ļ��ϣ�L={N1, N2, ��, Nm}��������n���·�������ɵ�·���m�����ӿ顣Ni��B
��һ���Ӽ�����Ni�еĵ�·����ͬһ������������һ����x��ʾn���·���һ�����У����ڻ���ĵ�i������в�
��ĵ�·������x[i]��x��ȷ���ĵ�·������Density (x)�ܶȶ���Ϊ��Խ���ڵ�·���۵������������
����ƻ���ʱ�����һ��Ĳ��߼�϶�ɵ�·������е��ܶ�ȷ������ˣ���·����������Ҫ����ڸ����ĵ�·����
������(���ӿ�)��ȷ����·���������У�ʹ�������С�ܶȡ�
��·������������NP�����⣬��˲�������ҵ��������Ķ���ʽʱ���㷨�����ǲ��û��ݷ�ϵͳ�����������ռ�
�����������ҳ���·���������С���������B��ʾ���롣B[i][j]��ֵΪ1���ҽ�����·��i�����ӿ�Nj�С���total[j]����
�ӿ�Nj�еĵ�·���������ڵ�·��Ĳ�������x[1:i]����now[j]��x[1:i]����������Nj�еĵ�·�������ɴ˿�֪�����ӿ�
Nj�����߿�Խ���i��i+1���ҽ���now[j]>0��now[j]��=total[j]�������������������i��i+1��������ܶȡ�
*/

#include "stdafx.h"
#include"iostream"
#include<fstream>
using namespace std;

ifstream fin("C:\\Users\\YAN\\Desktop\\data.txt");
class Board
{
	friend int Arrangement(int**B, int n, int m, int bestx[]);
private:
	void Backtrack(int i, int cd);
	int n,//��·����
		m,//���Ӱ���
		*x,//��ǰ��
		*bestx,//��ǰ���Ž�
		bestd,//��ǰ�����ܶ�
		*total,//total[j]=���ӿ�j�ĵ�·����
		*now,//now[j]=��ǰ�������������ӿ�j�ĵ�·����
		**B;//���ӿ�����
};
template<class Type>inline void Swap(Type&a, Type&b);
int Arrangement(int**B, int n, int m, int bestx[]);


int main()
{
	int m = 5, n = 8;
	int bestx[9];
	cout << "m=" << m << ",n=" << n << endl;
	cout << "��ά����B���£�" << endl;
	//����B
	int**B = new int*[n + 1];
	for (int i = 0; i <= n; i++)
	{
		B[i] = new int[m + 1];
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			fin >> B[i][j];
			cout << B[i][j] << " ";
		}
		cout << endl;
	}
	cout << "��ǰ�����ܶ�Ϊ��" << Arrangement(B, n, m, bestx) << endl;
	cout << "��������Ϊ��" << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << bestx[i] << " ";
	}
	cout << endl;
	for (int i = 1; i <= n; i++)
	{
		delete[]B[i];
	}
	delete[]B;
	return 0;
}

void Board::Backtrack(int i, int cd)//���ݷ�����������
{
	if (i == n)
	{
		for (int j = 1; j <= n; j++)
		{
			bestx[j]= x[j];
		}
		bestd = cd;
	}
	else
	{
		for (int j = i; j <= n; j++)
		{
			//ѡ��x[j]Ϊ��һ����·��
			int Id = 0;
			for (int k = 1; k <= m; k++)
			{
				now[k] += B[x[j]][k];
				if ((now[k] > 0) && (total[k] != now[k]))
				{
					Id++;
				}
			}
			//����Id
			{
				Id = cd;
			}
			if (Id < bestd)//��������
			{
				Swap(x[i], x[j]);
				Backtrack(i + 1, Id);
				Swap(x[i], x[j]);
				//�ָ�״̬
				for (int k = 1; k <= m; k++)
				{
					now[k] -= B[x[j]][k];
				}
			}
		}
	}
}
int Arrangement(int**B, int n, int m, int bestx[])
{
	Board X;
	//��ʼ��X
	X.x = new int[n + 1];
	X.total = new int[m + 1];
	X.now = new int[m + 1];
	X.B = B;
	X.n = n;
	X.m = m;
	X.bestx = bestx;
	X.bestd = m + 1;
	//��ʼ��total��now
	for (int i = 1; i <= m; i++)
	{
		X.total[i] = 0;
		X.now[i] = 0;
	}
	//��ʼ��xΪ��λ���в�����total
	for (int i = 1; i <= n; i++)
	{
		X.x[i] = i;
		for (int j = 1; j <= m; j++)
		{
			X.total[j] += B[i][j];
		}
	}
	X.Backtrack(1, 0);//��������
	delete[] X.x;
	delete[]X.total;
	delete[]X.now;
	return X.bestd;
}
template<class Type>inline void Swap(Type&a, Type&b)
{
	Type temp = a;
	a = b;
	b = temp;
}