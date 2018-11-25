#include<bits/stdc++.h>
using namespace std;

const int maxn=10001;
int head[maxn];
int cnt=0;
struct Edge{
	int to,w,next;	
};
Edge edge[maxn];

void addedge(int x,int y,int w){
	edge[++cnt].next=head[x];
	edge[cnt].to=y;
	edge[cnt].w=w;
	head[x]=cnt;
}


struct P{
	int x,l;	
};
P que[maxn];
int begin=0,end=0;
void push(P a){
	que[end++]=a;	
}
P pop(){
	return que[begin++];	
}
bool is_empty(){
	return begin==end;	
}

int dis[maxn];

void bfs(int x,int l){
	dis[x]=l<dis[x]?l:dis[x];	
	cout<<x<<'	'<<l<<'	'<<dis[x]<<endl;
	for(int i=head[x];i!=0;i=edge[i].next){
		P lp;
		lp.x=edge[i].to;
		lp.l=edge[i].w+l;
		cout<<"push  "<<lp.x<<'	'<<lp.l<<endl;	
		push(lp);	
	}
	if(!is_empty()){
		P a=pop();
		bfs(a.x,a.l);	
	}	
}

int n,m;

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
	//memset(dis,maxn,sizeof(dis)/sizeof(int));
	//memset只能初始化int数组为0,-1 
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int a,b,c;
		cin>>a>>b>>c;
		addedge(a,b,c);
	}
	for(int i=0;i<n;i++){//初始化一个很大的值 
		dis[i]=maxn;
	}
	bfs(1,0);
	cout<<dis[4]<<endl;
	return 0;	
}
