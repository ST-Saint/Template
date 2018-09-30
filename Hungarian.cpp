#include<bits/stdc++.h>

#define set(a,b) memset(a,(b),sizeof(a))

using namespace std;

typedef long long ll;

const int maxn=1000+5;
const int maxm=100000+5;

struct Side{
  int u,v,next;
}s[maxm];

bool vis[maxn];
int match[maxn];
int first[maxn],ind;
int n,m,cnt;

void Insert(int u,int v){
  s[ind]=Side{u,v,first[u]},first[u]=ind++;
  s[ind]=Side{v,u,first[v]},first[v]=ind++;
}

bool Find(int x){
  for(int i=first[x];i!=-1;i=s[i].next)
    if( !vis[s[i].v] ){
      vis[s[i].v]=true;
      if ( !match[s[i].v] || Find(match[s[i].v]) ){
        match[s[i].v]=x;
        match[x]=s[i].v;
        i=s[i].next;
        return true;
      }
    }
  return false;
}

int Hungarian(){
  int temp=0;
  for(int i=1;i<=n;i++)
    if( !match[i] ){
      set(vis,0);
      temp+=Find(i);
    }
  return temp;
}

int main(){
#ifndef ONLINE_JUDGE
  freopen("Hungarian.in","r",stdin);
  freopen("Hungarian.out","w",stdout);
#endif
  ios::sync_with_stdio(false);
  cnt=Hungarian();
  return 0;
}
