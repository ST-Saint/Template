#include<bits/stdc++.h>

#define set(a,b) memset(a,(b),sizeof(a))

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int maxn=1000+5;
const int maxm=20000+5;

struct sides{
  int u,v,w;
  int next;
}s[maxm];

struct path{
  int w,route,node;
  friend bool operator > (const path& a,const path& b){
    return (a.w>b.w);
  }
};

priority_queue<path,vector<path>,greater<path> > q;
queue<int> que;
int dis[maxn],cur[maxn],inq[maxn];
int first[maxn],ind;
int n,m,k,times;

void SPFA()
{
  set(dis,127);
  dis[1]=0;
  que.push(1);
  while( !que.empty() ){
    int sd=que.front();que.pop();
    inq[sd]=0;
    for(int i=first[sd];i!=-1;i=s[i].next)
      if( dis[s[i].v]>dis[sd]+s[i].w && s[i].u<s[i].v ){
	dis[s[i].v]=dis[sd]+s[i].w;
	if( !inq[s[i].v] ){
	  inq[s[i].v]=1;
	  que.push(s[i].v);
	}
      }
  }
}

void Bfs()
{
  q.push((path){dis[n],0,n});
  while( !q.empty() ){
    path sd=q.top();q.pop();
    if( sd.node==1 ){
      times++;
      cout << sd.route << endl ;
      if( times==k ) return ;
    }
    for(int i=first[sd.node];i!=-1;i=s[i].next)
      if( s[i].u>s[i].v )
	q.push((path){sd.route+s[i].w+dis[s[i].v],sd.route+s[i].w,s[i].v});
  }
}

int main()
{
#ifndef ONLINE_JUDGE
  freopen("K-Short.in","r",stdin);
  freopen("K-Short.out","w",stdout);
#endif
  ios::sync_with_stdio(false);
  cin >> n >> m >> k ;
  set(first,-1);
  for(int i=1;i<=m;i++){
    int u,v,w;
    cin >> u >> v >> w ;
    s[ind]=(sides){u,v,w,first[u]},first[u]=ind++;
    s[ind]=(sides){v,u,w,first[v]},first[v]=ind++;
  }
  SPFA(),Bfs();
  for(int i=times+1;i<=k;i++) cout << -1 << endl ;
  return 0;
}
