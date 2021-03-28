//============================================================================
// Name        : testPi.cpp
// Author      : jiangFeng
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "LinkN.h"
using namespace std;

int main() {
	int n,a,b;
	LinkN r =LinkN(1)/LinkN(2);
	LinkN pi(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		pi=pi+r;
		a=(2*i-1)*(2*i-1);
		b=8*i*(2*i+1);
		r = (LinkN(a)/LinkN(b))*r;
		if(i%100==0)cout<<"calculating..."<<endl;
}
	cout<<"结果: pi=";
	(LinkN(6)*pi).printValue();
	return 0;
}
