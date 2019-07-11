/*
File name: Relation.h
File desc: ��ϵ������
Author: ���
Date: 2011-04-02
Refactoring by: ���
Date: 2011-04-11
*/

#pragma once

#include "fstream"

#define N 2 //Ĭ��

/*
class: Relation
desc: ���弯��A�ϵĹ�ϵ��|A|�ǿ����õģ�Ĭ��ΪN
	�����˹�ϵ�Ļ����������հ�����
*/
class Relation
{
/*
˽�г�Ա��
*/
private:
	int card; //|A|�Ļ���
	int** matrix; //Ϊ���ڼ��㣬�þ����ʾ��ϵ�������Զ�άint����洢

/*
����������
*/
public:
	Relation(void); //Ĭ�Ϲ��캯����!A|=N
	Relation(int size); //���ι��캯����!A|=size
	Relation(const Relation& r); //�������캯������Ϊʹ������Դ������ʹ��Ĭ�Ͽ������캯��
	~Relation(void); //�����������黹����Ŀռ�

	void relationInput(); //�ӿ���̨�����ϵ
	void relationInput(char* fileName);
	void relationOutput(); //�ӿ���̨�Ծ�����ʽ�����ϵ
	void relationOutput(char* fileName);
	void relationOutputAsSet(); //�ӿ���̨�Լ�����ʽ�����ϵ
	void relationOutputAsSet(char* fileName);
	void relationInputByMatrix(); //�ӿ���̨���վ�����ʽ�Ĺ�ϵ
	void relationInputByMatrix(char* fileName);
	Relation relationComposition(const Relation& right); //��ϵ����
	Relation relationInverse(); //���ϵ
	int getCardinality() const; //����|A|
	Relation getReflectiveClosure(); //���Է��հ�
	Relation getSymmetricClosure(); //��ԳƱհ�
	Relation getTranstiveClosure(); //�󴫵ݱհ�����ֻʹ����Warshall�㷨

/*
˽�з�����
*/
private:
	bool isElementLegal(int first, int second); //�жϹ�ϵ��Ԫ���Ƿ�Ϸ�
	inline int reduce(int sum) {
		return sum == 0 ? 0 : 1;
	} //���㲼���ӷ���һ��С����
	void relationInput(std::istream& ins);
	void relationOutput(std::ostream& os);
	void relationInputByMatrix(std::istream& ins);
	void relationOutputAsSet(std::ostream& os);
};

