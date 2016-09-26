/* Knap.cpp : �������̨Ӧ�ó������ڵ㡣
���������0-1�����������Ӽ�ѡȡ���⡣0-1 ��������Ľ�ռ�������Ӽ�����ʾ����������ռ���ʱ��ֻҪ����
���ӽڵ���һ�����нڵ㣬�����ͽ����������������������п��ܺ������Ž�ʱ���Ž������������������򣬽�����
����ȥ����r�ǵ�ǰʣ����Ʒ��ֵ�ܺͣ�cp�ǵ�ǰ��ֵ��bestp�ǵ�ǰ���ż�ֵ����cp+r<=bestpʱ���ɼ�ȥ��������
�����������Ͻ�ĸ��õķ����ǽ�ʣ����Ʒ���ΰ��䵥λ��ֵ����Ȼ������װ����Ʒ��ֱ��װ����ʱ����װ����Ʒ
һ���ֶ�װ��������
��ʵ��ʱ����Bound���㵱ǰ�ڵ㴦���Ͻ硣��Knap�����ݳ�Ա��¼��ռ����еĽڵ���Ϣ���Լ��ٲ������ݵ�����
��Ҫ��ջ�ռ䡣�ڽ�ռ����ĵ�ǰ��չ�ڵ㴦����Ҫ����������ʱ�ż����Ͻ�Bound,���ж��Ƿ�ɽ���������ȥ������
������ʱ����Ҫ�����Ͻ磬��Ϊ�Ͻ�Ԥ�ڸ��ڵ���Ͻ���ͬ��
*/

#include "stdafx.h"
#include<iostream>
using namespace std;

template<class Typew, class Typep>class Knap
{
	template<class Typew, class Typep>friend Typep Knapsack(Typep[], Typew[], Typew, int);
private:
	Typep Bound(int i);
	void Backtrack(int i);
	Typew c;//��������
	int n;//��Ʒ��
	Typew*w;//��Ʒ��������
	Typep *p;//��Ʒ��ֵ����
	Typew cw;//��ǰ����
	Typep cp;//��ǰ��ֵ
	Typep bestp;//��ǰ����ֵ
};
template<class Typew, class Typep>Typep Knapsack(Typep p[], Typew w[], Typew c, int n);
template<class Type>inline void Swap(Type&a, Type&b);
template<class Type>void BubbleSort(Type a[], int n);

int main()
{
	int n = 4;//��Ʒ��  
	int c = 7;//��������  
	int p[] = { 0, 9, 10, 7, 4 };//��Ʒ��ֵ �±��1��ʼ  
	int w[] = { 0, 3, 5, 2, 1 };//��Ʒ���� �±��1��ʼ
	cout << "��������Ϊ��" << c << endl;
	cout << "��Ʒ�����ͼ�ֵ�ֱ�Ϊ��" << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << "(" << w[i] << "," << p[i] << ")";
	}
	cout << endl;
	cout << "������װ�µ�����ֵΪ" << Knapsack(p, w, c, n) << endl;
	return 0;
}

template<class Typew, class Typep>void Knap<Typew, Typep>::Backtrack(int i)
{
	if (i > n)//����Ҷ�ӽڵ�
	{
		bestp = cp;//��ǰ�ļ�ֵ��ֵ������ֵ��
		return;
	}
	if (cw + w[i] <= c)//����������
	{
		cw += w[i];
		cp += p[i];
		Backtrack(i + 1);
		cw -= w[i];
		cp -= p[i];
	}
	if (Bound(i + 1) > bestp)//����������
	{
		Backtrack(i + 1);
	}
}
template<class Typew, class Typep>Typep Knap<Typew, Typep>::Bound(int i)//�����Ͻ�
{
	Typew cleft = c - cw;//ʣ������
	Typep b = cp;
	//����Ʒ��λ������ֵ�ݼ�װ����Ʒ
	while ((i <= n) && (w[i] <= cleft))
	{
		cleft -= w[i];
		b += p[i];
		i++;
	}
	//װ������
	if (i <= n)
	{
		b += p[i] * (cleft / w[i]);
	}
	return b;
}
class Object
{
	template<class Typew, class Typep>friend Typep Knapsack(Typep[], Typew[], Typew, int);
private:
	int ID;
	float d;
public:
	int operator<=(Object a)const
	{
		return (d >= a.d);
	}
};
template<class Typew, class Typep>Typep Knapsack(Typep p[], Typew w[] ,Typew c, int n)
{
	//ΪKnap::Backtrack��ʼ��
	Typew W = 0;
	Typep P = 0;
	Object*Q = new Object[n];
	for (int i = 1; i <= n; i++)
	{
		Q[i - 1].ID = i;
		Q[i - 1].d = 1.0*p[i] / w[i];
		P += p[i];
		W += w[i];
	}
	if (W<= c)//װ��������Ʒ
	{
		return P;
	}
	//������Ʒ��λ������ֵ����
	BubbleSort(Q, n);
	Knap<Typew, Typep>K;
	K.p = new Typep[n + 1];
	K.w = new Typew[n + 1];
	for (int i = 1; i <= n; i++)
	{
		K.p[i] = p[Q[i - 1].ID];
		K.w[i] = w[Q[i - 1].ID];
	}
	K.cp = 0;
	K.cw = 0;
	K.c = c;
	K.n = n;
	K.bestp = 0;
	K.Backtrack(1);//��������
	delete[]Q;
	delete[]K.w;
	delete[]K.p;
	return K.bestp;
}
template<class Type>void BubbleSort(Type a[], int n)
{
	int i, j;
	for (j = 0; j < n - 1; j++)
	{
		for (i = 0; i < n - 1 - j; i++)
		{
			if (a[i+1]<=a[i])
			{
				Swap(a[i], a[i + 1]);
			}
		}
	}
}
template <class Type>inline void Swap(Type &a, Type&b)
{
	Type temp = a;
	a = b;
	b = temp;
}