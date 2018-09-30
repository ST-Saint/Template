#include<bits/stdc++.h>

#define set(a,b) memset(a,(b),sizeof(a))

using namespace std;

typedef long long ll;

const int maxn=10000+5;
const int maxm=200000+5;

struct Side{
  int u,v,w,c,next;
  Side(int u=0,int v=0,int c=0,int next=0):u(u),v(v),c(c),next(next){}
}s[maxm];

queue<int> q;
int h[maxn];
int first[maxn],cur[maxn],ind;
int S,T;

void Insert(int u,int v,int c){
  s[ind]=Side(u,v,c,first[u]),first[u]=ind++;
  s[ind]=Side(v,u,0,first[v]),first[v]=ind++;
}

bool Bfs()
{
  set(h,-1),h[T]=0;
  q.push(T);
  while( !q.empty() ){
    int sd=q.front();q.pop();
    for(int i=first[sd];i!=-1;i=s[i].next)
      if( s[i^1].c>0 && h[s[i].v]==-1 ){
	h[s[i].v]=h[sd]+1;
	q.push(s[i].v);
      }
  }
  return h[S]!=-1;
}

int Dfs(int x,int flow)
{
  if( x==T ) return flow;
  int used=0;
  for(int &i=cur[x];i!=-1;i=s[i].next)
    if( s[i].c>0 && h[s[i].v]+1==h[x] ){
      int w=Dfs(s[i].v,min(s[i].c,flow-used));
      s[i].c-=w,s[i^1].c+=w;
      used+=w;
      if( used==flow ) return flow;
    }
  return used;
}

int Dinic()
{
  int Maxflow=0;
  while( Bfs() ){
    memcpy(cur,first,sizeof(first));
    Maxflow+=Dfs(S,INT_MAX);
  }
  return Maxflow;
}

int main(){
#ifndef ONLINE_JUDGE
  freopen("Dinic.in","r",stdin);
  freopen("Dinic.out","w",stdout);
#endif
  ios::sync_with_stdio(false);
  return 0;
}
