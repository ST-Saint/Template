#include<bits/stdc++.h>

#define set(a,b) memset(a,(b),sizeof(a))

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int maxn=1e5+5;
const int maxm=2e5+5;

int first[maxn],ind;

struct Side{
  int u,v,w,next;
  Side(int u=0,int v=0,int w=0):u(u),v(v),w(w),next(first[u]){first[u]=ind++;}
}s[maxm];


void SPFA(int ST,int Dis[]){
  queue<int> q;
  int dis[maxn],inq[maxn]={0};
  dis[ST]=0;
  q.push(ST);
  while( !q.empty() ){
    int st=q.front();q.pop();
    inq[st]=0;
    for(int i=first[st];i!=-1;i=s[i].next){
      int np=s[i].v;
      if( dis[np]>dis[st]+s[i].w ){
        dis[np]=dis[st]+s[i].w;
        if( !inq[np] ) inq[np]=1,q.push(np);
      }
    }
  }
  memcpy(Dis,dis,sizeof(dis));
}

int main(){
#ifndef ONLINE_JUDGE
  freopen("SPFA.in","r",stdin);
  freopen("SPFA.out","w",stdout);
#endif
  ios::sync_with_stdio(false);
  return 0;
}
