/*
File name: Relation.h
File desc: 关系类的实现
Author: 杨海滨
Date: 2011-04-02
Refactoring by: 杨海滨
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
Desc：根据|A|动态申请空间，先申请一个指针数组，然后为每一个指针申请一个数组
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
Desc: 可以重构，对比带参构造函数有冗余
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
Desc: 归还空间也分两步，和构造函数过程相反
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
Desc: 输入形式x1 y1,x2 y2,x3 y3,...,xn yn
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
Desc: 输出形式{<x,y>, <y,z>}
	和集合输出不同的方式处理第一个元素，用一个标志fist来标记是否是第一个元素
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
以下几个函数是分别使用标准输入流和标准输出流作为输入流和输出流
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
以下几个函数是分别使用文件输入流和文件输出流作为输入流和输出流
*/
/*
Desc: 把一个文件作为输入流
*/
void Relation::relationInput(char* fileName) {
	ifstream ins(fileName);
	if(ins.fail()) {
		cout<<"文件"<<fileName<<"不能被打开！"<<endl;
	} else {
		relationInput(ins);
	}
	ins.close();
}
/*
Desc: 把一个文件作为输入流
*/
void Relation::relationInputByMatrix(char* fileName) {
	ifstream ins(fileName);
	if(ins.fail()) {
		cout<<"文件"<<fileName<<"不能被打开！"<<endl;
	} else {
		relationInputByMatrix(ins);
	}
	ins.close();
}

/*
Desc: 把一个文件作为输出流，并且把输出内容附加到文件尾
*/
void Relation::relationOutput(char* fileName) {
	ofstream os(fileName, ios::app);
	if(os.fail()) {
		cout<<"文件"<<fileName<<"不能被打开！"<<endl;
	} else {
		relationOutput(os);
	}
	os.close();
}
/*
Desc: 把一个文件作为输出流，并且把输出内容附加到文件尾
*/
void Relation::relationOutputAsSet(char* fileName) {
	ofstream os(fileName, ios::app);
	if(os.fail()) {
		cout<<"文件"<<fileName<<"不能被打开！"<<endl;
	} else {
		relationOutputAsSet(os);
	}
	os.close();
}

/*
Requirement: 同一个集合上的两个关系
Desc: 矩阵乘法，加法使用布尔加法: x+y==0 当且仅当 x=y=0
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
矩阵转置
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
Desc: R并I
*/
Relation Relation::getReflectiveClosure() {
	Relation reflectiveClosure(*this);
	for(int i=0; i<card; i++) {
		reflectiveClosure.matrix[i][i] = 1;
	}
	return reflectiveClosure;
}


/*
Desc: 对称位置上有一个非零，均置为非零，另外可以通过R并R(-1)来求
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
Desc: Warshall算法实现
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

