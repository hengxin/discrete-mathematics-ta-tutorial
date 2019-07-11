#include <iostream>
#include <cstdlib>
#include <cstdio>
#define N 20
using namespace std;

class Relation
{
private :
	bool m[N][N];
public :
	Relation ();
	Relation operator ~ ();//逆关系
	Relation operator * (const Relation& r);//关系的复合
	Relation ref ();//自反闭包
	Relation sym ();//对称闭包
	Relation tra ();//传递闭包
	void PrintSet () const;//以集合形式输出关系
	friend istream& operator >> (istream& in, Relation& r);//输入关系
	friend ostream& operator << (ostream& out, const Relation& r);//以矩阵形式输出关系
};

Relation::Relation ()
{//关系矩阵初始化为全0
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			m[i][j] = 0;
}

Relation Relation::operator ~ ()
{//逆关系
	Relation reverse_r;
	int i, j;
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			if (m[i][j])
				reverse_r.m[j][i] = 1;
	return reverse_r;
}

Relation Relation::operator * (const Relation& r)
{//关系的复合
	Relation combine_r;
	int i, j, k;
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			if (m[i][j])
			{
				for (k = 0; k < N; ++k)
					if (r.m[j][k])
						combine_r.m[i][k] = 1;
			}
	return combine_r;
}

Relation Relation::ref ()
{//自反闭包
	Relation ref_r = *this;
	for (int i = 0; i < N; ++i)
		if (!ref_r.m[i][i])
			ref_r.m[i][i] = 1;
	return ref_r;
}

Relation Relation::sym ()
{//对称闭包
	Relation sym_r = *this;
	for (int i = 0; i < N; ++i)
		for (int j = i + 1; j < N; ++j)
			if (sym_r.m[i][j] != sym_r.m[j][i])
				sym_r.m[i][j] = sym_r.m[j][i] = 1;
	return sym_r;
}

Relation Relation::tra ()
{//传递闭包，WarShall Algorithm
	Relation tra_r = *this;
	int i, j, k;
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			for (k = 0; k < N; ++k)
				tra_r.m[i][j] = tra_r.m[i][j] + tra_r.m[i][k] * tra_r.m[k][j];
	return tra_r;
}

istream& operator >> (istream& in, Relation& r)
{
	char ch;
	ch = getchar ();
	if (ch == '\n')
		return in;

	int num1, num2;
	while (ch != '\n')
	{
		num1 = num2 = 0;
		//提取第一个数,可能是1位或2位
		//读掉非数字的字符
		while (!isdigit (ch))
			ch = getchar ();
		while (isdigit (ch))
		{
			num1 = num1 * 10 + ch - '0';
			ch = getchar ();
		}
		//提取第二个数
		//读掉非数字的字符
		ch = getchar ();
		while (!isdigit (ch))
			ch = getchar ();
		while (isdigit (ch))
		{
			num2 = num2 * 10 + ch - '0';
			ch = getchar ();
		}
		//将这对数放入关系矩阵中
		if (num1 > 0 && num1 <= N && num2 > 0 && num2 <= N)
			r.m[num1 - 1][num2 - 1] = 1;
		//继续读取
		if (ch != '\n')
			ch = getchar ();
	}
	return in;
}

ostream& operator << (ostream& out, const Relation& r)
{//输出关系矩阵，每行以一个空格加换行符结束
    //每个矩阵之间没有空行相隔
	int i, j;
	for (i = 0; i < N; ++i)
	{
		for (j = 0; j < N; ++j)
			out<<r.m[i][j]<<" ";
        out<<endl;
	}
	return out;
}

void Relation::PrintSet () const
{//以集合形式打印关系
	cout<<"{";
	int i, j;
	bool flag;

	flag = false;//用于判断输出的有序对是不是第一对
	for (j = 0; j < N; ++j) //j遍历列
		for (i = 0; i < N; ++i) //i遍历行
			if (m[i][j])
			{ //以列输出
				if (!flag)
				{
					cout<<"<"<<i + 1<<","<<j + 1<<">";
					flag = true;
				}
				else
					cout<<",<"<<i + 1<<","<<j + 1<<">";
			}
	cout<<"}"<<endl;
}

int main ()
{
	Relation A;
	cin >> A;
	cout << A; //以矩阵形式输出关系
	A.PrintSet (); //以集合形式输出关系
	cout << ~A  //逆关系
		 << A * A  //关系复合
		 << A.ref ()  //自反闭包
		 << A.sym ()  //对称闭包
		 << A.tra (); //传递闭包
	return 0;
}
