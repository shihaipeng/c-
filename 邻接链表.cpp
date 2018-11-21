#include<iostream>
#include<vector>
using namespace std;

const int maxn=10001;
struct Edge{
	int to,w;
	Edge(int t,int w):to(t),w(w){};
};
vector<Edge> edge[maxn];
int vis[maxn]={0};
int n,m,ans=0;

/////////调教成双向的队列，可双向插入取出 
int que[maxn];
int begin=0,end=0;

//平移是关键 
void move_forward(int p){
	int len=end-begin;
	for(int i=begin,j=0;i!=end;i++,j++){
		que[p+j]=que[i];
	}
	begin=p;end=begin+len;
}
void move_back(int p){
	int len=end-begin;
	for(int i=end-1,j=len-1;i>=begin;i--,j--){
		que[p+j]=que[i];
	}
	begin=p;end=begin+len;
}
void push_back(int x){
	que[end++]=x;
}
void push_front(int x){
	if(begin==0){
		move_back(10);
	} 
	que[--begin]=x;
}
int pop_front(){
	int r=que[begin++];
	if(begin>50){
		move_forward(10);
	}
	return r;
}
int pop_back(){
	return que[--end];
}
bool is_empty(){
	return begin==end;
}
int length(){
	return end-begin;
} 

//加入边（邻接列表版） 
void addedge(int a,int b,int w){
	Edge e(b,w);
	edge[a].push_back(e);
}

//edge[x]={1,2,3...}//x点指向的点
//edge[x][0]=1 
void dfs(int x){//深度优先搜索 
	vis[x]=1;
	for(int i=edge[x].size()-1;i>=0;i--){
		if(vis[edge[x][i].to]){
			continue;
		}else{
			dfs(edge[x][i].to);//这里也是，先访问，再打标记 
			//vis[edge[x][i].to]=1;//多余 
		}
	}
}

void bfs(int x){//广度优先搜索 
	vis[x]=1;
	for(int i=edge[x].size()-1;i>=0;i--){
		if(vis[edge[x][i].to]){
			continue;
		}else{
			push_back(edge[x][i].to);
		}
	}
	if(!is_empty()){//千万注意 访问后再打标记 
		bfs(pop_front());
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


void c(){//计算联通块的个数 
	for(int i=1;i<=n;i++){
		if(vis[i]){
			continue;
		}else{
			bfs(i);
			ans++;
		}
	}
} 

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
	/*
	for(int i=20;i!=0;i--){
		push_front(i);
		push_back(i);
	}
	for(int i=0;i<15;i++){
		pop_front();
	} 
	for(int i=begin;i!=end;i++){
		cout<<que[i]<<endl;
	}
	cout<<endl;
	cout<<begin<<' '<<end<<endl;
	for(int i=0;i!=end;i++){
		cout<<que[i]<<endl;
	}//输出：0 1 5 6 7 8 9 //0,1无用 
	*/
	return 0;
}
