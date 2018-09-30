#include<bits/stdc++.h>

#define set(a,b) memset(a,(b),sizeof(a))

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int maxn=1e5+5;
const int maxm=2e5+5;

ll Qpower(ll x,ll p,ll mod){ll r=1;while(p){if(p&1)r=r*x%mod;x=x*x%mod;p>>=1;}return r;}
ll gcd(ll a,ll b){return a==0?b:gcd(b%a,a);}

struct Side{
  int u,v,w,next;
}s[maxm];

int first[maxn],ind;

void Insert(int u,int v,int w=0){
  s[ind]=(Side){u,v,w,first[u]},first[u]=ind++,deg[u]++;
  s[ind]=(Side){u,v,w,first[u]},first[u]=ind++,deg[v]++;
}

int main(){
#ifndef ONLINE_JUDGE
  freopen("graph.in","r",stdin);
  freopen("graph.out","w",stdout);
#endif
  ios::sync_with_stdio(false);
  set(first,-1),ind=0;
  return 0;
}
