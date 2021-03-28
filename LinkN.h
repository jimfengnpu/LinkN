/*
 * LinkN.h
 *
 *  Created on: 2021年3月16日
 *  Author: jimfeng www.github.com/jimfengnpu/LinkN
 */
#ifndef LINKN_H_
#define LINKN_H_

#define MaxComm 500  //定义最大小数点后位数
typedef struct link{
	int dig;
	link *pref, *next;
}num, *pnum;

class LinkN{//此类用于的非负数的精确+-*/=,==,>运算
private:
	num * head;
	int comm;
	int len;
	void delu0();//删除不必要的0
	void coNum(LinkN a);//格式规格化
public:
	LinkN(int a);//初始化大小不超过int类型数值大小
	~LinkN();
	void printValue();
	double getValued();
	LinkN& tenTimes();//返回原数的10倍
	LinkN operator+ ( LinkN a);
	LinkN operator- ( LinkN a);
	LinkN operator* ( LinkN a);
	LinkN operator/ ( LinkN a);
	bool operator> (const LinkN a);
	bool operator== (const LinkN a);
	LinkN& operator= ( LinkN a);
};

#endif /* LINKN_H_ */
