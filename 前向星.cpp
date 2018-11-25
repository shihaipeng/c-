#include<iostream>
using namespace std;

struct Edge{
	int next,to,w;
};

const int maxn=10001;
int head[maxn];
int cnt=0;//存储的边的数目 
Edge edge[maxn];//所有链表
int n,m,ans=0;

void addedge(int x,int y,int w){
	edge[++cnt].next=head[x];//链表连接，从1开始
	edge[cnt].to=y;//存储数据 
	edge[cnt].w=w;
	head[x]=cnt;//更新链表头 
} 

int vis[maxn]={0};

void dfs(int x){//从x开始 
	vis[x]=1;
	///略
}

void c(){
	for(int i=1;i<=n;i++){
		if(vis[i]){
			continue;
		}else{
			dfs(i);
			ans++;
		}
	}
} 
//1--2--5--4   7  10
// \          /
//  3  6--8---  9--11 
/*
11 7 
1 2 1
5 4 1
2 5 1
3 1 1
6 8 1
8 7 1
9 11 1 
*/
int main(){
	cin>>n>>m;//n点m边
	for(int i=0;i<m;i++){
		int a,b,w;
		cin>>a>>b>>w;
		addedge(a,b,w);
		addedge(b,a,w);
	} 
	c();
	cout<<ans;
	return 0;
} 
