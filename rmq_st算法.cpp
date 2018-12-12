#include<iostream>
using namespace std;
const int maxn=50001;
int n;
int a[maxn],dp[maxn][25],lg[maxn];


inline int max(int a,int b){
	return a>b?a:b;
}

int rmq(int l,int r){
	int k=0;
	while(1<<(k+1)<=r-l+1) ++k;
	return max(dp[l][k],dp[r-(1<<k)+1][k]);
}
void st(){
	for(int i=1;i<=n;++i){
		dp[i][0]=a[i];
	}
	for(int j=1;(1<<j)<=n;++j){//2^j<=n ==> j<=log2(n)
		for(int i=1;i+(1<<j)-1<=n;++i){//i+j^2-1<=n ==> log2(n-i+1)>=j
			dp[i][j]=max(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
		}
	}
}

int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
	}
	for(int i=1;i<=n;++i){
		lg[i]=lg[i-1]+(1<<lg[i-1]==i);
		//lg[1]=0+1=1;
		//lg[2]=1+1=2;
	}//log2(n)+1
	//for(int i=0;i<=65;i++){
	//	cout<<"log2("<<i<<")= "<<lg[i]-1<<endl;
	//}
	st();
	while(true){
		int l,r;
		cin>>l>>r;
		cout<<rmq(l,r)<<endl;
	}
	return 0;
} 
//1 2 4 5 2 4 7 2 7 3 9 0 5 4 2
// 1 2 4 5 2 4 7 2 7 3  9  0  5  4  2
// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
