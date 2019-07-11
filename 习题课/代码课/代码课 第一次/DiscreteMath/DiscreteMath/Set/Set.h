/*
File name: Set.h
File desc: 集合类声明
Author: 杨海滨
Date: 2011-03-26
Refactoring by: 杨海滨
Date: 2011-04-11
*/

#pragma once
#include "fstream"
#define N 62 //全集E的基数

/*
class: Set
desc: 定义在全集{0-9, a-z, A-Z}下的集合，实现了集合的基本运算和输入输出操作
*/
class Set
{
/*
私有成员区
*/
private:
	bool elements[N]; //集合元素，用布尔数组表示全集中的每一个元素是否在当前集合中
/*
公共方法区
*/
public:
	Set(void); //默认构造函数，声明一个空集
	Set(bool elements[]); //构造函数，用一个布尔数组构造一个集合
	~Set(void); //析构函数，没有使用系统资源，可不实现

	void setInput(); //从控制台输入一个集合，集合以一个字符串的形式输入
	void setOutput(); //从控制台输出一个集合，集合以列元素法输出
	void setInput(char* fileName);//从一个文件中输入一个集合
	void setOutput(char* fileName);//把集合输出到一个文件中
	void empty(); //把一个集合置为空集
	Set setIntersect(const Set& anotherSet); //求与参数的交集
	Set setUnion(const Set& anotherSet); //求与参数的并集
	Set setComplement(const Set& anotherSet); //求与参数的相对补
	Set setComplement(); //求绝度补

/*
私有方法区
*/
private:
	int charToPos(char c); //返回一个字符在字符表中的位置
	char posToChar(int pos); //返回一个某一个位置的字符
	void setInput(std::istream& ins); //从一个流输入集合
	void setOutput(std::ostream& os); //把集合输出到一个标准流中去

};

