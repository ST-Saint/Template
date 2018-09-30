#include<bits/stdc++.h>

#define set(a,b) memset(a,(b),sizeof(a))

using namespace std;

typedef long long ll;

double F(double x){
}

double Sumption(double l,double r){
  return (F(l)+4*F((l+r)/2)+F(r))*(r-l)/6;
}

double Simpson(double l,double r,double eps){
  double mid=(l+r)/2;
  double ls=Sumption(l,mid),lr=Sumption(mid,r),lt=Sumption(l,r);
  if( fabs(ls+lr-lt)<=15*eps ) return ls+lr+(ls+lr-lt)/15;
  else return Simpson(l,mid,eps/2)+Simpson(mid,r,eps/2);
}

int main(){
#ifndef ONLINE_JUDGE
  freopen("Simpson.in","r",stdin);
  freopen("Simpson.out","w",stdout);
#endif
  ios::sync_with_stdio(false);
  return 0;
}
