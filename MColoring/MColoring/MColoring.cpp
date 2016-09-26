/* MColoring.cpp : �������̨Ӧ�ó������ڵ㡣
�㷨���
�������е�ͼ������������ʹ��m����ɫ������£��ɶ�һ������ͼ��ɫ�����в�ͬ������ͨ�����ݵķ�������
�ϵ�Ϊÿһ���ڵ���ɫ����ǰ��n-1���ڵ㶼�Ϸ�����ɫ֮�󣬿�ʼ�Ե�n���ڵ������ɫ����ʱ��ö�ٿ��õ�m
����ɫ��ͨ���͵�n���ڵ����ڵĽڵ����ɫ�����ж������ɫ�Ƿ�Ϸ�������ҵ���ôһ����ɫʹ�õ�n���ڵ�
�ܹ���ɫ����ô˵��m����ɫ�ķ����ǿ��еġ�
��m����ɫΪ����ͼG=(V,E)��ɫ�����У�V�Ķ������Ϊn��������һ��nԪ��x=(x1,x2,��,xn)������ͼ��һ�ֿ���
��ɫ�����У�xi��{1, 2, ��, m}��(1��i��n)��ʾ���趥��i����ɫ�����磬5Ԫ��(1, 2, 2, 3, 1)��ʾ�Ծ���5�����������
ͼ��a����һ����ɫ������A����ɫ1������B����ɫ2������C����ɫ2����˵ȵȡ������nԪ��X�У��������ڶ���
����������ͬ��ɫ���ͳƴ�nԪ��Ϊ���н⣬����Ϊ��Ч�⡣���׿�����ÿ�����������ɫ��m��ѡ��n���������
mn�ֲ�ͬ����ɫ����������Ľ�ռ���һ�ø߶�Ϊn����ȫm�������������߶ȵĶ���Ϊ�Ӹ��ڵ㵽Ҷ�ӽڵ��·��
�ĳ��ȡ�ÿ����֧��㣬����m�����ӽ�㡣��ײ���mn��Ҷ�ӽ�㡣���磬��ʾ��3����ɫΪ3�������ͼ��ɫ��״
̬�ռ�������ͼ��ʾ���Ե�i��i>=1�����ϵ�ÿ�����㣬���丸�ڵ㵽�ýڵ�ı��ϵı�ű�ʾ����i��ɫ����ɫ��š�
*/

#include "stdafx.h"
#include"iostream"
#include<fstream>
using namespace std;

const int N = 5;//ͼ�Ķ�����
const int M =3;//ɫ����
ifstream fin("C:\\Users\\YAN\\Desktop\\data.txt");
class Color
{
	friend int mColoring(int, int, int**);
private:
	bool Ok(int k);
	void Backtrack(int t);
	int n,//ͼ�Ķ�����
		m,//���õ���ɫ��
		**a,//ͼ���ڽӾ���
		*x;//��ǰ��
	long sum;//��ǰ�Ѿ��ҵ��Ŀ�m��ɫ�ķ�����
};
int mColoring(int n, int m, int**a);


int main()
{
	int**a = new int*[N + 1];
	for (int i = 1; i <= N; i++)
	{
		a[i] = new int[N + 1];
	}
	cout << "ͼG���ڽӾ���Ϊ��" << endl;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			fin >> a[i][j];
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << "ͼG����ɫ�������£�" << endl;
	cout << "��m=" << M << "ʱ��ͼG�Ŀ�����ɫ������ĿΪ��" << mColoring(N, M, a) << endl;
	for (int i = 1; i <= N; i++)
	{
		delete[]a[i];
	}
	delete[]a;
	return 0;
}

void Color::Backtrack(int t)
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
		for (int i = 1; i <= m; i++)
		{
			x[t] = i;//t����iɫ
			if (Ok(t))
			{
				Backtrack(t + 1);
			}
			x[t] = 0;
		}
	}
}
bool Color::Ok(int k)//�����ɫ�Ŀ�����
{
	for (int j = 1; j <= n; j++)
	{
		if ((a[k][j] == 1) && (x[j] == x[k]))
		{
			return false;
		}
	}
	return true;
}
int mColoring(int n, int m, int**a)
{
	Color X;
	//��ʼ��
	X.n = n;
	X.m = m;
	X.a = a;
	X.sum = 0;
	int*p = new int[n + 1];
	for (int i = 0; i <= n; i++)
	{
		p[i] = 0;
	}
	X.x = p;
	X.Backtrack(1);
	delete[]p;
	return X.sum;
}