/*
File name: Set.cpp
File desc: �������ʵ��
Author: ���
Date: 2011-03-26
Refactoring by: ���
Date: 2011-04-11
*/

#include "Set.h"
#include "string"
#include "iostream"
using namespace std;


Set::Set(void) {
	//��ʼ��Ϊ�ռ�
	for(int i=0; i<N; i++) {
		this->elements[i] = false;
	}
}
Set::Set(bool elements[]){
	//��һ�����������ʼ������
	for(int i=0; i<N; i++) {
		this->elements[i] = elements[i];
	}
}


Set::~Set(void)
{
}
/*
�ַ����������£�
0-9,a-z,A-Z
������������ʵ��λ�ú��ַ���ӳ��
*/
/*
Func: charToPos
Desc: ����ַ���ȫ��E�У��򷵻���λ�ã����򣬷���-1
*/
int Set::charToPos(char c) {
	if(c>='0' && c<='9') {
		return c - '0';	
	}
	if(c>='a' && c<='z') {
		return c - 'a' + 10;
	}
	if(c>='A' && c<='Z') {
		return c - 'A' + 36;
	}
	return -1;
}

/*
Func: posToChar
Desc: ���λ�÷�Χ��[0,N)֮�䣬�򷵻ظ��ַ������򷵻�'\0'.
*/
char Set::posToChar(int pos) {
	if(pos>-1 && pos < 10) {
		return '0' + pos;
	}
	if(pos>9 && pos < 36) {
		return 'a' + pos - 10;
	}
	if(pos>35 && pos<62) {
		return 'A' + pos - 36;
	}
	return '\0';
}


void Set::setInput(istream& ins) {
	string temp;
	int len = 0;
	int pos = -1;
	ins>>temp;
	len = temp.length();
	this->empty();
	for(int i=0; i<len; i++) {
		pos = charToPos(temp[i]);
		if(pos>-1) {
			elements[pos] = true;
		}
	}
}

void Set::setOutput(ostream& os) {
	os<<'{';
	int i = -1;
	while(i++<N-1 && !elements[i]);
	if(i<N) {
		os<<posToChar(i);
	} 
	i++;
	for(; i<N; i++) {
		if(elements[i]) {
			os<<','<<posToChar(i);
		}
	}
	os<<'}'<<endl;
}

void Set::empty() {
	for(int i=0; i<N; i++) {
		elements[i] = false;
	}
}

void Set::setInput() {
	setInput(cin);
}

void Set::setOutput() {
	setOutput(cout);
}


void Set::setInput(char* fileName) {
	ifstream ins(fileName);
	if(ins.fail()) {
		cout<<"�ļ�"<<fileName<<"���ܱ��򿪣�"<<endl;
	} else {
		setInput(ins);
	}
	ins.close();
}

void Set::setOutput(char* fileName) {
	ofstream os(fileName, ios::app);
	if(os.fail()) {
		cout<<"�ļ�"<<fileName<<"���ܱ��򿪣�"<<endl;
	} else {
		setOutput(os);
	}
	os.close();
}

Set Set::setIntersect(const Set& anotherSet) {
	Set intersection;
	for(int i=0; i<N; i++) {
		intersection.elements[i] = elements[i] && anotherSet.elements[i]; //���߼���ʵ�ֽ�
	}
	return intersection;
}

Set Set::setUnion(const Set& anotherSet) {
	Set unionSet;
	for(int i=0; i<N; i++) {
		unionSet.elements[i] = elements[i] || anotherSet.elements[i]; //���߼���ʵ�ֲ�
	}
	return unionSet;
}

Set Set::setComplement(const Set& anotherSet) {
	Set complement;
	for(int i=0; i<N; i++) {
		complement.elements[i] = elements[i] && !anotherSet.elements[i]; //�����ʵ����Բ�
	}
	return complement;
}

Set Set::setComplement() {
	Set complement;
	for(int i=0; i<N; i++) {
		complement.elements[i] = !elements[i]; //�÷�ʵ�־��Բ����������ʹ��ȫ������Բ�ʵ�־��Բ�
	}
	return complement;
}


