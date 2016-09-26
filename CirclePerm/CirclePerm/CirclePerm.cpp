/*CirclePerm.cpp : �������̨Ӧ�ó������ڵ㡣
�������
Բ��������Ľ�ռ���һ�������������ջ��ݷ��������������㷨��ܣ��迪ʼʱa=[r1,r2,����rn]��������n��Ԫ�İ뾶������Ӧ����������a[1:n]���������й��ɡ�
��Բ��������Ļ����㷨�У�CirclePerm(n,a)�����ҵ�����С��Բ���г��ȡ���ʼʱ������a�������n��Բ�İ뾶����������󷵻���Ӧ�����Ž��Բ���С�center
����Բ�ڵ�ǰԲ�����еĺ����꣬��x^2 = sqrt((r1+r2)^2-(r1-r2)^2)�Ƶ���x = 2*sqrt(r1*r2)��Compoute���㵱ǰԲ���еĳ��ȡ�����min��¼��ǰ��СԲ���г�
�ȡ�����r��ʾ��ǰԲ���С�����x���¼��ǰԲ�����и�Բ��Բ�ĺ����ꡣ
�ڵݹ��㷨Backtrack�У���i>nʱ���㷨������Ҷ�ڵ㣬�õ��µ�Բ���з�������ʱ�㷨����Compute���㵱ǰԲ���еĳ��ȣ���ʱ���µ�ǰ����ֵ��
��i<nʱ����ǰ��չ�ڵ�λ����������i-1�㡣��ʱ�㷨ѡ����һ��Ҫ���е�Բ����������Ӧ���½纯����
*/

#include "stdafx.h"
#include"iostream"
#include<cmath>
using namespace std;

float CirclePerm(int n, float*a);//permutation ����
template<class Type>inline void Swap(Type&a, Type&b);

int main()
{
	float*a = new float[4];
	a[1] = 1; a[2] = 1; a[3] = 2;
	cout << "Բ�����и����뾶Ϊ��" << endl;
	for (int i = 1; i < 4; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	cout << "��СԲ���г���Ϊ��";
	cout << CirclePerm(3, a) << endl;
	return 0;
}

class Circle
{
	friend float CirclePerm(int, float*);
private:
	float Center(int t);//���㵱ǰ��ѡ���Բ�ڵ�ǰԲ������Բ�ĵĺ�����
	void Compute();//���㵱ǰԲ���еĳ���
	void Backtrack(int t);
	float min,//��ǰ����ֵ
		*x,//��ǰԲ����Բ�ĺ�����
		*r;//��ǰԲ����
	int n;//Բ������Բ�ĸ���
};
//���㵱ǰ��ѡ��Բ��Բ�ĺ�����
float Circle::Center(int t)
{
	float temp = 0;
	for (int j = 1; j < t; j++)
	{
		float valuex = x[j] + 2.0*sqrt(r[t] * r[j]);
		if (valuex>temp)
		{
			temp = valuex;
		}
	}
	return temp;
}
//���㵱ǰԲ���еĳ���
void Circle::Compute(void)
{
	float low = 0, high = 0;
	for (int i = 1; i <= n; i++)
	{
		if (x[i] - r[i] < low)
		{
			low = x[i] - r[i];
		}
		if (x[i] + r[i]>high)
		{
			high = x[i] + r[i];
		}
	}
	if (high - low < min)
	{
		min = high - low;
	}
}
void Circle::Backtrack(int t)
{
	if (t>n)
	{
		Compute();
	}
	else
	{
		for (int j = t; j <= n; j++)
		{
			Swap(r[t], r[j]);
			float centerx = Center(t);
			if (centerx + r[t] + r[1] < min)//�½�Լ��
			{
				x[t] = centerx;
				Backtrack(t + 1);
			}
			Swap(r[t], r[j]);
		}
	}
}
float CirclePerm(int n, float*a)
{
	Circle X;
	X.n = n;
	X.r = a;
	X.min = 1000;
	float *x = new float[n + 1];
	X.x = x;
	X.Backtrack(1);
	delete[] x;
	return X.min;
}
template<class Type>inline void Swap(Type&a, Type&b)
{
	Type temp = a;
	a = b;
	b = temp;
}