/*CirclePerm.cpp : 定义控制台应用程序的入口点。
问题分析
圆排列问题的解空间是一棵排列树。按照回溯法搜索排列树的算法框架，设开始时a=[r1,r2,……rn]是所给的n个元的半径，则相应的排列树由a[1:n]的所有排列构成。
解圆排列问题的回溯算法中，CirclePerm(n,a)返回找到的最小的圆排列长度。初始时，数组a是输入的n个圆的半径，计算结束后返回相应于最优解的圆排列。center
计算圆在当前圆排列中的横坐标，由x^2 = sqrt((r1+r2)^2-(r1-r2)^2)推导出x = 2*sqrt(r1*r2)。Compoute计算当前圆排列的长度。变量min记录当前最小圆排列长
度。数组r表示当前圆排列。数组x则记录当前圆排列中各圆的圆心横坐标。
在递归算法Backtrack中，当i>n时，算法搜索至叶节点，得到新的圆排列方案。此时算法调用Compute计算当前圆排列的长度，适时更新当前最优值。
当i<n时，当前扩展节点位于排列树的i-1层。此时算法选择下一个要排列的圆，并计算相应的下界函数。
*/

#include "stdafx.h"
#include"iostream"
#include<cmath>
using namespace std;

float CirclePerm(int n, float*a);//permutation 排列
template<class Type>inline void Swap(Type&a, Type&b);

int main()
{
	float*a = new float[4];
	a[1] = 1; a[2] = 1; a[3] = 2;
	cout << "圆排列中各个半径为：" << endl;
	for (int i = 1; i < 4; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	cout << "最小圆排列长度为：";
	cout << CirclePerm(3, a) << endl;
	return 0;
}

class Circle
{
	friend float CirclePerm(int, float*);
private:
	float Center(int t);//计算当前所选择的圆在当前圆排列中圆心的横坐标
	void Compute();//计算当前圆排列的长度
	void Backtrack(int t);
	float min,//当前最优值
		*x,//当前圆排列圆心横坐标
		*r;//当前圆排列
	int n;//圆排列中圆的个数
};
//计算当前所选择圆的圆心横坐标
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
//计算当前圆排列的长度
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
			if (centerx + r[t] + r[1] < min)//下界约束
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