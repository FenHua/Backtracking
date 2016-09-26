/*MaxStamp.cpp : �������̨Ӧ�ó������ڵ㡣
��������
������ҷ�����n�ֲ�ͬ��ֵ����Ʊ�����ҹ涨ÿ���ŷ������ֻ������m����Ʊ��������������Ҫ��
���ڸ�����n��m��ֵ��������Ʊ��ֵ�������ƣ���1���ŷ��Ͽ�����������1��ʼ������Ϊ1�����
�����������䡣���磬��n=5��m=4ʱ����ֵΪ(1,3,11,15,32)��5����Ʊ�����������ʵ������������������1��70��
�������ʹ�ö�̬�滮������������y��ֵ��״̬ת�ƹ��̣���x[i-1]����ȼ��༯S�У�������������x��������
���ʷ�Χ��󣬶�S��Ӱ�������S�е���Ʊ����m�ţ��Ǿ�һֱ��x[i-1],ֱ��S����m����Ʊ��������̻������
�಻ͬ�����ʣ�ȡ�ܲ�����಻ͬ���ʵ�����Ʊ���ٵ��Ǹ�Ԫ�ء�
*/
//������������
#include "stdafx.h"
#include"iostream"
using namespace std;

class Stamp
{
	friend int MaxStamp(int, int, int[]);
private:
	int Bound(int i);
	void Backtrack(int i, int r);
	int n;//��Ʊ��ֵ��
	int m;//ÿ���ŷ��������������Ʊ��
	int maxvalue;//��ǰ����ֵ
	int maxint;//������
	int maxl;//�����Ͻ�
	int *x;//��ǰ��
	int*y;//����������������������Ʊ��
	int*bestx;//��ǰ���Ž�
};
int MaxStamp(int n,int m,int bestx[]);

int main()
{
	int*bestx;
	int n = 5;
	int m = 4;
	cout << "��Ʊ��ֵ��" << n << endl;
	cout << "ÿ���ŷ��������������Ʊ����" << m << endl;
	bestx = new int[n + 1];
	for (int i = 1; i <= n; i++)
	{
		bestx[i] = 0;
	}
	cout << "������ʣ�" << MaxStamp(n, m, bestx) << endl;
	cout << "��ǰ���Ž⣺";
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
	��̬�滮������������y��ֵ��״̬ת�ƹ��̣����ǽ�x[i-1]����ȼ��༯S�У�������������x��������
	���ʷ�Χ��󣬶�s��Ӱ�������s�е���Ʊ����m�ţ��Ǿ�һֱ��x[i-1]��ֱ��S����m����Ʊ��������̻�����ܶ಻ͬ������
	ȡ�ܲ�����಻ͬ���ʵ�����Ʊ���ٵ��Ǹ�Ԫ��
	*/
	for (int j = 0; j <= x[i - 2] * (m - 1); j++)
	{
		if (y[j] < m)
		{
			for (int k = 1; k <= m - y[j]; k++)//k x[i-1]���ظ�����
			{
				if (y[j] + k < y[j + x[i - 1] * k])
				{
					y[j + x[i - 1] * k] = y[j] + k;
				}
			}
		}
	}
	//���y[r]��ֵ��������̬�滮����������Ѿ���ֵ����y[r]<maxint
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