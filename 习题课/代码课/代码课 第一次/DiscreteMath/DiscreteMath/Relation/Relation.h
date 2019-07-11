/*
File name: Relation.h
File desc: 关系类声明
Author: 杨海滨
Date: 2011-04-02
Refactoring by: 杨海滨
Date: 2011-04-11
*/

#pragma once

#include "fstream"

#define N 2 //默认

/*
class: Relation
desc: 定义集合A上的关系，|A|是可设置的，默认为N
	定义了关系的基本运算和求闭包操作
*/
class Relation
{
/*
私有成员区
*/
private:
	int card; //|A|的基数
	int** matrix; //为便于计算，用矩阵表示关系，矩阵以二维int数组存储

/*
公共方法区
*/
public:
	Relation(void); //默认构造函数，!A|=N
	Relation(int size); //带参构造函数，!A|=size
	Relation(const Relation& r); //拷贝构造函数，因为使用了资源，不能使用默认拷贝构造函数
	~Relation(void); //析构函数，归还申请的空间

	void relationInput(); //从控制台输入关系
	void relationInput(char* fileName);
	void relationOutput(); //从控制台以矩阵形式输出关系
	void relationOutput(char* fileName);
	void relationOutputAsSet(); //从控制台以集合形式输出关系
	void relationOutputAsSet(char* fileName);
	void relationInputByMatrix(); //从控制台接收矩阵形式的关系
	void relationInputByMatrix(char* fileName);
	Relation relationComposition(const Relation& right); //关系复合
	Relation relationInverse(); //逆关系
	int getCardinality() const; //返回|A|
	Relation getReflectiveClosure(); //求自反闭包
	Relation getSymmetricClosure(); //求对称闭包
	Relation getTranstiveClosure(); //求传递闭包，我只使用了Warshall算法

/*
私有方法区
*/
private:
	bool isElementLegal(int first, int second); //判断关系的元素是否合法
	inline int reduce(int sum) {
		return sum == 0 ? 0 : 1;
	} //方便布尔加法的一个小函数
	void relationInput(std::istream& ins);
	void relationOutput(std::ostream& os);
	void relationInputByMatrix(std::istream& ins);
	void relationOutputAsSet(std::ostream& os);
};

