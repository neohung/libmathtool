# Libmathtool
這是我的網誌 [Neo's blogger](http://iamhahar.blogspot.tw/) 放著Machine Learning,Embedded相關.

* **Machine Learning** - 主要是HMM跟Boosting在Audio跟Video上的應用.
* **Embeded** - Linux Kernel Driver Porting 跟 Android還有RTOS相關.

Libmathtool的目的是實作一些ML或Audio跟Video會用到的數學處理方法

## Getting Started
* 使用`git@github.com:neohung/libmathtool.git`抓取code
* 編譯:`make all`

## Examples
*注意目前libmathtool尚未完成!*

目前完成的有DFT跟FFT:

FFT:
```c
int i,n=128;
double w1,w2,s1[n],s2[n],fr[n],fi[n],FR[n],FI[n];
double *F = (double*) malloc(sizeof(double)*n);
const double PI=2.0 * acos(0);
for(i=0;i<n;i++){
	w1 = PI / 5;
	w2 = PI / 10;
	s1[i] = cos(w1*i);
	s2[i] = cos(w2*i);
	fr[i] = s1[i]+s2[i];
	fi[i] = 0;
}
FFT(n,0,fr,fi,FR,FI);
```
## Change Log
###2014-11-02
* 加上FFT

-![alt text](http://3.bp.blogspot.com/-kLd0VbVOFOk/T5R6jREfDFI/AAAAAAAAANA/YK7spn6JwJQ/s1600/1.JPG "Lucas-Kanade Optical Flow的圖")