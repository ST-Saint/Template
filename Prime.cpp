#include<bits/stdc++.h>

#define set(a,b) memset(a,(b),sizeof(a))

using namespace std;

typedef long long ll;

const int maxn=1e6+5;
const int upper=1e6;

bool prime[maxn];
int pri[maxn],mip[maxn],tot;

void Init(){
  for(int i=2;i<=upper;i++){
    if( !prime[i] ) pri[++tot]=i,mip[i]=tot;
    for(int j=1;j<=tot&&i*pri[j]<=upper;j++){
      prime[i*pri[j]]=true;
      mip[i*pri[j]]=j;
      if( i%pri[j]==0 ) break;
    }
  }
}

int main(){
#ifndef ONLINE_JUDGE
  freopen("Prime.in","r",stdin);
  freopen("Prime.out","w",stdout);
#endif
  ios::sync_with_stdio(false);
  Init();
  return 0;
}
