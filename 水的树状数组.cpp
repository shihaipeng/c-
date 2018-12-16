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
/*
单点修改+区间和
https://www.luogu.org/problemnew/show/P3374
#include<iostream>
using namespace std;
const int maxn=500100;
int a[maxn];
int n,m;

int lowbit(int t){
    return t&(-t);
}

void add(int x,int y){//单点修改要改其上方的值
    for(int i=x;i<=n;i+=lowbit(i))
        a[i]+=y;
}

int sum(int x){//区间是求其下方之和
    int ans=0;
    for(int i=x;i>0;i-=lowbit(i))
        ans+=a[i];
    return ans;
}

int range(int a,int b){
    return sum(b)-sum(a-1);
}

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
	    int a;
	    cin>>a;
	    add(i,a);
	}
	for(int i=0;i<m;i++){
	    int a,b,c;
	    cin>>a>>b>>c;
	    if(a==1){
	        add(b,c);
	    }
	    if(a==2){
	        cout<<range(b,c)<<endl;
	    }
	}
	return 0;
} 
*/

/*
区间修改+单点查询
这里介绍一下差分数组
原数组：1 2 3 5 6 3
差分 ：1 1 1 2 1 -3
所以我们要用树状数组来维护差分数组
求单点查询就是求差分数组前缀和
求区间修改就是将[l,r]区间在树状数组中l+k,r+1-k
代码：
#include<iostream>
using namespace std;
const int maxn=500010;
int a[maxn];
int n,m;

int lowbit(int x){
    return x&(-x);
}

void add(int p,int x){
    for(int i=p;i<=n;i+=lowbit(i)){
        a[i]+=x;
    }
}

int find(int p){
    int res=0;
    for(int i=p;i>0;i-=lowbit(i)){
        res+=a[i];
    }
    return res;
}

void range_add(int x,int y,int k){
    add(x,k);
    add(y+1,-k);
}


int main(){
    cin>>n>>m;
    int a,b;
    for(int i=1;i<=n;i++){
        cin>>b;
        add(i,b-a);
        a=b;
    }
    for(int i=0;i<m;i++){
        int s,x,y,k;
        cin>>s;
        if(s==1){
            cin>>x>>y>>k;
            range_add(x,y,k);
        }
        if(s==2){
            cin>>x;
            cout<<find(x)<<endl;
        }
    }
    return 0;
}
*/
