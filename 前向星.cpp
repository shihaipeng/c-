#include<iostream>
using namespace std;

struct Edge{
	int next,to,w;
};

const int maxn=10001;
int head[maxn];
int cnt=0;//�洢�ıߵ���Ŀ 
Edge edge[maxn];//��������
int n,m,ans=0;

void addedge(int x,int y,int w){
	edge[++cnt].next=head[x];//�������ӣ���1��ʼ
	edge[cnt].to=y;//�洢���� 
	edge[cnt].w=w;
	head[x]=cnt;//��������ͷ 
} 

int vis[maxn]={0};

void dfs(int x){//��x��ʼ 
	if(!vis[x]){
		vis[x]=1;
		for(int i=head[x];i!=0;i=edge[i].next){
			if(vis[i]){
				continue;
			}else{
				dfs(edge[i].to);
			}
		}
	}
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
	cin>>n>>m;//n��m��
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
