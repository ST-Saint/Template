#include<bits/stdc++.h>

#define maxp 13
#define maxd 23
#define maxt 512
#define maxn 3000+5
#define maxm 6000+5
#define mod 19260817
#define set(a,b) memset(a,(b),sizeof(a))

using namespace std;

typedef long long ll;

unsigned long long seed;

int mult[maxt][maxt];

struct Matrix{
  int l,g[maxd][maxd];
  friend Matrix operator * (const Matrix &a,const Matrix &b){
    Matrix c=a;set(c.g,0);
    for(int i=1;i<=c.l;i++)
      for(int j=1;j<=c.l;j++)
	for(int k=1;k<=c.l;k++)
	  c.g[i][j]^=mult[a.g[i][k]][b.g[k][j]];
    return c;
  }
}Iden;

int calc(int x,int y){
  int a[3][3],b[3][3],c[3][3],res=0;
  set(c,0);
  for(int i=2;i>=0;i--)
    for(int j=2;j>=0;j--)
      a[i][j]=x&1,x>>=1;
  for(int i=2;i>=0;i--)
    for(int j=2;j>=0;j--)
      b[i][j]=y&1,y>>=1;
  for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
      for(int k=0;k<3;k++)
	c[i][j]^=a[i][k]&b[k][j];
  for(int i=0;i<3;i++)
    for(int j=0;j<3;j++)
      res=res<<1|c[i][j];
  return res;
}

void Init(){
  for(int i=0;i<(1<<9);i++)
    for(int j=0;j<(1<<9);j++)
      mult[i][j]=calc(i,j);
  Iden.l=22;
  for(int i=1;i<=Iden.l;i++) Iden.g[i][i]=273;
}

int main(){
#ifndef ONLINE_JUDGE
  freopen("BitMatrix.in","r",stdin);
  freopen("BitMatrix.out","w",stdout);
#endif
  ios::sync_with_stdio(false);
  Init();
  return 0;
}
