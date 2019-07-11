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
	Relation operator ~ ();//���ϵ
	Relation operator * (const Relation& r);//��ϵ�ĸ���
	Relation ref ();//�Է��հ�
	Relation sym ();//�ԳƱհ�
	Relation tra ();//���ݱհ�
	void PrintSet () const;//�Լ�����ʽ�����ϵ
	friend istream& operator >> (istream& in, Relation& r);//�����ϵ
	friend ostream& operator << (ostream& out, const Relation& r);//�Ծ�����ʽ�����ϵ
};

Relation::Relation ()
{//��ϵ�����ʼ��Ϊȫ0
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			m[i][j] = 0;
}

Relation Relation::operator ~ ()
{//���ϵ
	Relation reverse_r;
	int i, j;
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			if (m[i][j])
				reverse_r.m[j][i] = 1;
	return reverse_r;
}

Relation Relation::operator * (const Relation& r)
{//��ϵ�ĸ���
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
{//�Է��հ�
	Relation ref_r = *this;
	for (int i = 0; i < N; ++i)
		if (!ref_r.m[i][i])
			ref_r.m[i][i] = 1;
	return ref_r;
}

Relation Relation::sym ()
{//�ԳƱհ�
	Relation sym_r = *this;
	for (int i = 0; i < N; ++i)
		for (int j = i + 1; j < N; ++j)
			if (sym_r.m[i][j] != sym_r.m[j][i])
				sym_r.m[i][j] = sym_r.m[j][i] = 1;
	return sym_r;
}

Relation Relation::tra ()
{//���ݱհ���WarShall Algorithm
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
		//��ȡ��һ����,������1λ��2λ
		//���������ֵ��ַ�
		while (!isdigit (ch))
			ch = getchar ();
		while (isdigit (ch))
		{
			num1 = num1 * 10 + ch - '0';
			ch = getchar ();
		}
		//��ȡ�ڶ�����
		//���������ֵ��ַ�
		ch = getchar ();
		while (!isdigit (ch))
			ch = getchar ();
		while (isdigit (ch))
		{
			num2 = num2 * 10 + ch - '0';
			ch = getchar ();
		}
		//������������ϵ������
		if (num1 > 0 && num1 <= N && num2 > 0 && num2 <= N)
			r.m[num1 - 1][num2 - 1] = 1;
		//������ȡ
		if (ch != '\n')
			ch = getchar ();
	}
	return in;
}

ostream& operator << (ostream& out, const Relation& r)
{//�����ϵ����ÿ����һ���ո�ӻ��з�����
    //ÿ������֮��û�п������
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
{//�Լ�����ʽ��ӡ��ϵ
	cout<<"{";
	int i, j;
	bool flag;

	flag = false;//�����ж������������ǲ��ǵ�һ��
	for (j = 0; j < N; ++j) //j������
		for (i = 0; i < N; ++i) //i������
			if (m[i][j])
			{ //�������
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
	cout << A; //�Ծ�����ʽ�����ϵ
	A.PrintSet (); //�Լ�����ʽ�����ϵ
	cout << ~A  //���ϵ
		 << A * A  //��ϵ����
		 << A.ref ()  //�Է��հ�
		 << A.sym ()  //�ԳƱհ�
		 << A.tra (); //���ݱհ�
	return 0;
}
