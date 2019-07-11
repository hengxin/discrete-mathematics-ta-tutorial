/*
File name: Relation.h
File desc: ��ϵ���ʵ��
Author: ���
Date: 2011-04-02
Refactoring by: ���
Date: 2011-04-11
*/


#include "Relation.h"
#include "iostream"

using namespace std;
Relation::Relation(void)
{
	new (this)Relation(N);
}

/*
Desc������|A|��̬����ռ䣬������һ��ָ�����飬Ȼ��Ϊÿһ��ָ������һ������
*/
Relation::Relation(int card) {
	this->card = card;
	matrix = new int *[card];
	for(int i=0; i<card; i++) {
		matrix[i] = new int[card];
	}
	for(int i=0; i<card; i++){
		for(int j=0; j<card; j++){
			matrix[i][j] = 0;
		}
	}
}
/*
Desc: �����ع����Աȴ��ι��캯��������
*/
Relation::Relation(const Relation& r) {
	this->card = r.card;
	matrix = new int *[card];
	for(int i=0; i<card; i++) {
		matrix[i] = new int[card];
	}
	for(int i=0; i<card; i++){
		for(int j=0; j<card; j++){
			matrix[i][j] = r.matrix[i][j];
		}
	}
}

/*
Desc: �黹�ռ�Ҳ���������͹��캯�������෴
*/
Relation::~Relation(void)
{
	for(int i=0; i<card; i++) {
		delete []matrix[i];
	}
	delete []matrix;
}

int Relation::getCardinality() const{
	return card;
}

bool Relation::isElementLegal(int first, int second) {
	return (first>0&&second>0&&first<card+1&&second<card+1);
}

/*
Desc: ������ʽx1 y1,x2 y2,x3 y3,...,xn yn
*/
void Relation::relationInput(istream& ins) {
	int first = 0, second = 0;
	char separator;
	while(1) {
		ins>>first>>second;
		separator = ins.get();
		if(isElementLegal(first, second)) {
			matrix[first-1][second-1] = 1;
		} else {
			break;
		}
		if(separator !=',') {
			break;
		}
	}
}

void Relation::relationInputByMatrix(istream& ins) {
	for(int i=0; i<card; i++){
		for(int j=0; j<card; j++){
			ins >> matrix[i][j];
		}
	}
}

void Relation::relationOutput(ostream& os) {
	for(int i=0; i<card; i++){
		for(int j=0; j<card; j++){
			os << matrix[i][j]<<' ';
		}
		os << endl;
	}
}
/*
Desc: �����ʽ{<x,y>, <y,z>}
	�ͼ��������ͬ�ķ�ʽ�����һ��Ԫ�أ���һ����־fist������Ƿ��ǵ�һ��Ԫ��
*/
void Relation::relationOutputAsSet(ostream& os) {
	os << "{";
	bool first = true;
	for(int i=0; i<card; i++) {
		for(int j=0; j<card; j++) {
			if(matrix[i][j]) {
				if(first) {
					first = false;
					os << "<" << i+1 << "," << j+1 << ">";
				} else {
					os << ",<" << i+1 << "," << j+1 << ">";
				}
			}
		}
	}
	os << "}" << endl;
}


/*
���¼��������Ƿֱ�ʹ�ñ�׼�������ͱ�׼�������Ϊ�������������
*/
void Relation::relationInput(){
	relationInput(cin);
}

void Relation::relationInputByMatrix(){
	relationInputByMatrix(cin);
}

void Relation::relationOutput(){
	relationOutput(cout);
}

void Relation::relationOutputAsSet() {
	relationOutputAsSet(cout);
}

/*
���¼��������Ƿֱ�ʹ���ļ����������ļ��������Ϊ�������������
*/
/*
Desc: ��һ���ļ���Ϊ������
*/
void Relation::relationInput(char* fileName) {
	ifstream ins(fileName);
	if(ins.fail()) {
		cout<<"�ļ�"<<fileName<<"���ܱ��򿪣�"<<endl;
	} else {
		relationInput(ins);
	}
	ins.close();
}
/*
Desc: ��һ���ļ���Ϊ������
*/
void Relation::relationInputByMatrix(char* fileName) {
	ifstream ins(fileName);
	if(ins.fail()) {
		cout<<"�ļ�"<<fileName<<"���ܱ��򿪣�"<<endl;
	} else {
		relationInputByMatrix(ins);
	}
	ins.close();
}

/*
Desc: ��һ���ļ���Ϊ����������Ұ�������ݸ��ӵ��ļ�β
*/
void Relation::relationOutput(char* fileName) {
	ofstream os(fileName, ios::app);
	if(os.fail()) {
		cout<<"�ļ�"<<fileName<<"���ܱ��򿪣�"<<endl;
	} else {
		relationOutput(os);
	}
	os.close();
}
/*
Desc: ��һ���ļ���Ϊ����������Ұ�������ݸ��ӵ��ļ�β
*/
void Relation::relationOutputAsSet(char* fileName) {
	ofstream os(fileName, ios::app);
	if(os.fail()) {
		cout<<"�ļ�"<<fileName<<"���ܱ��򿪣�"<<endl;
	} else {
		relationOutputAsSet(os);
	}
	os.close();
}

/*
Requirement: ͬһ�������ϵ�������ϵ
Desc: ����˷����ӷ�ʹ�ò����ӷ�: x+y==0 ���ҽ��� x=y=0
*/
Relation Relation::relationComposition(const Relation& right){
	Relation composition(card);
	if(right.card != card) {
		return composition;
	}
	for(int i=0; i<card; i++) {
		for(int j=0; j<card; j++) {
			for(int k=0; k<card; k++) {
				composition.matrix[i][j] += matrix[i][k] * right.matrix[k][j];
			}
			composition.matrix[i][j] = reduce(composition.matrix[i][j]);
		}
	}

	return composition;
}

/*
����ת��
*/
Relation Relation::relationInverse(){
	Relation inverse(card);
	for(int i=0; i<card; i++) {
		for(int j=0; j<card; j++) {
			inverse.matrix[i][j] = matrix[j][i];
		}
	}
	return inverse;
}


/*
Desc: R��I
*/
Relation Relation::getReflectiveClosure() {
	Relation reflectiveClosure(*this);
	for(int i=0; i<card; i++) {
		reflectiveClosure.matrix[i][i] = 1;
	}
	return reflectiveClosure;
}


/*
Desc: �Գ�λ������һ�����㣬����Ϊ���㣬�������ͨ��R��R(-1)����
*/
Relation Relation::getSymmetricClosure() {
	Relation symmetricClosure(card);
	for(int i=0; i<card; i++) {
		for(int j=i; j<card; j++) {
			if(matrix[i][j] + matrix[j][i] > 0) {
				symmetricClosure.matrix[i][j] = 1;
				symmetricClosure.matrix[j][i] = 1;
			}
		}
	}
	return symmetricClosure;
}

/*
Func: getTranstiveClosure
Desc: Warshall�㷨ʵ��
*/
Relation Relation::getTranstiveClosure() {
	Relation transtiveClosure(*this);
	for(int k=0; k<card; k++) {
		for(int i=0; i<card; i++) {
			for(int j=0; j<card; j++) {
				transtiveClosure.matrix[i][j] = reduce(transtiveClosure.matrix[i][j] + transtiveClosure.matrix[i][k] * transtiveClosure.matrix[k][j]);
			}
		}
	}

	return transtiveClosure;
}

