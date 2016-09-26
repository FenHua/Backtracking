/*TSP.cpp : �������̨Ӧ�ó������ڵ㡣
�������
�����ۻ�Ա����Ľ�ռ���һ���������������������Ļ��ݷ�������1,2,����n���������еĵݹ��㷨Perm����
����ʼʱx=[1,2,����n],����Ӧ����������x[1:n]���������й��ɡ�
�ڵݹ��㷨Backtrack�У���i=nʱ����ǰ��չ�ڵ�����������Ҷ�ڵ�ĸ��ڵ㡣��ʱ�㷨���ͼG�Ƿ����һ��
�Ӷ���x[n-1]������x[n]�ıߺ�һ���Ӷ���x[n]������1�ıߡ�����������߶����ڣ����ҵ�һ������Ա�ۻ���·
����ʱ���㷨����Ҫ�ж�������·�ķ����Ƿ��������ҵ��ĵ�ǰ���Ż����ķ���bestc������ǣ��������µ�
ǰ����ֵbestc�͵�ǰ���Ž�bestx��
��i<nʱ����ǰ��չ�ڵ�λ���������ĵ�i-1�㡣ͼG�д��ڴӶ���x[i-1]������x[i]�ı�ʱ��x[1:i]����ͼG��һ��·
�����ҵ�x[1:i]�ķ���С�ڵ�ǰ����ֵʱ�㷨�������ĵ�i�㣬���򽫼�ȥ��Ӧ��������
*/

#include "stdafx.h"
#include"iostream"
#include<fstream>
using namespace std;

ifstream fin("C:\\Users\\YAN\\Desktop\\data.txt");
const int N = 4;//������
template<class Type>class Traveling
{
	template<class Type>friend Type TSP(Type**a, int n);
private:
	void Backtrack(int i);
	int n,//ͼG�Ķ�����
		*x,//��ǰ��
		*bestx;//��ǰ���Ž�
	Type**a,//ͼG ���ڽӾ���
		cc,//��ǰ�ķ���
		bestc;//��ǰ����ֵ
	int NoEdge;//�ޱ߱��
};
template<class Type>inline void Swap(Type&a, Type&b);
template<class Type>Type TSP(Type**a, int n);

int main()
{
	cout << "ͼ�Ķ������Ϊ��"<<N<< endl;
	int**a = new int*[N + 1];
	for (int i = 0; i <= N; i++)
	{
		a[i] = new int[N + 1];
	}
	cout << "ͼ���ڽӾ���Ϊ��" << endl;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			fin >> a[i][j];
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << "��̻�·����Ϊ��" << TSP(a, N) << endl;
	for (int i = 0; i <= N; i++)
	{
		delete[]a[i];
	}
	delete[]a;
	return 0;
}

template<class Type>void Traveling<Type>::Backtrack(int i)
{
	if (i == n)
	{
		if ((a[x[n - 1]][x[n]] != 0) && (a[x[n]][1] != 0) && (cc + a[x[n - 1]][x[n]] + a[x[n]][1] < bestc || bestc == 0))
		{
			for (int j = 1; j <= n; j++)
				bestx[j] = x[j];
			bestc = cc + a[x[n - 1]][x[n]] + a[x[n]][1];
		}
	}
	else
	{
		for (int j = i; j <= n; j++)
		{
			//�Ƿ�ɽ���x[j]����
			if ((a[x[i - 1]][x[j]] != 0) && (cc + a[x[i - 1]][x[i]] < bestc || bestc == 0))
			{
				//��������
				Swap(x[i], x[j]);//֮���Խ���x����Ϊ��ʼ��ʱx�Ѿ���ֵ��˳��
				cc += a[x[i - 1]][x[i]];//��ǰ�����ۼӺ�
				Backtrack(i + 1);//����������չ������������һ����չ
				cc -= a[x[i - 1]][x[i]];
				Swap(x[i], x[j]);
			}
		}
	}
}
template<class Type>Type TSP(Type**a, int n)
{
	Traveling<Type>Y;
	Y.n = n;
	Y.x = new int[n + 1];
	Y.bestx = new int[n + 1];
	for (int i = 1; i <= n; i++)
	{
		Y.x[i] = i;
	}
	Y.a = a;
	Y.cc = 0;
	Y.bestc = 0;
	Y.NoEdge = 0;
	Y.Backtrack(2);
	cout << "��̻�·Ϊ��" << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << Y.bestx[i] << "-->";
	}
	cout << Y.bestx[1] << endl;
	delete[]Y.x;
	delete[]Y.bestx;
	return Y.bestc;
}
template<class Type>inline void Swap(Type&a, Type&b)
{
	Type temp = a;
	a = b;
	b = temp;
}