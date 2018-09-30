#include<bits/stdc++.h>

#define set(a,b) memset(a,(b),sizeof(a))

using namespace std;

typedef long long ll;

const int maxn=100000+5;
const int maxm=200000+5;

class Side{
public:
  int u,v,next;
}s[maxm];

stack<int> h;
int dfn[maxn],low[maxn],ist[maxn],stp;
int scc[maxn],scnt;
int first[maxn],ind;
int n,m;

void Insert(int u,int v){
  s[ind]=(Side){u,v,first[u]},first[u]=ind++;
}

void Tarjan(int x){
  dfn[x]=low[x]=++stp;
  h.push(x),ist[x]=1;
  for(int i=first[x];i!=-1;i=s[i].next)
    if( !dfn[s[i].v] ) Tarjan(s[i].v),low[x]=min(low[x],low[s[i].v]);
    else if( ist[s[i].v] ) low[x]=min(low[x],low[s[i].v]);
  if( dfn[x]==low[x] ){
    scnt++;
    while( h.top()!=x ){
      scc[h.top()]=scnt,h.pop();
    }
    scc[x]=scnt,h.pop();
  }
}

void ReBuild(){
  typedef pair<int,int> pii;
  map<pii,bool> Map;
  int snum=ind;
  set(first,-1),ind=0;
  for(int i=0;i<snum;i++)
    if( scc[s[i].u]!=scc[s[i].v] && !Map[(pii){scc[s[i].u],scc[s[i].v]}] ){
      Map[(pii){scc[s[i].u],scc[s[i].v]}]=true;
      Insert(scc[s[i].u],scc[s[i].v]);
    }
  for(int i=ind;i<snum;i++) s[i]=(Side){0,0,0};
}

int main(){
#ifndef ONLINE_JUDGE
  freopen("Tarjan_Scc.in","r",stdin);
  freopen("Tarjan_Scc.out","w",stdout);
#endif
  ios::sync_with_stdio(false);
  return 0;
}
