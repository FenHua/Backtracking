/*MaxClique.cpp : �������̨Ӧ�ó������ڵ㡣
��������
��������ͼG=(V, E)������V�Ƿǿռ��ϣ���Ϊ���㼯��E��V��Ԫ�ع��ɵ������Ԫ��ļ��ϣ���Ϊ��
��������ͼ�еı߾��Ƕ��������ԣ�����Գ���Բ���š�( )����ʾ�����U��V���Ҷ�������������u��
v��U��(u, v)��E�����U��G����ȫ��ͼ(��ȫͼG����ָͼG��ÿ������֮�䶼������)��G����ȫ��ͼU��
G���ŵ��ҽ���U��������G�ĸ������ȫ��ͼ�С�G���������ָG�����������������š�
�㷨���
����ͼG������ź������������ⶼ�����û��ݷ���O(n2^n)��ʱ���ڽ����ͼG������ź�������
�����ⶼ���Կ�����ͼG�Ķ��㼯V���Ӽ�ѡȡ���⡣��˿������Ӽ�������ʾ����Ľ�ռ䡣��������
����Ϊһ�����ţ������м���һ�����㣬Ȼ�����ο���ÿ�����㣬�鿴�ö��������֮����Ȼ����һ���ţ�
������ԣ����ǽ��ö�������Ż����������������������У�ֱ��������Ȼ��ݹ��ж���һ���㡣����
�����ӻ���ֱ����������������ڵݹ�ǰ���ɲ��ü�֦������������Ч������Ϊ���жϵ�ǰ���������֮��
�Ƿ�����һ���ţ�ֻ��Ҫ���Ǹö�������ж����Ƿ������ӡ������в�����һ���Ƚϼ򵥵ļ�֦���ԣ���
���ʣ��δ���ǵĶ������������ж����������ڵ�ǰ��Ķ���������ֹͣ����������������������ȵݹ�
��������һ��Ҷ���ʱ������ֹͣ��������ʱ�������Ž������ֵ��
*/
//����ţ����ݷ�
#include "stdafx.h"
#include<iostream>
#include<fstream>
using namespace std;

const int N = 5;//ͼG�Ķ�����
ifstream fin("C:\\Users\\YAN\\Desktop\\data.txt");
class Clique
{
	friend int MaxClique(int**, int[], int);
private:
	void Backtrack(int i);
	int **a,//ͼG���ڽӾ���
		n,//ͼG�Ķ�����
		*x,//��ǰ��
		*bestx,//��ǰ���Ž�
		cn,//��ǰ������
		bestn;//��ǰ��󶥵���
};
int MaxClique(int**a, int v[], int n);

int main()
{
	int v[N + 1];
	int **a = new int*[N + 1];
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
	cout << "ͼG������Ž�����Ϊ��" << endl;//��ִ�к�����������
	cout << "ͼG������Ŷ������Ϊ��" << MaxClique(a, v, N) << endl;
	for (int i = 1; i <= N; i++)
	{
		delete[]a[i];
	}
	delete[]a;
	return 0;
}

void Clique::Backtrack(int i)
{
	if (i > n)
	{
		//������Ҷ�ڵ�
		for (int j = 1; j <= n; j++)
		{
			bestx[j] = x[j];
			cout << x[j] << " ";
		}
		cout << endl;
		bestn = cn;
		return;
	}
	//��鶥��i�뵱ǰ�ŵ�����
	int OK = 1;
	for (int j = 1; j < i; j++)
	{
		if (x[j] && (a[i][j] == 0))
		{
			OK = 0;//i��j������
			break;
		}
	}
	if (OK)
	{
		//����������
		x[i] = 1;
		cn++;
		Backtrack(i + 1);
		x[i] = 0;
		cn--;
	}
	if (cn + n - i >= bestn)
	{
		//����������
		x[i] = 0;
		Backtrack(i + 1);
	}
}
int MaxClique(int**a, int v[], int n)
{
	Clique Y;
	//��ʼ��Y
	Y.x = new int[n + 1];
	Y.a = a;
	Y.n = n;
	Y.cn = 0;
	Y.bestn = 0;
	Y.bestx = v;
	Y.Backtrack(1);
	delete[]Y.x;
	return Y.bestn;
}