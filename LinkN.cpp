/*
 * LinkN.cpp
 *  Created on: 2021年3月16日
 *  Author: jimfeng www.github.com/jimfengnpu/LinkN
 * 	水平有限，还望多多指正
 */
#include <cstdlib>
#include <iostream>
#include "LinkN.h"


num * creatPrefNode(num * head,num* p){
	num * nnod;
	nnod =(num *)malloc(sizeof(num));
	nnod->pref=head;
	nnod->next=p;
	p->pref=nnod;
	head->next=nnod;
	return nnod;
}
void LinkN::coNum(LinkN a){
	for(num * p =a.head->pref;;p=p->pref){
			int t =p->dig;
			if(t>=10){
				if(p->pref==a.head){
					creatPrefNode(a.head,p);
					a.len++;
				}
				p->dig=t%10;
				p->pref->dig +=t/10;
			}else if(p->pref==a.head)break;//进位累加
		}
}
void LinkN::delu0(){
	int n=len-1,f=0;
		for(num * p =head->next;p!=head;p=p->next,n--){
			if((p->dig==0&&n>comm&&!f)||(-n>MaxComm)){
				num *t =p->pref;
				p->pref->next=p->next;
				p->next->pref=p->pref;
				free(p);
				p =t;
				len--;
			}else f=1;
		}
}
LinkN::LinkN(int a){
			num * c,* p;
			int i,ws;
			for(i =0,ws =a;ws>0;ws /=10)i++;
			if(!a)i=1;
			comm =0;//小数位数
			len =i;//总长
			head =(num*)malloc(sizeof(num));
			p =head;
			for(int k =0;k<len&&p!=NULL;k++){
				c =(num*)malloc(sizeof(num));
				c->pref =p;
				c->next =head;
				head->pref =c;
				p->next =c;
				p=c;
			}
			while(p!=head){
				p->dig=a%10;
				a= a/10;
				p=p->pref;
			}
			delu0();
		}
LinkN::~LinkN(){
}
LinkN& LinkN::tenTimes(){
	if(comm)comm--;
	else{
		num * nnod =creatPrefNode(head->pref,head);
		nnod->dig=0;
		len++;
	}
	delu0();
	return *this;
}
LinkN LinkN::operator+ (const LinkN a){//两数相加
	LinkN res(0);
	int l,la,j=0;
	num *nua,*nub,*nur;
	res.comm= comm>a.comm?comm:a.comm;
	l = res.comm-comm;
	la = res.comm-a.comm;
	nua =head->pref;nub =a.head->pref;
	nur =res.head->pref;
	for(int i =0;;i++){
		int t,na=0,nb=0;
		if(i>=l&&nua!=head)na=nua->dig;
		if(i>=la&&nub!=a.head)nb =nub->dig;//数位对齐
		t=na+nb+j;
		if(t>=10){
			t=t-10;
			j=1;
		}else j=0;
		if((!t)&&nua==head&&nub==a.head)break;
		if(nur==res.head){
			nur =creatPrefNode(res.head,nur->next);
			res.len++;
		}
		nur->dig =t;
		nur =nur->pref;
		if(i>=l&&nua!=head)nua =nua->pref;
		if(i>=la&&nub!=a.head)nub=nub->pref;
	}
	return res;
}
LinkN LinkN::operator- (const LinkN a){//大数减小数
	LinkN res(0);
	int l,la,j=0;
	num *nua,*nub,*nur;
	res.comm= comm>a.comm?comm:a.comm;
	l = res.comm-comm;
	la = res.comm-a.comm;
	nua =head->pref;nub =a.head->pref;
	nur =res.head->pref;
	for(int i =0;;i++){
		int t,na=0,nb=0;
		if(i>=l&&nua!=head)na=nua->dig;
		if(i>=la&&nub!=a.head)nb =nub->dig;
		t=na-nb-j;
		if(t<0){
			t=t+10;
			j=1;
		}else j=0;
		if((!t)&&nua==head&&nub==a.head)break;
		if(nur==res.head){
			nur =creatPrefNode(res.head,nur->next);
			res.len++;
		}
		nur->dig =t;
		nur =nur->pref;
		if(i>=l&&nua!=head)nua =nua->pref;
		if(i>=la&&nub!=a.head)nub=nub->pref;
	}
	res.delu0();
	return res;
}

LinkN LinkN::operator* (const LinkN a){ //计算两数乘积
	LinkN res(0);
	res.comm =comm +a.comm;
	num *nu,*nua,*nur,*nut=res.head->pref;
	for(nu=head->pref;nu!=head;nu=nu->pref){
		nur =nut;
		for(nua=a.head->pref;nua!=a.head;nua =nua->pref){
			if(nur==res.head){
				nur =creatPrefNode(res.head,nur->next);
				res.len++;
			}
			nur->dig +=nu->dig*nua->dig;
			nur=nur->pref;
		}
		nut =nut->pref;
	}
	coNum(res);
	res.delu0();
	return res;
}
LinkN LinkN::operator/ (const LinkN a){
	LinkN res(0),modd(0),shang(0);
	num * nur =res.head->next;
	int t,n=len-comm,d;
	res.comm =comm;
	for(num * p =head->next;-n<=MaxComm;n--){
		t=-1;
		d=0;
		LinkN chut(0),chus(0);
		if(p!=head)d=p->dig;
		modd = modd.tenTimes() + LinkN(d);
		do{
			chus=chut;t++;
			chut =chut +a;
		}while(!(chut>modd));//试商
		modd =modd -chus;
		if(nur==res.head){
			nur =creatPrefNode(nur->pref,res.head);
			res.len++;
			if(n<=0)res.comm++;
			}
		nur->dig =t;
		if(modd==shang)break;
		nur=nur->next;
		if(p!=head)p =p->next;
	}
	coNum(res);
	res.delu0();
	return res;
}
bool LinkN::operator> (const LinkN a){//比较大小
	num *p,*pa;
	int comp =len-comm-(a.len-a.comm);
	if(comp>0)return true;
	else if(comp<0)return false;
	else{
	for( p =head->next,pa =a.head->next;comp==0&&p!=head&&pa!=a.head;p=p->next,pa=pa->next){
			comp =p->dig-pa->dig;
	}
	if(comp==0){
		comp = p==head?-1:1;
	}
	if(comp>0)return true;
	else return false;
	}
}
bool LinkN::operator== (const LinkN a){
	num *p,*pa;
	if((len!=a.len)||(comm!=a.comm)){
		return false;
	}
	for(p=head->next,pa=a.head->next;p!=head&&pa!=a.head;){
		if(p->dig!=pa->dig)return false;
		p=p->next,pa=pa->next;
	}
	return true;
}
LinkN& LinkN::operator= ( LinkN a){//赋值
	comm =a.comm;
	len= a.len;
	head =a.head;
	return *this;
}
double LinkN::getValued(){//返回double型的值
	double val=0,expc=0.1;
	int n =0,c=0,l=len-comm-1;
	for(num * p =head->next;p!=head&&n<=len;n++){
		if(!c)val =10*val +p->dig;
		else{
			val= val+expc* p->dig;
			expc=expc/10;
		}
		if(n==l)c=1;
		p=p->next;
	}
	return val;
}
void LinkN::printValue(){//打印数据的值
			int i=0,c=0,nc=0;
			for(num * n=head->next;n!=head&&nc<MaxComm;n =n->next){
				std::cout<<n->dig;
				i++;
				if(c)nc++;
				if(i==len-comm&&comm){std::cout <<".";c=1;}
				if(c&&nc%100==0)std::cout<<std::endl;
			}
			std::cout<<std::endl;
	}
