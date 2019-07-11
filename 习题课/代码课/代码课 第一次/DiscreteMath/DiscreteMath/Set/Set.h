/*
File name: Set.h
File desc: ����������
Author: ���
Date: 2011-03-26
Refactoring by: ���
Date: 2011-04-11
*/

#pragma once
#include "fstream"
#define N 62 //ȫ��E�Ļ���

/*
class: Set
desc: ������ȫ��{0-9, a-z, A-Z}�µļ��ϣ�ʵ���˼��ϵĻ�������������������
*/
class Set
{
/*
˽�г�Ա��
*/
private:
	bool elements[N]; //����Ԫ�أ��ò��������ʾȫ���е�ÿһ��Ԫ���Ƿ��ڵ�ǰ������
/*
����������
*/
public:
	Set(void); //Ĭ�Ϲ��캯��������һ���ռ�
	Set(bool elements[]); //���캯������һ���������鹹��һ������
	~Set(void); //����������û��ʹ��ϵͳ��Դ���ɲ�ʵ��

	void setInput(); //�ӿ���̨����һ�����ϣ�������һ���ַ�������ʽ����
	void setOutput(); //�ӿ���̨���һ�����ϣ���������Ԫ�ط����
	void setInput(char* fileName);//��һ���ļ�������һ������
	void setOutput(char* fileName);//�Ѽ��������һ���ļ���
	void empty(); //��һ��������Ϊ�ռ�
	Set setIntersect(const Set& anotherSet); //��������Ľ���
	Set setUnion(const Set& anotherSet); //��������Ĳ���
	Set setComplement(const Set& anotherSet); //�����������Բ�
	Set setComplement(); //����Ȳ�

/*
˽�з�����
*/
private:
	int charToPos(char c); //����һ���ַ����ַ����е�λ��
	char posToChar(int pos); //����һ��ĳһ��λ�õ��ַ�
	void setInput(std::istream& ins); //��һ�������뼯��
	void setOutput(std::ostream& os); //�Ѽ��������һ����׼����ȥ

};

