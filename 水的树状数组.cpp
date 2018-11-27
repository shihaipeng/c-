#include<iostream>
using namespace std;
/*
树状数组
其实只是一个预处理的方法，仅用于区间求和

https://blog.csdn.net/flushhip/article/details/79165701
https://www.cnblogs.com/hsd-/p/6139376.html 
https://blog.csdn.net/gaojunonly1/article/details/80102418

重点在于这一个等式啊！！！！！
 
C[i]=A[i-lowbit(i)+1]+A[i-lowbit(i)+2]+......A[i];


arr={1,2,3,4,5,6,7,8,9} 
c:
	          8     
    4        
  2      6 
1  3   5    7
*/ 

const int maxn=10001;
int c[maxn];
int arr[maxn];
int m;

int lowbit(int x){
	return x&(-x);
}

int getsum(int x){
	int res=0;
	for(int i=x;i>0;i-=lowbit(i)){
		res+=c[i];
	}
	return res;
}

void add(int x,int a){
	for(int i=x;i<=m;i+=lowbit(i)){
		c[i]+=a;
	}
}

int main(){
	cin>>m;
	for(int i=1;i<=m;i++){
		cin>>arr[i];
		//for(int k=i-lowbit(i)+1;k<=i;k++){
			//cout<<i<<'	'<<k<<endl;
			//c[i]+=arr[k];
		//}
		add(i,arr[i]);
	}
	//add(1,2);
	for(int i=1;i<=m;i++){
		cout<<getsum(i)<<endl;
	}
	return 0;
} 
