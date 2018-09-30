#include<bits/stdc++.h>

#define set(a,b) memset(a,(b),sizeof(a))

using namespace std;

typedef long long ll;

const int maxn=10000+5;
const int maxm=200000+5;

struct Side{
  int u,v,c,w,next;
  Side(){}
  Side(int u,int v,int c,int w,int next):
    u(u),v(v),c(c),w(w),next(next){}
}s[maxm];

queue<int> q;
int dis[maxn],inq[maxn],par[maxn];
int first[maxn],ind;
int n,m,S,T,cost;

void Insert(int u,int v,int c,int w)
{
  s[ind]=Side{u,v,c,w,first[u]},first[u]=ind++;
  s[ind]=Side{v,u,0,-w,first[v]},first[v]=ind++;
}

int Costflow()
{
  int Cost=0,Flow=0;
  while( true ){
    for(int i=S;i<=T;i++) dis[i]=INT_MAX;
    dis[S]=0;
    q.push(S);
    while( !q.empty() ){
      int sd=q.front();q.pop();
      inq[sd]=0;
      for(int i=first[sd];i!=-1;i=s[i].next)
        if( dis[s[i].v]>dis[sd]+s[i].w && s[i].c ){
          dis[s[i].v]=dis[sd]+s[i].w;
          par[s[i].v]=i;
          if( !inq[s[i].v] ){
            inq[s[i].v]=1;
            q.push(s[i].v);
          }
        }
    }
    if( dis[T]==INT_MAX ) break;
    int t=T,flow=INT_MAX;
    while( t!=S ){
      flow=min(flow,s[par[t]].c);
      t=s[par[t]].u;
    }
    t=T;
    while( t!=S ){
      Cost+=flow*s[par[t]].w;
      s[par[t]].c-=flow,s[par[t]^1].c+=flow;
      t=s[par[t]].u;
    }
    Flow+=flow;
  }
  return Cost;
}

int main()
{
#ifndef ONLINE_JUDGE
  freopen("Costflow.in","r",stdin);
  freopen("Costflow.out","w",stdout);
#endif
  set(first,-1),ind=0;
  cost=Costflow();
  return 0;
}
