#include<bits/stdc++.h>

#define set(a,b) memset(a,(b),sizeof(a))

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

ll Qpower(ll x,ll p,ll m){ll r=1;while(p){if(p&1)r=r*x%m;x=x*x%m;p>>=1;}return r;}
ll gcd(ll a,ll b){return a==0?b:gcd(b%a,a);}

int main(){
#ifndef ONLINE_JUDGE
  freopen(".in","r",stdin);
  freopen(".out","w",stdout);
#endif
  ios::sync_with_stdio(false);
  return 0;
}
