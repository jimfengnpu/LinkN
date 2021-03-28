#  LinkN
用于计算高位数非负小数的 c++ 实现
为保证精度，用int 类型初始化（必须是正数）
## Valid Operator
+ +、-、\*、/（ - 法仅支持大数减小数）
+ \>、==、=
##  Universal Function
+ getValued(): 返回double 类型的值
+ printValue():直接打印存储的数据
+ tenTimes(): 返回原数的10倍（比乘10快）
## 注 
+ testPi : 一个demo,计算高精度pi 
```c++
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
```
+ 可通过更改LinkN.h 中MaxComm 的值改变精确度（小数点后位数）

